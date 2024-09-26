/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:22:13 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/26 14:14:21 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Assigns an id to each command in the linked list of tokens.
 * @param head The head of the linked list of tokens.
 * @returns void.
 */
static void	set_id(t_tokens *head, int id_cmd)
{
	bool	met_heredoc;

	met_heredoc = false;
	while (head)
	{
		if (head->type == HEREDOC && head->next && head->next->type == HEREDOC)
		{
			met_heredoc = true;
			head->id_cmd = id_cmd;
			id_cmd++;
			head = head->next;
		}
		else if (head->type == PIPE)
		{
			head = head->next;
			id_cmd++;
			met_heredoc = false;
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
__int8_t	get_cmd_array(t_tokens **node, t_tokens *itr, int id)
{
	char		*joined_cmds;
	char		**cmd_array;

	joined_cmds = NULL;
	while (itr && (itr->id_cmd != -1 && itr->id_cmd == id))
	{
		if (itr->type != WORD && itr->type != CMD && itr->type != BUILTIN)
		{
			itr = itr->next;
			continue ;
		}
		joined_cmds = merge_strings(joined_cmds, itr->word, -32);
		if (!joined_cmds)
			return (ALLOCATION_FAILURE);
		itr = itr->next;
	}
	cmd_array = ft_split(joined_cmds, -32);
	if (!cmd_array && joined_cmds)
		return (free(joined_cmds), ALLOCATION_FAILURE);
	while ((*node) && (*node) != itr)
	{
		(*node)->cmd_array = cmd_array;
		*node = (*node)->next;
	}
	return (free(joined_cmds), SUCCESS);
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
	set_id(*head, 0);
	while (*head)
	{
		if ((*head)->type == PIPE)
		{
			*head = (*head)->next;
			continue ;
		}
		ret = get_cmd_array(head, *head, (*head)->id_cmd);
		if (ret == ALLOCATION_FAILURE)
			return (ALLOCATION_FAILURE);
	}
	*head = first;
	return (SUCCESS);
}
