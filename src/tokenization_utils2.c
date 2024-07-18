/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization_utils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 17:34:01 by sokaraku          #+#    #+#             */
/*   Updated: 2024/07/18 14:11:56 by sokaraku         ###   ########.fr       */
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
	if (ft_isalnum(c) || (!is_separator(c) && c != ' ' && c != '\t'
			&& c != '$'))
		return (WORD);
	else if (c == '$') //$? ?
		return (EXPAND);
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
	return (NONE);
}

/**
 * @brief Finds the precise kind of token for a string.
 * @param str A string containing tokens of the same type.
 * @returns The token type.
 */
__int8_t	find_token_type(char *str)
{
	short int	len;

	len = ft_strlen(str);
	if (*str == '"' || *str == '\'')
		return (WORD);
	if (len > 1 && *str == '>')
		return (APPENDREDIR);
	else if (len > 1 && *str == '<')
		return (HEREDOC);
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
