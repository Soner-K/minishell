/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 13:03:00 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/18 13:14:12 by sokaraku         ###   ########.fr       */
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

/**
 * @brief Removes a part of a string, starting from index start, and
 * ending at index end.
 * @param str A pointer to a string.
 * @param start Beginning index of the portion to remove.
 * @param end End index of the portion to remove.
 * @param alloc_fail Pointer to a boolean taking the value 1 (true)
 * if an allocation failure occured, and 0 (false) otherwise.
 * @returns The modified string, or NULL in case of an error.
 */
char	*ft_strslice(char *str, int start, int end, bool *alloc_fail)
{
	char	*new;
	int		size;
	int		i;
	int		j;

	if (!str || start > ft_strlen(str) || end > ft_strlen(str) || end < 0
		|| start < 0)
		return (NULL);
	size = ft_strlen(str) - (end - start) + 1;
	new = malloc(size * sizeof(char));
	if (!new)
		return (*alloc_fail = true, NULL);
	i = 0;
	j = 0;
	while (str[i] && i < start)
		new[j++] = str[i++];
	i = end + 1;
	while (str[i])
		new[j++] = str[i++];
	new[j] = '\0';
	return (new);
}

/**
 * @brief Merges two strings, replacing a part of the previous string "str",
 * with a new string "add", starting from index "start" and ending at
 * index "end".
 * @param str The original string.
 * @param add The string to add in str.
 * @param start The beginning index at which to merge the new string.
 * @param end The end index at which the merge of the new string ends.
 * @returns The new string with
 */
char	*ft_strreplace(char *str, char *add, int start, int end)
{
	char	*new;
	int		i;
	int		j;
	int		size;

	if (!str || start > ft_strlen(str) || end > ft_strlen(str) || end < 0
		|| start < 0)
		return (str); // COME BACK
	i = -1;
	j = 0;
	size = ft_strlen(str) + ft_strlen(add) + count_char(str, -34)
		+ count_char(str, -39) - (end - start - 2) + 1;
	new = malloc(size * sizeof(char));
	if (!new)
		return (NULL);
	while (str[++i] && i < start)
		new[j++] = str[i];
	i = -1;
	while (add && add[++i])
		new[j++] = -add[i];
	i = end;
	while (str[++i])
		new[j++] = str[i];
	new[j] = '\0';
	return (new);
}
