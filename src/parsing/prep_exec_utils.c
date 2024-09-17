/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:16:08 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/17 15:05:04 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a new node of type t_exec.
 * @return t_exec* The new node.
 */
t_exec	*new_node_exec(void)
{
	t_fdata	*infile_info;
	t_fdata	*outfile_info;
	t_exec	*exec_node;
	t_files	*files;

	exec_node = malloc(sizeof(t_exec));
	infile_info = malloc(sizeof(t_fdata));
	outfile_info = malloc(sizeof(t_fdata));
	files = malloc(sizeof(t_files));
	if (!exec_node || !infile_info || !outfile_info || !files)
		return (NULL);
	infile_info->name = NULL;
	infile_info->type = NONE;
	infile_info->rights = 0;
	outfile_info->name = NULL;
	outfile_info->type = NONE;
	outfile_info->rights = 0;
	files->infile_info = infile_info;
	files->outfile_info = outfile_info;
	exec_node->builtin = false;
	exec_node->path = NULL;
	exec_node->cmd_array = NULL;
	exec_node->next = NULL;
	exec_node->prev = NULL;
	exec_node->files_info = files;
	exec_node->old_infile = -1; 
	exec_node->old_outfile = -1;
	exec_node->id_cmd = -1;
	return (exec_node);
}

/**
 * @brief Adds a new node to the end of the list.
 * @param head A double pointer to the head of the list.
 * @param add The node to add.
 */
void	lst_addback_exec(t_exec **head, t_exec *add)
{
	t_exec	*tmp;

	if (!(*head))
	{
		*head = add;
		return ;
	}
	tmp = *head; //COME BACK if no add, return error ?
	while ((tmp->next))
		tmp = tmp->next;
	tmp->next = add;
	add->prev = tmp;
	add->next = NULL;
}

/**
 * @brief Frees the nodes of the list.
 * @param head A pointer to the head of the list.
 */
void	free_exec_nodes(t_exec *head)
{
	t_exec *tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->files_info->infile_info);
		free(tmp->files_info->outfile_info);
		free(tmp->files_info);
		free(tmp);
	}
}

t_data	*set_data_struct(t_tokens *tokens)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->exit_status = 0;
	data->pids = NULL;
	data->limiter = NULL;
	data->total_cmds = 0;
	data->counter = 0;
	data->num_pipe = 0;
	while (tokens)
	{
		if (tokens->type == PIPE)
			data->num_pipe++;
		tokens = tokens->next;
	}
	data->total_cmds = data->num_pipe + 1;
	return (data);
}
