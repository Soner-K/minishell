/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:20:21 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/24 15:53:09 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define EXPAND_SYNTAX_NOT_VALID -2
#define EXPAND_INSIDE_SINGLE_QUOTES -3

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
	if (ft_strlen(var) == 0)
	{
		str = ft_strslice(node->word, s - (s != 0), end, &alloc_fail);
		if (alloc_fail == true)
			return (NULL);
		return (str);
	}
	str = ft_strreplace(node->word, var, s - (s != 0), end);
	if (!str)
		return (NULL);
	return (str);
}

/**
 * @brief Retrieves the content of an environment variable
 * from minishell's environment list. If the variable refers to another one
 * (i.e. starts with '$'), finds the referenced variable recursively.
 * The recursion continues as long as there are referenced variables.
 * @param var The variable name.
 * @param env_list The environment list.
 * @param first A pointer to the first node of the environment list.
 * @returns The content of the variable.
 */
static char	*getenv_from_env_list(char *var, t_env *env_list, t_env *first,
		bool *alloc_fail)
{
	int		len_var;
	char	*ret;

	if (!env_list || !var || *alloc_fail == true)
		return (NULL);
	len_var = ft_strlen(var);
	while (env_list)
	{
		if (!ft_strncmp(var, env_list->variable, len_var)
			&& env_list->variable[len_var] == '=')
		{
			ret = &env_list->variable[len_var + 1];
			if (ret[0] == '$')
				ret = getenv_from_env_list(ret, first, first, alloc_fail);
			break ;
		}
		env_list = env_list->next;
	}
	if (env_list)
	{
		ret = ft_strdup(ret);
		if (!ret)
			return (*alloc_fail = 1, NULL);
	}
	return (NULL);
}

/**
 * @brief Retrieves a variable name from ENV, stores its content
 * and puts it inside node's word.
 * N-B : Quotes are marked but aren't removed here.
 * Happens after all the expands variables are replaced.
 * @param node Pointer to a node of the tokens' list.
 * @param env_list Pointer to the head of minishell's env_list.
 * @returns -3 if the expand is inside single quotes, -2 if the expand's
 * syntax isn't valid, -1 if there is an allocation failure and 1 (SUCESS)
 * if none of these cases happened.
 */
static __int8_t	extract_variable(t_tokens *node, t_env *env_list, int last_exit,
		bool *alloc_f)
{
	int		start;
	int		end;
	char	*var_content;
	char	*str;

	if (expand_inside_single_quotes(node) == true)
		return (EXPAND_INSIDE_SINGLE_QUOTES);
	if (check_expand_syntax(node->word, &start, &end) == false)
		return (EXPAND_SYNTAX_NOT_VALID);
	str = ft_substr(node->word, start, (end - start + 1));
	if (!str)
		return (ALLOCATION_FAILURE);
	if (node->word[end] == '?')
	{
		var_content = ft_itoa(last_exit);
		if (!var_content)
			return (free(str), ALLOCATION_FAILURE);
	}
	else
		var_content = getenv_from_env_list(str, env_list, env_list, alloc_f);
	free(str);
	str = get_new_word(node, var_content, start, end);
	if (!str)
		return (free(var_content), ALLOCATION_FAILURE);
	return (free(node->word), node->word = str, free(var_content), SUCCESS);
}

/**
 * @brief Iterates through all the tokenized list's nodes, and
 * replace the expands when found.
 * @param head A pointer to the head of the tokenized list.
 * @param env_list Pointer to the head of minishell's env_list.
 * @param last_exit_status Value of the last exit status.
 * @returns -1 (ALLOCATION_FAILURE) if a memory allocation failed, and
 * 1 (SUCCESS) if the list was iterated through fully.
 */
__int8_t	extract_all(t_tokens *head, t_env *env_list, int last_exit_status)
{
	__int8_t	ret;
	t_tokens	*first;
	short int	n_expand;
	bool		alloc_f;

	if (!head)
		return (0);
	n_expand = count_expands(head->word);
	first = head;
	alloc_f = false;
	while (head)
	{
		while (n_expand > 0)
		{
			ret = extract_variable(head, env_list, last_exit_status, &alloc_f);
			if (ret == ALLOCATION_FAILURE)
				return (ret);
			n_expand--;
		}
		head = head->next;
		if (head)
			n_expand = count_expands(head->word);
	}
	reset_negative_characters(first);
	return (SUCCESS);
}
