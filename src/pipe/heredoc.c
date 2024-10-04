/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:15:01 by sumseo            #+#    #+#             */
/*   Updated: 2024/10/04 15:39:21 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_heredoc(char *str, int tmp)
{
	ft_putstr_fd(str, tmp);
	ft_putstr_fd("\n", tmp);
}

void	close_heredoc(t_exec *cmds_list, t_data *data, int i)
{
	close(data->fd_hd[i]);
	data->fd_hd[i] = open(data->hd_files[i], O_RDONLY);
	if (data->fd_hd[i] == -1)
	{
		perror("Error reopening heredoc file");
		return ;
	}
	cmds_list->infile = data->fd_hd[i];
	close(data->fd_hd[i]);
}

void	close_heredoc_signal(t_exec *cmds_list, t_data *data, int i)
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

void	heredoc_open_check(t_data *data, int i)
{
	data->fd_hd[i] = open(data->hd_files[i], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (data->fd_hd[i] == -1)
	{
		perror("Error opening heredoc file");
		return ;
	}
}

void	open_heredoc(t_exec *cmds_list, int i, t_data *data)
{
	char	*str;

	heredoc_open_check(data, i);
	while (1)
	{
		str = readline(">");
		if (g_signal == 2)
			close_heredoc_signal(cmds_list, data, i);
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
	close_heredoc(cmds_list, data, i);
}
