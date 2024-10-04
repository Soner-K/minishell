/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getfile_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 20:39:12 by sumseo            #+#    #+#             */
/*   Updated: 2024/10/04 20:48:12 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	final_infile_problem(t_data *data, t_exec **cmds_list)
{
	close(data->last_heredoc_fd);
	perror((*cmds_list)->files_info->infile_info->final_name);
	store_or_free(NULL, NULL, false, true);
	exit(1);
}

void	infile_problem(t_data *data, t_exec **cmds_list)
{
	close(data->last_heredoc_fd);
	perror((*cmds_list)->files_info->infile_info->name);
	store_or_free(NULL, NULL, false, true);
	exit(1);
}

void	control_normal_infile(t_data *data, t_exec **cmds_list)
{
	int	infile_exist;

	infile_exist = open((*cmds_list)->files_info->infile_info->name, O_RDONLY);
	if (infile_exist < 0)
		infile_problem(data, cmds_list);
	else
		(*cmds_list)->infile = infile_exist;
}

void	control_outfile(t_exec **cmds_list, int flags)
{
	int	outfile_exist;

	outfile_exist = open((*cmds_list)->files_info->outfile_info->name, flags,
			0644);
	if (outfile_exist < 0)
		outfile_problem(cmds_list);
	else
		(*cmds_list)->outfile = outfile_exist;
}

void	outfile_problem(t_exec **cmds_list)
{
	perror((*cmds_list)->files_info->outfile_info->name);
	store_or_free(NULL, NULL, false, true);
	exit(1);
}
