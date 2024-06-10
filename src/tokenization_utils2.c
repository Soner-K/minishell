/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:34:01 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/10 15:52:06 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Returns a character's token type.
 * @param c A character.
 * @returns The token type.
 */
__int8_t	find_one_token(char c)
{
	if (ft_isalnum(c) || (!is_separator(c) && c != ' ' && c != '\t'))
		return (WORD);
	else if (c == '$' || c == '?')
		return (OPERATOR);
	else if (c == ' ')
		return (SPACE_);
	else if (c == '\t')
		return (TAB_);
	else if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (INREDIR);
	else if (c == '>')
		return (OUTREDIR);
	else if (c == '"')
		return (DOUBLE_QUOTE);
	else if (c == '\'')
		return (SINGLE_QUOTE);
	return (NONE);
}

/**
 * @brief Finds the precise kind of token for a string.
 * @param str A string containing tokens of the same type.
 * @returns The token type.
 */
__int8_t	find_token_type(char *str)
{
	if (ft_strlen(str) == 1)
		return (find_one_token(*str));
	if (*str == '\'' || *str == '"')
		return (WORD);
	return (find_one_token(*str));
}

/**
 * @brief Checks if a character is a separator.
 * @param c A character.
 * @returns Returns the character's value if it is a separator,
 * and false otherwise.
 */
char	is_separator(char c)
{
	if (c == '>')
		return ('>');
	if (c == '<')
		return ('<');
	if (c == '|')
		return ('|');
	if (c == ' ')
		return (' ');
	return (false);
}