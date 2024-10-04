/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_tokenizer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 17:45:50 by sokaraku          #+#    #+#             */
/*   Updated: 2024/10/04 20:59:33 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	mark_str(char *str);

// NOTE what happens when alloc failure for the added nodes?
// they're added to curr so should be freed
__int8_t	retokenize(char **split_word, t_tokens *curr, t_tokens *next)
{
	char	*str;
	int		i;
	int		start;
	int		end;

	i = 0;
	check_expand_syntax(curr->word, &start, &end);
	printf("split word is %s\n", split_word[0]);
	curr->word = get_new_word(curr, split_word[0], start, end);
	while (split_word[++i])
	{
		str = ft_strdup(split_word[i]);
		if (!str)
			return (ALLOCATION_FAILURE);
		curr->next = new_node_token(str, false);
		curr->next->type = find_token_type(str);
		curr = curr->next;
	}
	curr->next = next;
	return (SUCCESS);
}

__int8_t	split_new_word(t_tokens *node, t_tokens *next, char *word)
{
	char	**split_word;

	(void)node;
	(void)next;
	mark_str(word);
	split_word = ft_split(word, -32);
	if (!split_word)
		return (ALLOCATION_FAILURE);
	retokenize(split_word, node, next);
	free_arrs((void **)split_word);
	return (SUCCESS);
}

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
