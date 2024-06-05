/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:34:13 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/05 17:40:34 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Returns a character's token type.
 * @param c A character.
 * @returns The token type.
 */
static __int8_t	find_token(char c)
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
/**
 * @brief Stores inside a node everything starting from a character
 * with the token "token", until a character different from it.
 * different from the given token type.
 * @param line Adress to the pointer containing the output of readline.
 * @param token Pretty self-explanatory.
 * @param node A pointer to a node of a tkens' list.
 * @returns void
 */
static void	copy_until_next_token(char **line, char token, t_test *node)
{
	short int	len;
	char		*tmp;

	// if (!(*line)) //protection needed?
	// 	return ;
	len = 0;
	tmp = *line;
	while (**line && token == find_token(**line))
	{
		len++;
		(*line)++;
		if (token == SINGLE_QUOTE || token == DOUBLE_QUOTE)
			break ;
	}
	node->word = malloc(sizeof(char) * len + 1);
	node->word[len] = '\0';
	ft_memcpy(node->word, tmp, len);
	node->type = token;
}

/**
 * @brief Creates a tokens list, where each node contains elements
 * that are of a single token type, including spaces and tabs.
 * @param line The output of the readline function.
 * @returns The tokens list.
 */
t_test	*create_tokens(char *line)
{
	t_test	*tokens;
	t_test	*head;
	char	token;

	if (!line)
		return (NULL);
	tokens = new_token(NULL, 1);
	if (!tokens)
		exit(EXIT_FAILURE); //?
	head = tokens;
	while (*line)
	{
		token = find_token(*line);
		copy_until_next_token(&line, token, tokens);
		tokens->next = new_token(NULL, 0);
		if (!tokens->next)
			exit(EXIT_FAILURE);// fonction erreur + free
		tokens = tokens->next;
	}
	//delete last node which value's is NULL ? keep it cuz split for commands' array?
	return (head);
}
