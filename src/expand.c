/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:20:21 by sokaraku          #+#    #+#             */
/*   Updated: 2024/08/01 18:26:03 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

#define EXPAND_SYNTAX_NOT_VALID -2
/*
The tokenized list should be the input for doing the expand.
{words}$VAR{word} will give one token, not multiples, so should be okay
*/

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

// __int8_t	extract_variable(t_tokens *node)
// {
// 	short int	start;
// 	short int	end;
// 	char		*var;
// 	char		*str;

// 	if (!check_expand_syntax(node->word, &start, &end))
// 		return (EXPAND_SYNTAX_NOT_VALID);
// 	str = ft_substr(node->word, start, (end - start + 1));
// 	if (!str)
// 		return (ALLOCATION_FAILURE);
// 	var = getenv(str);
// 	// if (!var)
// 	// 	return (free(str), VAR_NOT_FOUND); //no need, get_new_word will get rid of the variable in the final result
// 	free(str);
// 	str = get_new_word(node, var, start, end);
// 	if (!str)
// 		return (ALLOCATION_FAILURE);
// 	free(node->word);
// 	node->word = str;
// 	return (SUCCESS);
// }

__int8_t	extract_variable(char **str)
{
	short int	start;
	short int	end;
	char		*var;
	char		*new;

	if (!check_expand_syntax(*str, &start, &end))
		return (EXPAND_SYNTAX_NOT_VALID);
	new = ft_substr(*str, start, (end - start + 1));
	if (!new)
		return (ALLOCATION_FAILURE);
	var = getenv(str);
	// if (!var)
	// 	return (free(str), VAR_NOT_FOUND); //no need, get_new_word will get rid of the variable in the final result
	free(new);
	new = get_new_word(*str, var, start, end);
	if (!new)
		return (ALLOCATION_FAILURE);
	free(*str);
	*str = new;
}

__int8_t	extract_all(t_tokens *head)
{
	char	*str;

	if (!head)
		return (0);
	while (head)
	{
		str = head->word;
		while (count_char(head->word, '$') && !expand_inside_single_quotes(head->word))
		{
			extract_variable(head);
		}
		head = head->next;
	}
	return (SUCCESS);
}

