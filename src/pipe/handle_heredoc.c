/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:03:52 by sumseo            #+#    #+#             */
/*   Updated: 2024/10/02 15:40:53 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_count(t_exec *exec)
{
	int		count;
	t_exec	*current;

	count = 0;
	current = exec;
	while (current)
	{
		if (current->files_info->infile_info->is_heredoc)
			count++;
		current = current->next;
	}
	return (count);
}

char	*get_file_name(int i)
{
	char	*name;
	char	*index_str;

	index_str = ft_itoa(i);
	if (!index_str)
		return (NULL);
	name = ft_strjoin("hd_", index_str);
	free(index_str);
	return (name);
}

char	**init_hd_files(t_data *data)
{
	char	**hd_files;
	int		i;

	hd_files = malloc(sizeof(char *) * (data->total_hd + 1));
	if (!hd_files)
		return (NULL);
	i = 0;
	while (i < data->total_hd)
	{
		hd_files[i] = get_file_name(i);
		if (!hd_files[i])
		{
			while (i-- > 0)
				free(hd_files[i]);
			free(hd_files);
			return (NULL);
		}
		i++;
	}
	hd_files[i] = NULL;
	return (hd_files);
}

void	free_hd_files(char **hd_files)
{
	int	i;

	i = 0;
	while (hd_files[i])
	{
		free(hd_files[i]);
		i++;
	}
	free(hd_files);
}
void	launch_heredoc(t_exec **exec_list, t_data *data)
{
	int		i;
	t_exec	*cur_list;
	int		last_heredoc_fd;

	last_heredoc_fd = -1;
	data->total_hd = heredoc_count(*exec_list);
	i = 0;
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
	cur_list = *exec_list;
	printf("Total heredocs: %d\n", data->total_hd);
	while (i < data->total_hd && cur_list != NULL)
	{
		if (cur_list->files_info->infile_info->is_heredoc)
		{
			open_heredoc(cur_list, i, data);
			last_heredoc_fd = data->fd_hd[i];
			cur_list->files_info->infile_info->name = data->hd_files[i];
			cur_list->files_info->infile_info->rights = 6;
			if (i > 0 && data->fd_hd[i - 1] != -1)
				close(data->fd_hd[i - 1]);
		}
		cur_list = cur_list->next;
		i++;
	}
	cur_list = *exec_list;
	while (cur_list != NULL)
	{
		if (last_heredoc_fd != -1
			&& cur_list->files_info->infile_info->type != INREDIR)
		{
			cur_list->infile = last_heredoc_fd;
			cur_list->files_info->infile_info->name = data->hd_files[data->total_hd
				- 1];
		}
		cur_list = cur_list->next;
	}
	if (last_heredoc_fd != -1)
		close(last_heredoc_fd);
}
