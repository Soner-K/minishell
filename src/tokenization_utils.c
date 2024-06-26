/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:56:05 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/26 09:41:25 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_one_token(t_tokens *node)
{
	free(node->word);
	free(node);
}
/**
 * @brief Free a list of tokens.
 * @param head The head of the tokens' list.
 * @returns void.
 */
void	free_tokens(t_tokens *head)
{
	t_tokens	*tmp;

	if (!head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		free_one_token(tmp);
	}
}

/**
 * @brief Retrieves the address of the last node of a tokens list.
 * @param lst Pointer to a node of the tokens list.
 * @returns The address of the last node of a tokens list.
 */
t_tokens	*last_token(t_tokens *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/**
 * @brief Adds a node to the end of a tokens' list.
 * @param lst A double pointer to a node of the tokens list.
 * @param to_add The node to add.
 * @returns void
 */
__int8_t	add_token(t_tokens **lst, t_tokens *to_add)
{
	if (!(*lst))
	{
		*lst = to_add;
		to_add->type = find_token_type(to_add->word);
		return (1);
	}
	if (!to_add)
		return (-1);
	to_add->prev = last_token(*lst);
	last_token(*lst)->next = to_add;
	to_add->type = find_token_type(to_add->word);
	return (1);
}
