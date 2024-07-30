/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:20:21 by sokaraku          #+#    #+#             */
/*   Updated: 2024/07/30 19:04:34 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

#define VAR_NOT_FOUND -1
#define ALLOCATION_FAILURE -2
#define EXPAND_NAME_NOT_VALID -3
/*
The tokenized list should be the input for doing the expand.
{words}$VAR{word} will give one token, not multiples, so should be okay
*/

/**
 * @brief Checks if the first character of an expand variable is valid
 * (alpha char, underscore or a '?') or if the checked character is
 * the end of the variable name (i.e. different from an alphanumerical char,
 * an underscore and a '?').
 * @param c The character to check.
 * @param first_char A boolean taking the value 1 if the first character
 * of the expand variable is being checked, and 0 otherwise.
 * @returns True (1) if the character is a valid first character
 * and false (0) otherwise. For the other characters, returns true (1)
 * if the character is not alpha, numerical, an underscore and not '?'.
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
bool	check_expand_syntax(char *str, short int *start, short int *end)
{
	short int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$')
			break ;
	}
	*start = ++i;
	if (!check_if_edge_characters(str[i], true))
		return (false);
	if (str[i] != '?' && str[i] != '_' && str[++i] == '\0')
		return (false);
	while (str[++i])
	{
		if (check_if_edge_characters(str[i], false))
			break ;
	}
	*end = --i;
	return (true);
}

/*
Check thoroughly where to free
*/
char	*get_new_word(t_tokens *node, char *var, short int s, short int end)
{
	char	*str;
	int		size;

	size = ft_strlen(var) + (end - s - 2) + 1;
	str = ft_calloc(size, sizeof(char));
	if (!str)
		return (NULL);
	ft_memcpy(str, node->word, s - 1);
	size = ft_strlen(var);
	ft_memcpy(str + s - 1, var, size);
	size = ft_strlen(node->word) - end;
	ft_memcpy(str + s - 1 + ft_strlen(var), node->word + end + 1, size);
	return (str);
}

__int8_t	extract_variable(t_tokens *node)
{
	short int	start;
	short int	end;
	char		*var;
	char		*str;

	if (!check_expand_syntax(node->word, &start, &end))
		return (EXPAND_NAME_NOT_VALID);
	str = ft_substr(node->word, start, (end - start + 1));
	if (!str)
		return (ALLOCATION_FAILURE);
	var = getenv(str);
	if (!var)
		return (free(str), VAR_NOT_FOUND);
	free(str);
	str = get_new_word(node, var, start, end);
	if (!str)
		return (ALLOCATION_FAILURE);
	free(node->word);
	node->word = str;
	return (true);
}

/*
The protection in the beginning of the functions is_inside_singles_quotes
and valid_expand_syntax won't be necessary in the final version
*/

bool	is_inside_single_quotes(char *str)
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