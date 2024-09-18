/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:07:40 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/18 16:35:28 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_child_pipe(t_exec *cmds_list, t_data *pipe_info, char **env_copy,
		int i)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
	if (parse_path(cmds_list->cmd_array, cmds_list->path))
	{
		redirection(cmds_list, pipe_info, i);
		execve(cmds_list->path, cmds_list->cmd_array, env_copy);
	}
	else
		exit(127);
}

void	exec_pipe(t_exec *cmds_list, char **env_copy, int i, t_env **env_list)
{
	if (which_builtin(cmds_list) > 0)
		redirect_and_init(cmds_list, cmds_list->data, i, env_list);
	else
	// exec_pipe(cmds_list, data, env_copy, i);
	{
		init_child_pipe(cmds_list, cmds_list->data, env_copy, i);
		exit(0);
	}
}

void	file_close(t_exec *cmds_list, t_data *data, int fork_id)
{
	store_pid(data, fork_id);
	if (cmds_list->next != NULL)
		close(cmds_list->pipe_fdo);
	if (cmds_list->prev != NULL)
		close(cmds_list->prev->pipe_fdi);
}

void	redirect_and_init(t_exec *cmds_list, t_data *data, int i,
		t_env **env_list)
{
	redirection(cmds_list, data, i);
	exec_builtin(which_builtin(cmds_list), &cmds_list, env_list);
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
	while (i < data->total_cmds)
	{
		pipe_init(data, cmds_list, i, data);
		fork_id = fork();
		if (fork_id == 0)
		{
			if (getfile(&cmds_list))
				exec_pipe(cmds_list, env_copy, i, env_list);
			else
				close_no_file(cmds_list);
		}
		file_close(cmds_list, data, fork_id);
		i++;
		cmds_list = cmds_list->next;
	}
	close_parent(head, data);
}
