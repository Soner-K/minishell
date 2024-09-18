/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files_control.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 16:26:45 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/18 16:31:27 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_extra_files(t_exec *cmds_list)
{
	if (cmds_list->next != NULL)
		close(cmds_list->pipe_fdo);
	if (cmds_list->prev != NULL)
		close(cmds_list->prev->pipe_fdi);
}

void	close_files(t_exec *cmds_list)
{
	if (cmds_list->files_info->infile_info->name)
		close(cmds_list->infile);
	if (cmds_list->files_info->outfile_info->type)
		close(cmds_list->outfile);
}
