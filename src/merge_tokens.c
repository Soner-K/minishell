/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   merge_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:56:42 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/05 17:36:13 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief If a token is a quote, join in a string all the tokens that follow, 
 * until a similar quote is found. If there is only one quote, everything
 * is stored inside the string.
 * @param tokens Double pointer to a node inside the tokens list.
 * @param quote_type The type of quotes, being either " or '.
 * @returns The joined string.
 */
char	*join_inside_quotes(t_test **tokens, __int8_t quote_type)
{
	char	*str;

	str = ft_fuse(NULL, (*tokens)->word);
	if (!str)
		return (NULL);
	*tokens = (*tokens)->next;
	while (*tokens && (__int8_t)(*tokens)->type != quote_type)
	{
		str = ft_fuse(str, (*tokens)->word);
		if (!str)
			return (NULL);
		*tokens = (*tokens)->next;
	}
	if ((*tokens) && (__int8_t)(*tokens)->type == quote_type)
	{
		str = ft_fuse(str, (*tokens)->word);
		if (!str)
			return (NULL);
		(*tokens) = (*tokens)->next;
	}
	return (str);
}

/**
 * @brief If a token is different than NULL, adds a new node
 * to a new token list. This funtion is called until all the nodes
 * of the old list are gone through.
 * @param old A double pointer to a node of the old tokens' list.
 * @param new A double pointer to the head of the new tokens' list.
 * @param type The type of the current old node's token.
 * @param i A boolean being TRUE if the created node will be the head of
 * the new tokens list.
 * @returns SUCCESS (1) if the new node was created and added to the list.
 * FALSE otherwise.
 */
bool	merger(t_test **old, t_test **new, __int8_t type, bool i)
{
	char	*str;
	t_test	*token;

	if (type == SINGLE_QUOTE || type == DOUBLE_QUOTE)
	{
		str = join_inside_quotes(old, type);
		if (!str && type != NONE)
			return (FAILURE);
		token = new_token(str, i);
		token->type = WORD; // ATTENTION avec expand dans "". Si juste "", type = word?
		add_token(new, token);
		return (SUCCESS);
	}
	str = ft_strdup((*old)->word);
	if (!str && type != NONE)
		return (FAILURE);
	token = new_token(str, i);
	if (!token)
		return (FAILURE);
	token->type = (*old)->type;
	add_token(new, token);
	*old = (*old)->next;
	return (SUCCESS);
}

/**
 * @brief Generates a new tokens list, without the spaces and tabs and
 * with the quotes partially handled (see join_inside_quotes).
 * @param head The head of the old tokens list.
 * @returns The new tokens list.
 */
t_test	*merge_tokens(t_test *head)
{
	t_test		*new;
	t_test		*first;
	int			i;

	i = 0;
	if (!head)
		return (NULL);
	first = head;
	new = NULL;
	while (head)
	{
		if (head->type != SPACE_ && head->type != TAB_)
		{
			 if (merger(&head, &new, head->type, i++ == 1) == FAILURE)
			 {
				free_tokens(new);
				free_tokens(first);
				//do error functon. That kind of error = give back terminal?
			 }
		}
		else
			head = head->next;
	}
	free_tokens(first);
	return (new);
}

//add one node for a NULL token?
int	main(void)
{
	char *line = readline(">>> ");
	t_test *tokens = create_tokens(line);
	t_test *final = NULL;
	t_test *first = tokens;

	printf("\t\t\tBEFORE MERGING\t\t\t\n");
	while (tokens)
	{
		printf("[%u] -> %s\n", tokens->type, tokens->word);
		tokens = tokens->next;
	}
	printf("\t\t\tAFTER MERGING\t\t\t\n");
	final = merge_tokens(first);
	first = final;
	while (final)
	{
		printf("[%u] -> %s\n", final->type, final->word);
		final = final->next;
	}
	free_tokens(first);
}
