/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/23 16:03:01 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc_check(t_exec *cmds_list)
{
	char	*str;
	int		fd;

	fd = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (1)
	{
		str = readline("> ");
		if (!str)
			perror("read string problem");
		if (ft_strncmp(str, cmds_list->files_info->infile_info->name, 10) == 0)
		{
			free(str);
			break ;
		}
		write(fd, str, ft_strlen(str));
		write(fd, "\n", 1);
		free(str);
	}
}

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
