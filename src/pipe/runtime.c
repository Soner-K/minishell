/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:07:40 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/16 14:07:47 by sumseo           ###   ########.fr       */
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

t_data	*init_pipeinfo(t_exec *cmds_list)
{
	t_data	*pipe_info;

	pipe_info = malloc(sizeof(t_data));
	if (pipe_info == NULL)
		pipe_null_check();
	pipe_info->total_cmds = count_cmds(cmds_list);
	printf("total_cmds%d\n", pipe_info->total_cmds);
	return (pipe_info);
}

void	close_extra_files(t_exec *cmds_list)
{
	if (cmds_list->next != NULL)
		close(cmds_list->pipe_fdo);
	if (cmds_list->prev != NULL)
	{
		close(cmds_list->prev->pipe_fdi);
	}
}

void	close_files(t_exec *cmds_list)
{
	(void)cmds_list;
	// if (cmds_list->files_info->infile)
	// 	close(cmds_list->files_info->infile);
	// if (cmds_list->outfile_access)
	// 	close(cmds_list->outfile);
}

void	runtime_shell(t_exec *cmds_list, char **env_copy, t_data *data,
		t_env **env_list)
{
	pid_t	fork_id;
	int		i;
	t_exec	*head;

	head = cmds_list;
	i = 0;
	data = init_pipeinfo(cmds_list);
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
					printf("check if it is not builtin\n");
					redirection(cmds_list, data, i);
					exec_builtin(which_builtin(cmds_list), &cmds_list,
						env_list);
				}
				else
					init_child_pipe(cmds_list, data, env_copy, i);
			}
			else
				close_no_file(cmds_list);
		}
		close_extra_files(cmds_list);
		i++;
		cmds_list = cmds_list->next;
	}
	close_parent(head, data);
}
