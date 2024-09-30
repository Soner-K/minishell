/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:03:00 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/29 18:26:14 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Count the number of expand(s) inside one token.
 * @param str The token.
 * @returns The number of expand(s) inside one token.
 */
short int	count_expands(char *str)
{
	short int	i;
	short int	n;

	if (!str)
		return (0);
	i = 0;
	n = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			n++;
			while (str[i] && str[i] == '$')
				i++;
		}
		else
			i++;
	}
	return (n);
}

/**
 * @brief Resets all negative ASCII characters to positive ones.
 * Negative characters are from the content of an environment variable.
 * @param head A pointer to the head of the tokens' list.
 * @returns void.
 */
void	reset_negative_characters(t_tokens *head)
{
	char	*str;
	int		i;

	while (head)
	{
		i = -1;
		str = head->word;
		while (str[++i])
		{
			if (str[i] < 0 && str[i] != -34 && str[i] != -39)
				str[i] *= -1;
		}
		head = head->next;
	}
}

bool	expand_inside_single_quotes(t_tokens *node)
{
	char		*str;
	int			i;
	__int8_t	inside;
	int			len_inside;

	str = node->word;
	i = -1;
	inside = -1;
	len_inside = 0;
	while (str[++i])
	{
		if (inside == true && str[i] != -39)
			len_inside++;
		if (str[i] == -39 && inside != true)
			inside = true;
		else if (inside == true && str[i] == -39)
		{
			inside = false;
			if (!str[i + 1] && len_inside)
				inside = true;
			len_inside = 0;
		}
	}
	return (inside >= true);
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
bool	check_expand_syntax(char *str, int *start, int *end)
{
	int	i;

	i = -1;
	*start = 0;
	*end = 0;
	while (str[++i])
	{
		if (str[i] == '$')
		{
			while (str[i] && str[i] == '$')
				i++;
			break ;
		}
	}
	*start = i;
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
