/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/20 12:54:37 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getfile(t_exec **cmds_list)
{
	int		flags;
	t_fdata	*infile_info;

	infile_info = (*cmds_list)->files_info->infile_info;
	if ((*cmds_list)->files_info->infile_info->type == HEREDOC)
	{
		call_heredoc((*cmds_list));
	}
	else if ((*cmds_list)->files_info->infile_info->type == INREDIR)
	{
		if (infile_info->rights == 6)
			(*cmds_list)->infile = open(infile_info->name, O_RDONLY);
		else
			return (perror((*cmds_list)->files_info->infile_info->name), 0);
	}
	if ((*cmds_list)->files_info->outfile_info->type == APPENDREDIR)
		flags = O_RDWR | O_APPEND | O_CREAT;
	else if ((*cmds_list)->files_info->outfile_info->type == OUTREDIR)
		flags = O_WRONLY | O_TRUNC | O_CREAT;
	else
		return (1);
	(*cmds_list)->outfile = open((*cmds_list)->files_info->outfile_info->name,
			flags, 0644);
	return (1);
}

void	close_pipe_files(t_exec *cmds_list)
{
	while (cmds_list != NULL)
	{
		if (cmds_list && cmds_list->prev)
		{
			if (cmds_list->prev->pipe_fdi >= 0)
				close(cmds_list->prev->pipe_fdi);
			if (cmds_list->prev->pipe_fdo >= 0)
				close(cmds_list->prev->pipe_fdo);
		}
		cmds_list = cmds_list->next;
	}
}

void	pipe_init(t_data *pipe_info, t_exec *cmds_list, int i, t_data *data)
{
	int	fd[2];

	if (data->num_pipe < 1)
		return ;
	else
	{
		if (i < pipe_info->total_cmds - 1)
		{
			if (pipe(fd) == -1)
				perror("Pipe");
			cmds_list->pipe_fdi = fd[0];
			cmds_list->pipe_fdo = fd[1];
		}
		else
			return ;
	}
}

void	redirection(t_exec *cmds_list, t_data *pipe_info, int i)
{
	printf("Redirection called\n");
	if (!cmds_list || !pipe_info)
		perror("cmds_list or pipe_info is NULL\n");
	if (pipe_info->total_cmds == 1)
	{
		only_redirection(&cmds_list);
		return ;
	}
	else if (i == 0)
		first_cmd(cmds_list);
	else if (i == pipe_info->total_cmds - 1)
		last_cmd(cmds_list);
	else
		middle_cmd(cmds_list);
}
