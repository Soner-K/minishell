/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/05 16:56:05 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/07 17:37:46 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a new node tailored for a list of tokens.
 * @param word The word that will be stored in the created node.
 * @param is_head A boolean being TRUE if the created node will be the
 * head of a list, and FALSE otherwise.
 * @returns The created node.
 */
t_test	*new_token(char *word, bool is_head)
{
	t_test			*new;
	static t_test	*head = NULL;

	new = malloc(sizeof(t_test));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->prev = NULL;
	new->word = word;
	new->type = NONE;
	if (is_head)
		head = new;
	new->head = head;
	return (new);
}

/**
 * @brief Free a list of tokens.
 * @param head The head of the tokens' list.
 * @returns void.
 */
void	free_tokens(t_test *head)
{
	t_test	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->word);
		free(tmp);
	}
}

/**
 * @brief Retrieves the address of the last node of a tokens list.
 * @param lst Pointer to a node of the tokens list.
 * @returns The address of the last node of a tokens list.
 */
t_test	*last_token(t_test *lst)
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
void	add_token(t_test **lst, t_test *to_add)
{
	if (!(*lst))
	{
		*lst = to_add;
		return ;
	}
	if (!to_add)
		return ;
	last_token(*lst)->next = to_add;
	to_add->prev = last_token(*lst);
}

short int	skip_tab_spaces(char *str)
{
	short int	count;

	count = 0;
	if (!str)
		return (0);
	while (*str && (*str == ' ' || *str == '\t'))
	{
		str++;
		count++;
	}
	return (count);
}
