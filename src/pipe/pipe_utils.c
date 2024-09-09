/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 23:29:23 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/09 12:22:14 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_arr_length(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}

int	count_cmds(t_parse *cmds_list)
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

void	close_no_file(t_parse *cmds_list)
{
	close(cmds_list->pipe_fdi);
	close(cmds_list->pipe_fdo);
	exit(EXIT_FAILURE);
}

void	close_parent(t_parse *head, t_pipe *pipe_info, t_data *data)
{
	close_pipe_files(head);
	wait_pipe_files(pipe_info, data);
	free(pipe_info->pids);
	free(pipe_info);
}
