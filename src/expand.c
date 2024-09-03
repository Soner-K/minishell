/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:20:21 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/03 21:00:00 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EXPAND_SYNTAX_NOT_VALID -2
#define EXPAND_INSIDE_SINGLE_QUOTES -3

/*
Check thoroughly where to free
s = start
*/
/**
 * @brief
 * @param node Pointer to a node of the tokens' list.
 * @param var The expand's variable content.
 * @param s
 * @param end
 * @returns
 */
char	*get_new_word(t_tokens *node, char *var, short int s, short int end)
{
	char	*str;
	int		size;

	printf("var is %s, start is %hd end is %hd\n", var, s, end);
	size = ft_strlen(var) + (end - s - 2) + 1;
	printf("size in get_new_word %d\n", size); /// why 10 with "   $USER  "
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

/**
 * @brief Retrieve a variable name from ENV, stores its content
 * and puts it inside node's word. 
 * N-B : Quotes aren't removed here, but after all the expands variables
 * are replaced.
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

	printf("node word is %s\n", node->word);
	if (node->quotes == SINGLE_QUOTE)
		return (EXPAND_INSIDE_SINGLE_QUOTES);
	if (!check_expand_syntax(node->word, &start, &end))
		return (printf("\n start is %d & end is %d\n", start, end),
			EXPAND_SYNTAX_NOT_VALID);
	str = ft_substr(node->word, start, (end - start + 1));
	if (!str)
		return (ALLOCATION_FAILURE);
	var_content = getenv(str);
	// if (!var_content)
	// 	return (free(str), VAR_NOT_FOUND); //no need, get_new_word will get rid of the variable in the final result
	free(str);
	str = get_new_word(node, var_content, start, end);
	if (!str)
		return (ALLOCATION_FAILURE);
	free(node->word);
	node->word = str;
	return (SUCCESS);
}

// __int8_t	extract_all(t_tokens *head)
// {
// 	char	*str;

// 	if (!head)
// 		return (0);
// 	while (head)
// 	{
// 		str = head->word;
// 		while (count_char(head->word, '$'))
// 		{
// 			if (extract_variable(head) < 0)
// 				break ;
// 		}
// 		head = head->next;
// 	}
// 	return (SUCCESS);
// }

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

__int8_t	extract_all(t_tokens *head)
{
	char *str;
	__int8_t ret;
	short int n_expand;

	if (!head)
		return (0);
	n_expand = count_expands(head->word);
	printf("n expand %d\n", n_expand);
	while (head)
	{
		str = head->word;
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
	return (SUCCESS);
}