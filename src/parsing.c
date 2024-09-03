/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:00:31 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/03 20:13:07 by sokaraku         ###   ########.fr       */
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
static bool	check_all_operators(t_tokens *head) //error code is 2?
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
 * @brief Helper function for set_redirections.
 * If a redirection node is found, sets the following node accordingly,
 * and adjust the next and previous nodes' addresses. The current node is
 * then disregarded, since it is a redirection operator.
 * @param head A double pointer to the head of the tokenized list.
 * A double pointer is used to move the head accordingly if the first
 * node is a redirection.
 * @param curr A double pointer to the current node that is processed.
 * A double pointer is used to move curr's address in the calling function.
 * The curr node is necessarily a redirection operation ('<', '>', '>>', '<<').
 * @param next A double pointer to the node following the one that's processed.
 * A double pointer is used to move next's address in the calling function.
 * @returns void.
 */
static void	redir_helper(t_tokens **head, t_tokens **curr, t_tokens **next)
{
	bool		is_head;
	t_tokens	*prev;

	is_head = 0;
	prev = (*curr)->prev;
	if (*curr && !prev)
		is_head = 1;
	(*next)->type = (*curr)->type;
	(*next)->prev = prev;
	free_one_token(*curr);
	if (prev)
		prev->next = *next;
	else
	{
		*curr = *next;
		if (is_head)
			*head = *curr;
		return ;
	}
	*curr = (*next)->next;
	if (is_head)
		*head = *curr;
}

/**
 * @brief Processes a tokenized list, and sets the redirections in place by
 * removing and freeing redirections tokens and associating
 * subsequent ones as file, with a given redirection ('<', '>','<<' or '>>').
 * 
 * N-B : when coming to this part of the program, the syntax and grammar of
 * the operators are correct.
 * @param head A double pointer to the head of the tokenized list. 
 * A double pointer is used to move the head accordingly if the first
 * node is a redirection.
 * @returns void.
 */
static void	set_redirections_type(t_tokens **head)
{
	t_tokens	*curr;
	t_tokens	*next;

	curr = *head;
	next = curr->next;
	while (next)
	{
		if (curr->type >= INREDIR && curr->type < PIPE && next->type == WORD)
			redir_helper(head, &curr, &next);
		else
			curr = curr->next;
		if (curr)
			next = curr->next;
		else
			break ;
	}
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
	while (head)
	{
		if (head->type >= INREDIR && head->type < PIPE)
		{
			if (!head->next || head->next->type != WORD)
				return (false);
		}
		else if (head->type == PIPE && !head->next)
			return (false);
		head = head->next;
	}
	return (true);
}

//find better name accounting for pipes too.
/**
 * @brief Checks the operators validity and the redirections' syntax.
 * @param head A double pointer to the head of the list.
 * A double pointer is needed to adjust the head of the list
 * (see set_redirections).
 * @returns True (1) if the operators are correct and the syntax is valid,
 * and false (0) otherwise.
 */
bool	check_all_redirections(t_tokens **head)
{
	if (!check_all_operators(*head))
		return (free_tokens(*head), false);
	printf("Operators are valid \n");
	if (!check_syntax(*head))
		return (free_tokens(*head), printf("Syntax not valid\n"), false);
	set_redirections_type(head);
	printf("Redirections set\n");
	return (true);
}
