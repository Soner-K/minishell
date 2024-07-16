/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:00:31 by sokaraku          #+#    #+#             */
/*   Updated: 2024/07/16 21:52:40 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	set_operators_array(char *operators[])
{
	operators[INREDIR] = "<";
	operators[OUTREDIR] = ">";
	operators[HEREDOC] = "<<";
	operators[APPENDREDIR] = ">>";
	operators[PIPE] = "|";
}

char	*find_error(t_tokens *node)
{
	
}

int	write_error(t_tokens *node)
{
	char	*str;


	str = find_error();
	printf("syntax error near unexpected token '%s'\n", str);
}

bool	is_valid_operator(t_tokens *node)
{
	static char *operators[5];
	__int8_t	i;

	i = 0;
	set_operators_array(operators);
	if (!ft_strcmp(node->word, operators[node->type]))
		return (true);
	return (false);
}