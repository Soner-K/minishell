/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:16:08 by sokaraku          #+#    #+#             */
/*   Updated: 2024/10/04 21:45:28 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	initialize_node(t_exec **node, t_exec *tmp)
{
	tmp = *node;
	tmp->files_info->infile_info->is_heredoc = false;
	tmp->files_info->infile_info->rights = 0;
	tmp->files_info->infile_info->type = NONE;
	tmp->files_info->infile_info->name = NULL;
	tmp->files_info->infile_info->del = NULL;
	tmp->files_info->outfile_info->is_heredoc = false;
	tmp->files_info->outfile_info->rights = 0;
	tmp->files_info->outfile_info->type = NONE;
	tmp->files_info->outfile_info->name = NULL;
	tmp->files_info->outfile_info->del = NULL;
	tmp->builtin = false;
	tmp->path = NULL;
	tmp->cmd_array = NULL;
	tmp->next = NULL;
	tmp->prev = NULL;
	tmp->old_stdin = -1;
	tmp->old_stdout = -1;
	tmp->infile = -1;
	tmp->outfile = -1;
	tmp->pipe_fdo = -1;
	tmp->pipe_fdi = -1;
	tmp->old_infile = -1;
	tmp->old_outfile = -1;
	tmp->data = NULL;
}

/**
 * @brief Creates a new node of type t_exec.
 * @return The new node.
 */
t_exec	*new_node_exec(void)
{
	t_fdata	*infile_info;
	t_fdata	*outfile_info;
	t_exec	*exec;
	t_files	*files;

	exec = malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	infile_info = malloc(sizeof(t_fdata));
	if (!infile_info)
		return (free(exec), NULL);
	outfile_info = malloc(sizeof(t_fdata));
	if (!outfile_info)
		return (free(exec), free(infile_info), NULL);
	files = malloc(sizeof(t_files));
	if (!files)
		return (free(exec), free(infile_info), free(outfile_info), NULL);
	exec->files_info = files;
	infile_info->final_name = NULL;
	outfile_info->final_name = NULL;
	files->infile_info = infile_info;
	files->outfile_info = outfile_info;
	initialize_node(&exec, NULL);
	return (exec);
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
	tmp = *head;
	while ((tmp->next))
		tmp = tmp->next;
	tmp->next = add;
	add->prev = tmp;
	add->next = NULL;
}

/**
 * @brief Sets the data structure and stores it in the execution's node.
 * @param tokens A pointer to the head of the tokens' list.
 * @param exec A pointer to the head of the execution's list.
 * @param env_list A pointer to the head of the environment list.
 * @returns The data structure.
 */
t_data	*set_data_struct(t_tokens *tokens, t_exec *exec, t_env *env_list)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (free_tokens(tokens, false), free_exec(exec, true),
			free_env_list(env_list), exit(EXIT_FAILURE), NULL);
	data->limiter = NULL;
	data->total_cmds = 0;
	data->num_pipe = 0;
	data->hd_files = NULL;
	data->last_heredoc_fd = -1;
	while (tokens)
	{
		if (tokens->type == PIPE)
			data->num_pipe++;
		tokens = tokens->next;
	}
	data->total_cmds = data->num_pipe + 1;
	while (exec)
	{
		exec->data = data;
		exec = exec->next;
	}
	return (data->env_list = env_list, data->fd_hd = 0, data->total_hd = 0,
		data->counter = 0, data->pids = NULL, data->exit_status = 0, data);
}

/**
 * @brief Fucking norm
 */
void	all_my_homies_hate_the_norm(t_tokens **head, t_exec *itr, int id_cmd)
{
	while (*head && (*head)->id_cmd == -1)
		*head = (*head)->next;
	while (*head && (*head)->id_cmd == id_cmd)
	{
		if ((*head)->type >= INREDIR && (*head)->type <= APPENDREDIR)
			set_files_info(itr->files_info, *head);
		else
			set_node_exec(itr, *head, id_cmd);
		*head = (*head)->next;
	}
}
