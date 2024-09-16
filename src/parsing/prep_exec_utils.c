/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 19:16:08 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/12 20:33:06 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Creates a new node of type t_exec.
 * @return t_exec* The new node.
 */
t_exec	*new_node_exec(void)
{
	t_files	*files_info;
	t_exec	*exec_node;

	exec_node = malloc(sizeof(t_exec));
	files_info = malloc(sizeof(t_files));
	if (!exec_node || !files_info)
		return (NULL);
	exec_node->builtin = false;
	exec_node->path = NULL;
	exec_node->cmd_array = NULL;
	exec_node->next = NULL;
	exec_node->files_info = files_info;
	files_info->is_heredoc = false;
	files_info->infile = NULL;
	files_info->outfile = NULL;
	files_info->rights_infile = 0;
	files_info->rights_outfile = 0;
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
	tmp = *head;
	while ((tmp->next))
		tmp = tmp->next;
	tmp->next = add;
}

/**
 * @brief Frees the nodes of the list.
 * @param head A pointer to the head of the list.
 */
void	free_exec_nodes(t_exec *head)
{
	t_exec	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->files_info);
		free(tmp);
	}
}