/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/10/03 14:27:33 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	only_redirection(t_exec **cmds_list)
{
	if ((*cmds_list)->files_info->infile_info->rights)
	{
		dup2((*cmds_list)->infile, STDIN_FILENO);
		close((*cmds_list)->infile);
	}
	if ((*cmds_list)->files_info->outfile_info->rights)
	{
		dup2((*cmds_list)->outfile, STDOUT_FILENO);
		close((*cmds_list)->outfile);
	}
}

void	first_cmd(t_exec *cmds_list)
{
	if (cmds_list->files_info->infile_info->rights)
	{
		dup2(cmds_list->infile, STDIN_FILENO);
		close(cmds_list->infile);
	}
	if (cmds_list->files_info->outfile_info->rights)
	{
		dup2(cmds_list->outfile, STDOUT_FILENO);
		close(cmds_list->outfile);
	}
	else
		dup2(cmds_list->pipe_fdo, STDOUT_FILENO);
	close(cmds_list->pipe_fdo);
	close(cmds_list->pipe_fdi);
}

void	last_cmd(t_exec *cmds_list)
{
	if (cmds_list->files_info->outfile_info->rights)
	{
		dup2(cmds_list->outfile, STDOUT_FILENO);
		close(cmds_list->outfile);
	}
	if (cmds_list->files_info->infile_info->rights)
	{
		dup2(cmds_list->infile, STDIN_FILENO);
		close(cmds_list->infile);
	}
	else
		dup2(cmds_list->prev->pipe_fdi, STDIN_FILENO);
	close(cmds_list->prev->pipe_fdi);
}

void	middle_cmd(t_exec *cmds_list)
{
	if (cmds_list->files_info->infile_info->name)
	{
		dup2(cmds_list->infile, STDIN_FILENO);
		close(cmds_list->infile);
	}
	else
		dup2(cmds_list->prev->pipe_fdi, STDIN_FILENO);
	if (cmds_list->files_info->outfile_info->name)
	{
		dup2(cmds_list->outfile, STDOUT_FILENO);
		close(cmds_list->outfile);
	}
	else
		dup2(cmds_list->pipe_fdo, STDOUT_FILENO);
	close(cmds_list->pipe_fdi);
	close(cmds_list->pipe_fdo);
	close(cmds_list->prev->pipe_fdi);
	close(cmds_list->prev->pipe_fdo);
}

void	init_heredoc(t_exec **exec_list, t_data *data)
{
	data->total_hd = heredoc_count(*exec_list);
	if (data->total_hd == 0)
		return ;
	data->fd_hd = malloc(sizeof(int) * data->total_hd);
	if (!data->fd_hd)
		return ;
	data->hd_files = init_hd_files(data);
	if (!data->hd_files)
	{
		free(data->fd_hd);
		return ;
	}
}
