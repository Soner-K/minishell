/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 17:27:37 by ftanon            #+#    #+#             */
/*   Updated: 2024/09/20 16:18:13 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_pid_array(t_data *pipe_info)
{
	pipe_info->counter = 0;
	pipe_info->pids = ft_calloc(pipe_info->total_cmds + 1, sizeof(pid_t));
}

void	store_pid(t_data *pipe_info, pid_t fork_id)
{
	pipe_info->pids[pipe_info->counter] = fork_id;
	pipe_info->counter++;
}

void	close_no_file(t_exec *cmds_list)
{
	if (cmds_list->pipe_fdi != -1)
		close(cmds_list->pipe_fdi);
	if (cmds_list->pipe_fdo != -1)
		close(cmds_list->pipe_fdo);
	// exit(EXIT_FAILURE);
}

void	wait_pipe_files(t_data *data)
{
	int	i;
	int	status;

	signal(SIGINT, &sig_handler_wait);
	status = 0;
	i = 0;
	while (i < data->total_cmds)
	{
		waitpid(data->pids[i], &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		if (WIFSIGNALED(status))
			data->exit_status = WTERMSIG(status) + 128;
		i++;
	}
}

void	close_parent(t_exec *head, t_data *data)
{
	close_pipe_files(head);
	wait_pipe_files(data);
}
