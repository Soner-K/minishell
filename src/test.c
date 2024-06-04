/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 17:56:42 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/04 17:35:02 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_test	*lstnew(char *word) // exclusivement pour token
{
	t_test *new;

	new = malloc(sizeof(t_test));
	new->word = word;
	new->next = NULL;
	new->type = NONE;
	// new->head = head;
	return (new);
}

void	free_tokens(t_test *head)
{
	t_test	*tmp;

	while (head)
	{
		tmp = head;
		head = head->next;
		free(tmp->word);
		free(tmp);
	}
}

char	*join_inside_quotes(t_test **head, __int8_t mode)
{
	char	*str;

	str = ft_fuse(NULL, (*head)->word);
	*head = (*head)->next;
	while (*head && (__int8_t)(*head)->type != mode)
	{
		str = ft_fuse(str, (*head)->word);
		*head = (*head)->next;
	}
	if ((*head) && (__int8_t)(*head)->type == mode)
	{
		str = ft_fuse(str, (*head)->word);
		(*head) = (*head)->next;
	}
	return (str);
}

void	quotes_merger(t_test **old_tokens, t_test **new_tokens, __int8_t type)
{
	char	*str;
	t_test	*token;

	str = join_inside_quotes(old_tokens, type);
	token = lstnew(str);
	token->type = WORD; // ATTENTION avec expand dans "". Si juste "", type = word?
	printf("[%u] -> %s\n", token->type, token->word);
	if (*new_tokens)
		(*new_tokens)->next = token;
	else
		*new_tokens = token;
	*new_tokens = (*new_tokens)->next;
}

t_test	*merge_tokens(t_test *head)
{
	t_test		*new;
	t_test		*first;
	char		*str;

	if (!head)
		return (NULL);
	first = head;
	new = NULL;
	while (head)
	{
		if (head->type == SINGLE_QUOTE || head->type == DOUBLE_QUOTE)
			quotes_merger(&head, &new, head->type);
		else if (head->type != SPACE_ && head->type != TAB_ && head->type != NONE)
		{
			str = ft_strdup(head->word);
			new = lstnew(str);
			new->type = head->type;
			new = new->next;
			head = head->next;
		}
		else
			head = head->next;
	}
	free_tokens(first);
	return (NULL);
}

int	main(void)
{
	char *line = readline(">>> ");
	t_test *tokens = get_tokens(line);
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
	// while (final)
	// {
	// 	printf("[%u] -> %s\n", final->type, final->word);
	// 	final = final->next;
	// }
	// while (first)
	// {
	// 	t_test	*tmp = first;
	// 	first = first->next;
	// 	free(tmp->word);
	// 	free(tmp);
	// }
}