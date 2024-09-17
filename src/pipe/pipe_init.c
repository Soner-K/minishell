/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/22 17:59:43 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/17 10:39:49 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	getfile(t_exec **cmds_list)
{
	printf("Check (*cmds_list)->files_info->infile_info->type: %d\n",
		(*cmds_list)->files_info->infile_info->type);
	printf("Check (*cmds_list)->files_info->infile_info->name: %s\n",
		(*cmds_list)->files_info->infile_info->name);
	printf("Check (*cmds_list)->files_info->infile_info->rights: %hd\n",
		(*cmds_list)->files_info->infile_info->rights);
	printf("Check (*cmds_list)->files_info->outfile_info->type: %d\n",
		(*cmds_list)->files_info->outfile_info->type);
	printf("Check (*cmds_list)->files_info->outfile_info->name: %s\n",
		(*cmds_list)->files_info->outfile_info->name);
	printf("Check (*cmds_list)->files_info->outfile_info->rights: %hd\n",
		(*cmds_list)->files_info->outfile_info->rights);
	if ((*cmds_list)->files_info->infile_info->type == HEREDOC)
		call_heredoc((*cmds_list));
	else if ((*cmds_list)->files_info->infile_info->type == INREDIR)
	{
		if ((*cmds_list)->files_info->infile_info->rights == 6)
		{
			printf("YIIII\n");
			(*cmds_list)->infile = open((*cmds_list)->files_info->infile_info->name,
					O_RDONLY);
		}
		else
		{
			perror((*cmds_list)->files_info->infile_info->name);
			return (0);
		}
	}
	if ((*cmds_list)->files_info->infile_info->type == APPENDREDIR)
		(*cmds_list)->outfile = open((*cmds_list)->files_info->outfile_info->name,
				O_RDWR | O_APPEND, 0644);
	else if ((*cmds_list)->files_info->outfile_info->type != NONE)
	{
		if ((*cmds_list)->files_info->outfile_info->type
			&& !(*cmds_list)->files_info->outfile_info->name)
		{
			printf("H??\n");
			perror((*cmds_list)->files_info->outfile_info->name);
			return (0);
		}
		else if ((*cmds_list)->files_info->outfile_info->type == OUTREDIR)
			(*cmds_list)->outfile = open((*cmds_list)->files_info->outfile_info->name,
					O_WRONLY | O_TRUNC | O_CREAT, 0644);
	}
	return (1);
}

void	close_pipe_files(t_exec *cmds_list)
{
	while (cmds_list != NULL)
	{
		if (cmds_list && cmds_list->prev)
		{
			if (cmds_list->prev->pipe_fdi >= 0)
				close(cmds_list->prev->pipe_fdi);
			if (cmds_list->prev->pipe_fdo >= 0)
				close(cmds_list->prev->pipe_fdo);
		}
		cmds_list = cmds_list->next;
	}
}

void	wait_pipe_files(t_data *pipe_info)
{
	int	i;
	int	status;

	i = 0;
	status = 123;
	while (i < pipe_info->total_cmds)
	{
		waitpid(pipe_info->pids[i], &status, 0);
		i++;
	}
}

void	pipe_init(t_data *pipe_info, t_exec *cmds_list, int i, t_data *data)
{
	int	fd[2];

	if (data->num_pipe < 1)
		return ;
	else
	{
		if (i < pipe_info->total_cmds - 1)
		{
			if (pipe(fd) == -1)
				perror("Pipe");
			cmds_list->pipe_fdi = fd[0];
			cmds_list->pipe_fdo = fd[1];
		}
		else
			return ;
	}
}

void	redirection(t_exec *cmds_list, t_data *pipe_info, int i)
{
	if (!cmds_list || !pipe_info)
		perror("cmds_list or pipe_info is NULL\n");
	if (pipe_info->total_cmds == 1)
	{
		only_redirection(&cmds_list);
		return ;
	}
	else if (i == 0)
		first_cmd(cmds_list);
	else if (i == pipe_info->total_cmds - 1)
		last_cmd(cmds_list);
	else
		middle_cmd(cmds_list);
}
