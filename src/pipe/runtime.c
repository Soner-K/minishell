/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:07:40 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/17 13:31:44 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_child_pipe(t_exec *cmds_list, t_data *pipe_info, char **env_copy,
		int i)
{
	if (parse_path(cmds_list->cmd_array, cmds_list->path))
	{
		redirection(cmds_list, pipe_info, i);
		execve(cmds_list->path, cmds_list->cmd_array, env_copy);
		exit(0);
	}
	else
		exit(127);
}

void	close_extra_files(t_exec *cmds_list)
{
	if (cmds_list->next != NULL)
		close(cmds_list->pipe_fdo);
	if (cmds_list->prev != NULL)
		close(cmds_list->prev->pipe_fdi);
}

void	close_files(t_exec *cmds_list)
{
	if (cmds_list->files_info->infile_info->name)
		close(cmds_list->infile);
	if (cmds_list->files_info->outfile_info->type)
		close(cmds_list->outfile);
}

void	runtime_shell(t_exec *cmds_list, char **env_copy, t_data *data,
		t_env **env_list)
{
	pid_t	fork_id;
	int		i;
	t_exec	*head;

	head = cmds_list;
	i = 0;
	data->total_cmds = 4;
	data->num_pipe = 3;
	init_pid_array(data);
	while (i < data->total_cmds)
	{
		pipe_init(data, cmds_list, i, data);
		fork_id = fork();
		if (fork_id == 0)
		{
			if (getfile(&cmds_list))
			{
				if (which_builtin(cmds_list) > 0)
				{
					redirection(cmds_list, data, i);
					exec_builtin(which_builtin(cmds_list), &cmds_list,
						env_list);
				}
				else
				{
					init_child_pipe(cmds_list, data, env_copy, i);
				}
				exit(0);
			}
			else
				close_no_file(cmds_list);
		}
		store_pid(data, fork_id);
		close_extra_files(cmds_list);
		i++;
		cmds_list = cmds_list->next;
	}
	close_parent(head, data);
}
