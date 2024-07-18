/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:00:31 by sokaraku          #+#    #+#             */
/*   Updated: 2024/07/18 15:30:07 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	set_operators_array(char *operators[])
// {
// 	operators[INREDIR] = "<";
// 	operators[OUTREDIR] = ">";
// 	operators[HEREDOC] = "<<";
// 	operators[APPENDREDIR] = ">>";
// 	operators[PIPE] = "|";
// }

// char	*find_error(t_tokens *node)
// {
	
// }

// int	write_error(t_tokens *node)
// {
// 	char	*str;


// 	str = find_error();
// 	printf("syntax error near unexpected token '%s'\n", str);
// }

bool	check_operators(t_tokens *head)
{
	static char *operators[6] = {"<", ">", "<<", ">>", "|"};

	while (head)
	{
		if (ft_strcmp(head->word, operators[head->type]))
			return (false);
		head = head->next;
	}
	return (true);
}

void	set_redirections(t_tokens **head)
{
	t_tokens	*curr;
	t_tokens	*next;
	t_tokens	*prev;
	bool		is_head;

	curr = *head;
	next = curr->next;
	prev = curr->prev;
	while (next)
	{
		if (curr->type >= INREDIR && curr->type < PIPE && next->type == WORD)
		{
			if (curr && !curr->prev)
				is_head = 1;
			next->type = curr->type;
			next->prev = curr->prev;
			curr->prev->next = next;
			free_one_token(curr);
			curr = next->next;
			if (is_head)
				*head = curr;
			is_head = 0;
		}
		else
			curr = curr->next;
		if (curr)
			next = curr->next;
		else
			break ;
	}
}
