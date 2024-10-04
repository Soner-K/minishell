/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 23:29:23 by sumseo            #+#    #+#             */
/*   Updated: 2024/10/04 15:42:09 by sumseo           ###   ########.fr       */
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

void	heredoc_init_name(t_exec *cur_list, t_data *data, int i)
{
	cur_list->files_info->infile_info->final_name = data->hd_files[i];
	cur_list->files_info->infile_info->rights = 6;
	if (i > 0 && data->fd_hd[i - 1] != -1)
		close(data->fd_hd[i - 1]);
}
