/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:22:13 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/16 16:18:47 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define TOKEN_IS_PIPE -2

/**
 * @brief Assigns an id to each command in the linked list of tokens.
 * @param head The head of the linked list of tokens.
 * @returns void.
 */
void	set_id(t_tokens *head)
{
	int	id_cmd;

	id_cmd = 0;
	while (head)
	{
		if (head->type == PIPE)
		{
			head = head->next;
			id_cmd++;
		}
		else
		{
			head->id_cmd = id_cmd;
			head = head->next;
		}
	}
}

/**
 * @brief Gets the command array of a portion of the command line.
 * @param node A pointer to the current node.
 * @param id The id of the command.
 * @returns TOKEN_IS_PIPE (-2) if the token is a pipe, ALLOCATION_FAILURE (-1)
 * if the allocation failed, and SUCCESS (1) otherwise.
 */
__int8_t	get_cmd_array(t_tokens **node, int id)
{
	char		*joined_cmds;
	char		**cmd_array;
	t_tokens	*tmp;

	tmp = *node;
	joined_cmds = NULL;
	if (tmp->type == PIPE)
		return (TOKEN_IS_PIPE);
	while (tmp && (tmp->id_cmd != -1 && tmp->id_cmd == id))
	{
		if (tmp->type != WORD && tmp->type != CMD && tmp->type != BUILTIN)
		{
			tmp = tmp->next;
			continue ;
		}
		joined_cmds = merge_strings(joined_cmds, tmp->word, -32);
		if (!joined_cmds)
			return (ALLOCATION_FAILURE);
		tmp = tmp->next;
	}
	cmd_array = ft_split(joined_cmds, -32);
	if (!cmd_array)
		return (free(joined_cmds), ALLOCATION_FAILURE);
	while ((*node) && ((*node)->type != CMD && (*node)->type != BUILTIN))
		*node = (*node)->next;
	if (*node)
		(*node)->cmd_array = cmd_array;
	while (*node && *node != tmp)
		*node = (*node)->next;
	free(joined_cmds);
	return (SUCCESS);
}

/**
 * @brief Iterates through the linked list of tokens and assigns a command
 * array to each command.
 * @param head A double pointer to the head of the linked list of tokens.
 * @returns void.
 */
__int8_t	set_cmds_arrays(t_tokens **head)
{
	t_tokens	*first;
	__int8_t	ret;

	first = *head;
	ret = SUCCESS;
	set_id(*head);
	while (*head)
	{
		ret = get_cmd_array(head, (*head)->id_cmd);
		if (ret == TOKEN_IS_PIPE)
			*head = (*head)->next;
		else if (ret == ALLOCATION_FAILURE)
			return (FAILURE); // COME BACK
	}
	*head = first;
	return (SUCCESS);
}
