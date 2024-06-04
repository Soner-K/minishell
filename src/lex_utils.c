/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:34:13 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/04 17:35:25 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	find_sep(char c)
{
	if (ft_isalpha(c) || c == '-' || c == '.')
		return (WORD);
	else if (c == '$' || c == '?')
		return (OPERATOR);
	else if (c == ' ')
		return (SPACE_);
	else if (c == '\t')
		return (TAB_);
	else if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (INREDIR);
	else if (c == '>')
		return (OUTREDIR);
	else if (c == '"')
		return (DOUBLE_QUOTE);
	else if (c == '\'')
		return (SINGLE_QUOTE);
	return (NONE);
}
void	copy_until_next_sep(char **line, char sep, t_test *node)
{
	short int	len;
	char		*tmp;

	// if (!(*line))
	// 	return ;
	len = 0;
	tmp = *line;
	while (**line && sep == find_sep(**line))
	{
		len++;
		(*line)++;
		if (sep == SINGLE_QUOTE || sep == DOUBLE_QUOTE)
			break ;
	}
	node->word = malloc(sizeof(char) * len + 1);
	node->word[len] = '\0';
	ft_memcpy(node->word, tmp, len);
	node->type = sep;
}

t_test	*get_tokens(char *line)
{
	t_test	*tokens;
	t_test	*head;
	char	sep;

	if (!line)
		return (NULL);
	tokens = lstnew(NULL);
	if (!tokens)
		exit(EXIT_FAILURE);
	head = tokens;
	while (*line)
	{
		sep = find_sep(*line);
		copy_until_next_sep(&line, sep, tokens);
		tokens->next = lstnew(NULL);
		if (!tokens->next)
			exit(EXIT_FAILURE);// fonction erreur + free
		tokens = tokens->next;
	}
	//delete last node which value's is NULL ? keep it cuz split for commands' array
	return (head);
}