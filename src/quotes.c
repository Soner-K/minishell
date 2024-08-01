/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:40:26 by sokaraku          #+#    #+#             */
/*   Updated: 2024/08/01 17:42:23 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mark_quotes(t_tokens *head)
{
	char	*str;
	char	quote_to_mark;

	if (!head)
		return ;
	str = head->word;
	quote_to_mark = 0;
	while (*str)
	{
		if (!quote_to_mark && (*str == '\'' || *str == '"'))
			quote_to_mark = *str;
		if (quote_to_mark && *str == quote_to_mark)
		{
			*str = -(*str);
			head->contain_quotes = true;
		}
		str++;
	}
	mark_quotes(head->next);
}

// is there a need to null terminate the string if calloc was used ?
static __int8_t	quotes_remover_helper(t_tokens *node, short int quotes_count)
{
	char		*new;
	short int	size;
	short int	i;
	short int	j;

	size = ft_strlen(node->word) - quotes_count + 1;
	new = ft_calloc(size, sizeof(char));
	if (!new)
		return (ALLOCATION_FAILURE);
	i = 0;
	j = 0;
	while (i < size)
	{
		if (node->word[j] != -39 && node->word[j] != -34)
		{
			new[i] = node->word[j];
			i++;
		}
		j++;
	}
	free(node->word);
	node->word = new;
	return (SUCCESS);
}

// think about error codes
__int8_t	quotes_remover(t_tokens *head)
{
	short int quotes_count;

	if (!head)
		return (false);
	mark_quotes(head);
	while (head)
	{
		if (head->contain_quotes == false)
		{
			head = head->next;
			continue ;
		}
		quotes_count = count_char(head->word, -39) +
		count_char(head->word, -34);
		if (quotes_remover_helper(head, quotes_count) == ALLOCATION_FAILURE)
			return (ALLOCATION_FAILURE);
		head = head->next;
	}
	return (SUCCESS);
}