/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:00:31 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/17 11:07:04 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Checks the validity of all redirections or pipe operators
 * in an input line, after the tokenization.
 * @param head A pointer to the head of the tokenized list.
 * @returns true (1) if there is no operators or
 * if the operators syntax is valid and false (0) otherwise.
 */
static bool	check_operators_validity(t_tokens *head)
{
	static char	*operators[6] = {"<", ">", "<<", ">>", "|"};

	while (head)
	{
		if (head->type >= INREDIR && head->type <= PIPE)
		{
			if (ft_strcmp(head->word, operators[head->type]))
				return (false);
		}
		head = head->next;
	}
	return (true);
}

/**
 * @brief Checks the syntax error. A syntax error happens when
 * the token following a redirection is different than a word or
 * if a pipe if there is no token after a pipe.
 * @param head A pointer to the head of the list.
 * @returns True (1) if the syntax is correct, and false (0) otherwise.
 */
static bool	check_syntax(t_tokens *head)
{
	int	len_str;

	while (head)
	{
		if (head->next)
			len_str = ft_strlen(head->next->word);
		if (head->type >= INREDIR && head->type <= PIPE)
		{
			if (!head->next || (head->next->type < WORD
					|| head->next->type > CMD) || len_str == 0)
				return (false);
		}
		else if (head->type == PIPE && !head->next)
			return (false);
		head = head->next;
	}
	return (true);
}

/**
 * @brief Checks the operators validity and the redirections' syntax.
 * @param head A double pointer to the head of the list.
 * A double pointer is needed to adjust the head of the list
 * (see set_redirections).
 * @returns True (1) if the operators are correct, the syntax and semantics
 *  are valid and false (0) otherwise.
 */
bool	full_check(t_tokens **head)
{
	if (!check_operators_validity(*head))
		return (false);
	if (!check_syntax(*head))
		return (false);
	set_redirections_type(head);
	return (true);
}
