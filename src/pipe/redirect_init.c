/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_init.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/06 16:13:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/14 18:32:25 by sumseo           ###   ########.fr       */
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
		if (ft_strncmp(str, cmds_list->files_info->infile, 10) == 0)
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
	(void)cmds_list;
	// if ((*cmds_list)->files_info->infile)
	// {
	// 	dup2((*cmds_list)->files_info->infile, STDIN_FILENO);
	// 	close((*cmds_list)->files_info->infile);
	// }
	// if ((*cmds_list)->files_info->outfile)
	// {
	// 	dup2((*cmds_list)->files_info->outfile, STDOUT_FILENO);
	// 	close((*cmds_list)->files_info->outfile);
	// }
}

void	first_cmd(t_exec *cmds_list)
{
	(void)cmds_list;
	// if (cmds_list->files_info->rights_infile)
	// {
	// 	dup2(cmds_list->files_info->infile, STDIN_FILENO);
	// 	close(cmds_list->files_info->infile);
	// }
	// if (cmds_list->files_info->outfile)
	// {
	// 	dup2(cmds_list->files_info->outfile, STDOUT_FILENO);
	// 	close(cmds_list->files_info->outfile);
	// }
	// else
	// 	dup2(cmds_list->pipe_fdo, STDOUT_FILENO);
	// close(cmds_list->pipe_fdo);
	// close(cmds_list->pipe_fdi);
}

void	last_cmd(t_exec *cmds_list)
{
	(void)cmds_list;
	// if (cmds_list->files_info->outfile)
	// {
	// 	dup2(cmds_list->files_info->outfile, STDOUT_FILENO);
	// 	close(cmds_list->files_info->outfile);
	// }
	// if (cmds_list->files_info->rights_infile)
	// {
	// 	dup2(cmds_list->files_info->infile, STDIN_FILENO);
	// 	close(cmds_list->files_info->infile);
	// }
	// else
	// {
	// 	dup2(cmds_list->prev->pipe_fdi, STDIN_FILENO);
	// }
	// close(cmds_list->prev->pipe_fdi);
}

void	middle_cmd(t_exec *cmds_list)
{
	(void)cmds_list;
	// if (cmds_list->files_info->rights_infile)
	// {
	// 	dup2(cmds_list->files_info->infile, STDIN_FILENO);
	// 	close(cmds_list->files_info->infile);
	// }
	// else
	// {
	// 	dup2(cmds_list->prev->pipe_fdi, STDIN_FILENO);
	// }
	// if (cmds_list->files_info->outfile)
	// {
	// 	dup2(cmds_list->files_info->outfile, STDOUT_FILENO);
	// 	close(cmds_list->files_info->outfile);
	// }
	// else
	// {
	// 	dup2(cmds_list->pipe_fdo, STDOUT_FILENO);
	// }
	// close(cmds_list->pipe_fdi);
	// close(cmds_list->pipe_fdo);
	// close(cmds_list->prev->pipe_fdi);
	// close(cmds_list->prev->pipe_fdo);
}
