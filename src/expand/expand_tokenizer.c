/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:45:50 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/30 13:52:06 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void mark_str(char *str);

// COME BACK think about quotes in expand var. quotes are handled like
// usual
__int8_t	split_new_word(t_tokens *node, t_tokens *next, char *word)
{
	char		**split_word;

	(void)node;
	(void)next;
	mark_str(word);
	split_word = ft_split(word, -32);
	if (!split_word)
		return (ALLOCATION_FAILURE);
	print_strs(split_word);
	
	return (SUCCESS);
}

// static __int8_t	retokenize(char **split_word, t_tokens *curr, t_tokens *next)
// {
// 	char	*str;
// 	int		i;

// 	i = 0;
// }

static void	mark_str(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == ' ')
			str[i] = -str[i];
		else if (i > 0 && str[i] != ' ' && str[i - 1] == -32)
			str[i - 1] *= -1;
	}
}
