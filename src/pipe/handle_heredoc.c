
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:03:52 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/27 20:57:19 by sumseo           ###   ########.fr       */
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
	int i;

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
	while (i < data->total_hd && *exec_list != NULL)
	{
		open_heredoc(*exec_list, i, data);
		if ((*exec_list)->next != NULL
			&& (*exec_list)->next->files_info->infile_info->is_heredoc)
		{
			// There are more herdocs so I have to pass current infile to next infile
			// (*exec_list)->next->infile = data->fd_hd[i - 1];
			printf("NEXT IS HEREDOC ???? \n");
			(*exec_list)->infile = data->fd_hd[i];
		}
		if ((*exec_list)->next == NULL
			&& (*exec_list)->files_info->infile_info->is_heredoc)
		{ // There are no more heredocs,
			// so I have to change this heredoc input as normal input file
			printf("LAST IS HEREDOC ???? \n");
			printf("YO %d\n", data->fd_hd[i]);
			(*exec_list)->infile = data->fd_hd[i];
			(*exec_list)->files_info->infile_info->is_heredoc = 0;
			(*exec_list)->files_info->infile_info->type = INREDIR;
			(*exec_list)->files_info->infile_info->name = (*exec_list)->files_info->infile_info->del;
		}
		exec_list = &(*exec_list)->next;
		i++;
	}
	free_hd_files(data->hd_files);
	free(data->fd_hd);
}