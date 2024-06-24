/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:25:38 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/24 15:28:58 by sokaraku         ###   ########.fr       */
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
t_tokens	*new_token(char *word, bool is_head)
{
	t_tokens			*new;
	static t_tokens	*head = NULL;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->word = word;
	new->path = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->type = NONE;
	if (is_head)
		head = new;
	new->head = head;
	return (new);
}

t_cmds	*new_cmd(bool is_head)
{
	t_cmds			*new;
	static t_cmds	*head = NULL;

	new = malloc(sizeof(t_cmds));
	if (!new)
		return (NULL);
	new->next = NULL;
	new->cmd = NULL;
	new->file_redir = NULL;
	new->redirection = 0;
	if (is_head)
		head = new;
	new->head = head;
	return (new);
}