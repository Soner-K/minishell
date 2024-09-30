/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:15:01 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/30 11:52:28 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_heredoc(char *str, int tmp)
{
	ft_putstr_fd(str, tmp);
	ft_putstr_fd("\n", tmp);
}

void	close_heredoc(t_exec *cmds_list, int tmp)
{
	if (cmds_list->pipe_fdi != -1)
		close(cmds_list->pipe_fdi);
	if (cmds_list->pipe_fdo != -1)
		close(cmds_list->pipe_fdo);
	if (cmds_list->prev != NULL && cmds_list->prev->pipe_fdi != -1)
		close(cmds_list->prev->pipe_fdi);
	close(tmp);
	store_or_free(NULL, NULL, false, true);
	exit(130);
}

void	free_heredoc(char *str, int tmp)
{
	write_heredoc(str, tmp);
	free(str);
}

void	close_heredoc_tmp(int tmp, t_exec *cmds_list)
{
	close(tmp);
	cmds_list->infile = open("tmp", O_RDONLY, 0644);
}

void	open_heredoc(t_exec *cmds_list, int i, t_data *data)
{
	char	*str;

	printf("HEREdoc opend\n");
	data->fd_hd[i] = open(data->hd_files[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->fd_hd[i] == -1)
	{
		perror("Error opening heredoc file");
		return ;
	}
	while (1)
	{
		str = readline(">");
		if (g_signal == 2)
		{
			if (cmds_list->pipe_fdi != -1)
				close(cmds_list->pipe_fdi);
			if (cmds_list->pipe_fdo != -1)
				close(cmds_list->pipe_fdo);
			if (cmds_list->prev != NULL && cmds_list->prev->pipe_fdi != -1)
				close(cmds_list->prev->pipe_fdi);
			close(data->fd_hd[i]);
			store_or_free(NULL, NULL, false, true);
			exit(130);
		}
		if (str == NULL)
		{
			printf("heredoc delimited (`%s')\n",
				cmds_list->files_info->infile_info->name);
			break ;
		}
		if (ft_strncmp(str, cmds_list->files_info->infile_info->del,
				ft_strlen(cmds_list->files_info->infile_info->del)) == 0
			&& str[ft_strlen(cmds_list->files_info->infile_info->del)] == '\0')
		{
			free(str);
			break ;
		}
		write_heredoc(str, data->fd_hd[i]);
		free(str);
	}
	close(data->fd_hd[i]);
	data->fd_hd[i] = open(data->hd_files[i], O_RDONLY, 0644);
	if (data->fd_hd[i] == -1)
	{
		perror("Error reopening heredoc file");
		return ;
	}
	close(data->fd_hd[i]);
}
