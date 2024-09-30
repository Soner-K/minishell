/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 14:40:26 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/29 18:23:21 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define UNCLOSED_QUOTES_ERR_MESSAGE "minishell: syntax error: unclosed quotes\n"

/**
 * @brief Checks if there are unclosed quotes in the tokens' list.
 * @param head A pointer to the head of the tokens' list.
 * @returns True (1) if there is no unclosed quotes, and false (0) otherwise.
 */
static __int8_t	check_if_closed_quotes(t_tokens *head)
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
			return (printf("%s", UNCLOSED_QUOTES_ERR_MESSAGE), false);
		head = head->next;
	}
	return (true);
}

/**
 * @brief Mark the quotes to remove.
 * @param head A pointer to the head of the tokens' list.
 * @returns void.
 */
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
		if (quote_to_mark == 0 && (*str == '\'' || *str == '"'))
		{
			quote_to_mark = *str;
			*str = -(*str);
		}
		else if (quote_to_mark != 0 && *str == quote_to_mark)
		{
			*str = -(*str);
			head->quotes = quote_to_mark;
			quote_to_mark = 0;
		}
		str++;
	}
	mark_quotes(head->next);
}

/**
 * @brief Helper function for quotes_remover.
 * @param node Pointer to the node in which the marked quotes are removed.
 * @param quotes_count The number of quotes to remove.
 * @returns SUCCESS (1) if the removing worked 
 * or ALLOCATION_FAILURE (-1) otherwise.
 */
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

/**
 * @brief Remove marked quotes from the tokens' list.
 * @param head A pointer to the head of the tokens' list.
 * @returns SUCCESS (1) if the removing worked 
 * or ALLOCATION_FAILURE (-1) otherwise.
 */
static __int8_t	quotes_remover(t_tokens *head)
{
	short int	quotes_count;

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

/**
 * @brief Handles quotes in the tokens list given an instruction.
 * @param head A pointer to the head of the tokens list.
 * @param mode The instruction to do.
 * @returns SUCCESS (1) if the check or action worked, and FAILURE (0)
 * otherwise.
 */
__int8_t	quotes_handler(t_tokens *head, __int8_t mode)
{
	if (mode == CLOSED_QUOTES_CHECK)
		return (check_if_closed_quotes(head));
	if (mode == QUOTES_MARKING_MODE)
		return (mark_quotes(head), SUCCESS);
	if (mode == QUOTES_REMOVING_MODE)
		return (quotes_remover(head));
	return (SUCCESS);
}
