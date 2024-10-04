/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:07:40 by sumseo            #+#    #+#             */
/*   Updated: 2024/10/04 18:39:24 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_child_pipe(t_exec *cmds_list, char **env_copy)
{
	if (parse_path(cmds_list->cmd_array, cmds_list->path))
		execve(cmds_list->path, cmds_list->cmd_array, env_copy);
	else
	{
		store_or_free(NULL, NULL, false, true);
		exit(127);
	}
}

void	exec_pipe(t_exec *cmds_list, char **env_copy, int i, t_env **env_list)
{
	redirection(cmds_list, cmds_list->data, i);
	if (which_builtin(cmds_list) > 0)
		exec_builtin(which_builtin(cmds_list), &cmds_list, env_list);
	else
		init_child_pipe(cmds_list, env_copy);
	store_or_free(NULL, NULL, false, true);
	exit(0);
}

void	file_close(t_exec *cmds_list, t_data *data, int fork_id)
{
	store_pid(data, fork_id);
	if (cmds_list->next != NULL)
		close(cmds_list->pipe_fdo);
	if (cmds_list->prev != NULL)
		close(cmds_list->prev->pipe_fdi);
}

void	runtime_shell_init(t_data *data, t_exec *cmds_list, int i)
{
	cmds_list->pipe_fdi = -1;
	cmds_list->pipe_fdo = -1;
	pipe_init(data, cmds_list, i);
	signal(SIGQUIT, sig_handler_quit);
}

void	runtime_shell(t_exec *cmds_list, char **env_copy, t_data *data,
		t_env **env_list)
{
	pid_t	fork_id;
	int		i;
	t_exec	*head;

	head = cmds_list;
	i = 0;
	init_pid_array(data);
	launch_heredoc(&cmds_list, data);
	while (i < data->total_cmds)
	{
		runtime_shell_init(data, cmds_list, i);
		fork_id = fork();
		if (fork_id == 0)
		{
			runtime_signal();
			if (getfile(&cmds_list, data))
				exec_pipe(cmds_list, env_copy, i, env_list);
			else
				runtime_free(cmds_list);
		}
		file_close(cmds_list, data, fork_id);
		i++;
		cmds_list = cmds_list->next;
	}
	close_parent(head, data);
}
