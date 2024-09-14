/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:56:05 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/12 19:14:22 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a new node tailored for a list of tokens.
 * @param word The word that will be stored in the created node.
 * @param is_head A boolean being true (1) if the created node will be the
 * head of a list, and false (0) otherwise.
 * @returns The created node.
 */
t_tokens	*new_node_token(char *word, bool is_head)
{
	t_tokens		*new;
	static t_tokens	*head = NULL;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->quotes = false;
	new->n_quotes = 0;
	new->id_cmd = -1;
	new->old_stdin = -1;
	new->old_stdout = -1;
	new->word = word;
	new->path = NULL;
	new->cmd_array = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->type = NONE;
	if (is_head)
		head = new;
	new->head = head;
	return (new);
}

/**
 * @brief Frees one token node.
 * @param node A pointer to a node of the tokens' list.
 * @returns void.
 */
void	free_one_token(t_tokens *node)
{
	free(node->word);
	if (node->path)
		free(node->path);
	if (node->cmd_array)
		free_arrs((void **)node->cmd_array);
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
