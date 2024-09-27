/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:03:52 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/27 19:12:34 by sumseo           ###   ########.fr       */
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
		if (current->files_info->infile_info->type == HEREDOC)
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
void	create_hd_files(t_exec *exec_list, t_data *data)
{
	t_exec	*cur_list;

	cur_list = exec_list;
	(void)data;
	while (cur_list)
	{
		// Check if cur_list->cmd_array is not NULL before accessing it
		if (cur_list->cmd_array)
		{
			if (cur_list->cmd_array[0])
				printf("CURRENT COMMAND CHECK %s\n", cur_list->cmd_array[0]);
			else
				printf("NO COMMAND\n");
		}
		else
		{
			printf("cmd_array is NULL\n");
		}
		cur_list = cur_list->next; // Move to the next command in the list
	}
}

void	launch_heredoc(t_exec **exec_list, t_data *data, char **env_copy,
		t_env **env_list)
{
	int	i;

	(void)exec_list;
	(void)env_copy;
	(void)env_list;
	data->total_hd = heredoc_count(*exec_list);
	i = 0;
	if (data->total_hd == 0)
		return ;
	data->fd_hd = malloc(sizeof(int) * data->total_hd);
	if (!data->fd_hd)
		return ;
	data->hd_files = init_hd_files(data);
	if (!data->hd_files)
		return ;
	while (i < data->total_hd)
	{
		printf("Each file name %s\n", data->hd_files[i]);
		i++;
	}
	// create_hd_files(*exec_list, data);
	while (i < data->total_hd && *exec_list != NULL)
	{
		open_heredoc(*exec_list);
		// printf("current heredoc infile %d\n", (*exec_list)->infile);
		exec_list = &(*exec_list)->next;
		i++;
	}
}
