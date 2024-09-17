/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 23:29:23 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/17 14:50:29 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_exec *cmds_list)
{
	int	total_cmd;

	total_cmd = 0;
	while (cmds_list)
	{
		if (cmds_list->cmd_array)
			total_cmd++;
		cmds_list = cmds_list->next;
	}
	return (total_cmd);
}

void	pipe_null_check(void)
{
	perror("pipe_info_malloc");
	exit(EXIT_FAILURE);
}

void	close_no_file(t_exec *cmds_list)
{
	close(cmds_list->pipe_fdi);
	close(cmds_list->pipe_fdo);
	exit(EXIT_FAILURE);
}
void	wait_pipe_files(t_data *data)
{
	int	i;
	int	status;

	status = 0;
	i = 0;
	while (i < data->total_cmds)
	{
		waitpid(data->pids[i], &status, 0);
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		i++;
	}
}

void	close_parent(t_exec *head, t_data *data)
{
	close_pipe_files(head);
	wait_pipe_files(data);
	free(data->pids);
}
