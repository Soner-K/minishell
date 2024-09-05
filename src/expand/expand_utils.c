/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:03:00 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/03 19:22:29 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks if there is an expand inside single quotes. If it is,
 * the variable isn't expanded.
 * @param str The string to check.
 * @returns True (1) if the expand isn't inside single quotes 
 * and false (0) otherwise.
 */
bool	expand_inside_single_quotes(char *str)
{
	short int	quotes_count;
	short int	i;

	if (!str)
		return (true);
	quotes_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && quotes_count % 2 == 0)
			return (false);
		if (str[i] == '\'')
			quotes_count++;
		i++;
	}
	return (true);
}

/**
 * @brief Checks if the first character of an expand variable is valid
 * (alphabetical char, underscore or a '?') or if the checked character is
 * the end of the variable name (i.e. different from an alphanumerical char,
 * an underscore and a '?').
 * @param c The character to check.
 * @param first_char A boolean taking the value 1 if the first character
 * of the expand variable is being checked, and 0 otherwise.
 * @returns True (1) if the character is a valid first character
 * and false (0) otherwise. For the other characters, returns true (1)
 * if the character is not alphanumerical, an underscore and not '?'.
 * Returns false (0) otherwise.
 * 
 */
bool	check_if_edge_characters(char c, bool first_char)
{
	if (first_char == true)
	{
		if (ft_isalpha(c) || c == '_' || c == '?')
			return (true);
		return (false);
	}
	if ((!ft_isalnum(c) && c != '_') || (c == '?'))
		return (true);
	return (false);
}

/*
When this function is called, there must be a $ in str (i.e. no need to check
outside of the first loop if a dollar sign is found).
*/

/**
 * @brief Checks the syntax of an expand variable. First character of the
 * variable's name must be either an underscore, an alphabetic character
 * or a ?. Last character must be different from an alphanumerical character
 * and an underscore.
 * @param str The string to check, which contains a '$'.
 * @param start A pointer to a short int storing the index of the variables's
 * first character.
 * @param end A pointer to a short int storing the index of the variables's
 * last character.
 * @returns True (1) if the expand syntax is valid, whether the
 * variable exists or not. Returns false (0) if the first character of the
 * expand isn't valid.
 */
bool	check_expand_syntax(char *str, short int *start, short int *end)
{
	short int	i;

	i = -1;
	*start = 0;
	*end = 0;
	while (str[++i])
	{
		if (str[i] == '$')
			break ;
	}
	*start = ++i;
	if (!check_if_edge_characters(str[i], true))
		return (false);
	while (str[++i])
	{
		if (check_if_edge_characters(str[i], false))
			break ;
	}
	*end = --i;
	return (true);
}
