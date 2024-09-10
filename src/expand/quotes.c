/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:40:26 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/10 12:47:23 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

__int8_t	check_if_closed_quotes(t_tokens *head)
{
	char		*str;
	short int	i;
	__int8_t	quote;

	quote = 0;
	while (head)
	{
		i = -1;
		str = head->word;
		while (str[++i])
		{
			if (str[i] == quote)
				quote = 0;
			else if (!quote && (str[i] == '\'' || str[i] == '"'))
				quote = str[i];
		}
		if (quote)
			return (false);
		head = head->next;
	}
	return (true);
}

void	mark_quotes(t_tokens *head)
{
	char	*str;
	char	quote_to_mark;

	if (!head)
		return ;
	str = head->word;
	quote_to_mark = 0;
	while (*str)
	{
		if (quote_to_mark == 0 && (*str == '\'' || *str == '"'))
			quote_to_mark = *str;
		if (quote_to_mark != 0 && *str == quote_to_mark)
		{
			*str = -(*str);
			head->quotes = quote_to_mark;
			head->n_quotes++;
		}
		str++;
	}
	mark_quotes(head->next);
}

// is there a need to null terminate the string if ft_calloc was used ? COME BACK
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
	while (i < size - 1)
	{
		if (node->word[j] && node->word[j] != -39 && node->word[j] != -34)
		{
			new[i] = node->word[j];
			i++;
		}
		j++;
	}
	new[i] = '\0';
	free(node->word);
	node->word = new;
	return (SUCCESS);
}

// think about error codes COME BACK
__int8_t	quotes_remover(t_tokens *head)
{
	short int quotes_count;

	if (!head)
		return (false);
	while (head)
	{
		if (head->quotes == false)
		{
			head = head->next;
			continue ;
		}
		quotes_count = count_char(head->word, -39) + count_char(head->word,
				-34);
		if (quotes_remover_helper(head, quotes_count) == ALLOCATION_FAILURE)
			return (ALLOCATION_FAILURE);
		head = head->next;
	}
	return (SUCCESS);
}