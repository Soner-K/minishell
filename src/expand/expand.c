/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:20:21 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/10 12:47:08 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EXPAND_SYNTAX_NOT_VALID -2
#define EXPAND_INSIDE_SINGLE_QUOTES -3

/*
Check thoroughly where to free
*/
/**
 * @brief Stores inside the node's word the string var, replacing the
 * expand variable's name.
 * @param node Pointer to a node of the tokens' list.
 * @param var The expand's variable content.
 * @param s The starting index at which to place var.
 * @param end The end index at which var should end.
 * @returns The new string with the expand's variable content.
 */
char	*get_new_word(t_tokens *node, char *var, short int s, short int end)
{
	char	*str;
	bool	alloc_fail;

	alloc_fail = false;
	if (!node->word || s > ft_strlen(node->word) || end > ft_strlen(node->word)
		|| end < 0 || s < 0)
		if (ft_strlen(var) == 0)
		{
			str = ft_strslice(node->word, s - (s != 0), end, &alloc_fail);
			if (alloc_fail == true)
				return (NULL); //how handle in calling function? COME BACK
			return (str);
		}
	str = ft_strreplace(node->word, var, s - (s != 0), end);
	if (!str)
		return (NULL);
	return (str);
}
/**
 * @brief Retrieves a variable name from ENV, stores its content
 * and puts it inside node's word.
 * N-B : Quotes are marked but aren't removed here.
 * Happens after all the expands variables are replaced.
 * @param node Pointer to a node of the tokens' list.
 * @returns -3 if the expand is inside single quotes, -2 if the expand's
 * syntax isn't valid, -1 if there is an allocation failure and 1 (SUCESS)
 * if none of these cases happened.
 */
__int8_t	extract_variable(t_tokens *node)
{
	short int	start;
	short int	end;
	char		*var_content;
	char		*str;

	if (node->quotes == SINGLE_QUOTE)
		return (EXPAND_INSIDE_SINGLE_QUOTES);
	if (!check_expand_syntax(node->word, &start, &end))
		return (EXPAND_SYNTAX_NOT_VALID);
	str = ft_substr(node->word, start, (end - start + 1));
	if (!str)
		return (ALLOCATION_FAILURE);
	var_content = getenv(str);
	free(str);
	str = get_new_word(node, var_content, start, end);
	if (!str)
		return (ALLOCATION_FAILURE);
	free(node->word);
	node->word = str;
	return (SUCCESS);
}

/**
 * @brief Count the number of expand(s) inside one token.
 * @param str The token.
 * @returns The number of expand(s) inside one token.
 */
static short int	count_expands(char *str)
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

void	reset(t_tokens *head)
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
 * @brief Iterates through all the tokenized list's nodes, and
 * replace the expands when found.
 * @param head A pointer to the head of the tokenized list.
 * @returns -1 (ALLOCATION_FAILURE) if a memory allocation failed, and
 * 1 (SUCCESS) if the list was iterated through fully.
 */
__int8_t	extract_all(t_tokens *head)
{
	__int8_t	ret;
	t_tokens	*first;
	short int	n_expand;

	if (!head)
		return (0);
	n_expand = count_expands(head->word);
	first = head;
	while (head)
	{
		while (n_expand > 0)
		{
			ret = extract_variable(head);
			if (ret == ALLOCATION_FAILURE)
				return (ret);
			n_expand--;
		}
		head = head->next;
		if (head)
			n_expand = count_expands(head->word);
	}
	reset(first);
	return (SUCCESS);
}
