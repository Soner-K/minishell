/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:03:52 by sumseo            #+#    #+#             */
/*   Updated: 2024/10/04 15:43:42 by sumseo           ###   ########.fr       */
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
	name = ft_strjoin(".hd_", index_str);
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

void	redirect_heredoc(t_exec *cur_list, int last_heredoc_fd, t_data *data,
		char *temp_s)
{
	while (cur_list != NULL)
	{
		if (last_heredoc_fd != -1
			&& cur_list->files_info->infile_info->type != INREDIR)
		{
			cur_list->infile = last_heredoc_fd;
			cur_list->files_info->infile_info->name = data->hd_files[data->total_hd
				- 1];
		}
		if (cur_list->files_info->infile_info->type == INREDIR)
			cur_list->files_info->infile_info->name = temp_s;
		cur_list = cur_list->next;
	}
	if (last_heredoc_fd != -1)
		close(last_heredoc_fd);
}

void	launch_heredoc(t_exec **exec_list, t_data *data)
{
	int		i;
	t_exec	*cur_list;
	int		last_heredoc_fd;
	char	*temp_s;

	last_heredoc_fd = -1;
	i = 0;
	init_heredoc(exec_list, data);
	cur_list = *exec_list;
	while (i < data->total_hd && cur_list != NULL)
	{
		if (cur_list->files_info->infile_info->type == INREDIR)
			temp_s = cur_list->files_info->infile_info->name;
		if (cur_list->files_info->infile_info->is_heredoc)
		{
			open_heredoc(cur_list, i, data);
			last_heredoc_fd = data->fd_hd[i];
			heredoc_init_name(cur_list, data, i);
		}
		cur_list = cur_list->next;
		i++;
	}
	cur_list = *exec_list;
	if (data->total_hd)
		redirect_heredoc(cur_list, last_heredoc_fd, data, temp_s);
}
