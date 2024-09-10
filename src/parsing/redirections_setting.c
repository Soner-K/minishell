/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirections_setting.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 15:31:20 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/10 10:49:59 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static __int8_t	check_if_redir(char *word, __int8_t type)
{
	static char	*redirections[5] = {"<", ">", "<<", ">>"};

	if (ft_strcmp(word, redirections[type]))
		return (-1);
	return (type);
}

/**
 * @brief Helper function for set_redirections.
 * If a redirection node is found, sets the following node accordingly,
 * and adjust the next and previous nodes' addresses. The current node is
 * then disregarded, since it is a redirection operator.
 * @param head A double pointer to the head of the tokenized list.
 * A double pointer is used to move the head accordingly if the first
 * node is a redirection.
 * @param curr A double pointer to the current node that is processed.
 * A double pointer is used to move curr's address in the calling function.
 * The curr node is necessarily a redirection operation ('<', '>', '>>', '<<').
 * @param next A double pointer to the node following the one that's processed.
 * A double pointer is used to move next's address in the calling function.
 * @returns void.
 */
static void	redir_helper(t_tokens **head, t_tokens **curr, t_tokens **next)
{
	bool		is_head;
	t_tokens	*prev;

	is_head = 0;
	prev = (*curr)->prev;
	if (*curr && !prev)
		is_head = 1;
	(*next)->type = (*curr)->type;
	(*next)->prev = prev;
	free_one_token(*curr);
	if (prev)
		prev->next = *next;
	else
	{
		*curr = *next;
		if (is_head)
			*head = *curr;
		return ;
	}
	*curr = (*next)->next;
	if (is_head)
		*head = *curr;
}

/**
 * @brief Processes a tokenized list, and sets the redirections in place by
 * removing and freeing redirections tokens and associating
 * subsequent ones as file, with a given redirection ('<', '>','<<' or '>>').
 *
 * N-B : when coming to this part of the program, the syntax and grammar of
 * the operators are correct.
 * @param head A double pointer to the head of the tokenized list.
 * A double pointer is used to move the head accordingly if the first
 * node is a redirection.
 * @returns void.
 */
void	set_redirections_type(t_tokens **head)
{
	t_tokens	*curr;
	t_tokens	*next;
	__int8_t	type;

	curr = *head;
	next = curr->next;
	while (next)
	{
		type = check_if_redir(curr->word, curr->type);
		if (type >= INREDIR && type < PIPE && next->type >= WORD
			&& next->type <= CMD)
			redir_helper(head, &curr, &next);
		else
			curr = curr->next;
		if (curr)
			next = curr->next;
		else
			break ;
	}
}