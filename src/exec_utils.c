/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:04:42 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/30 22:32:35 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Iterate through a list of tokens, and store the components inside
 * an array of strings, until the next delimitor (>, <, >>, << |) or the
 * end of the list.
 * @param head Double pointer to the head of the tokens list. A double
 * pointer is used to free the memory of the copied nodes and move the
 * head of the list accordingly.
 * @returns An array of strings, more precisely an array of commands.
 *
 */
/*free tokens here in caseof malloc failure ?
ATTENTION : Need to handle the case where the first
node is a separator.

*/
char	**get_cmd(t_tokens **head)
{
	t_tokens	*tmp;
	char		*str;
	char		**cmd;

	str = NULL;
	while (*head && (*head)->type == WORD)
	{
		tmp = *head;
		str = merge_strings(str, tmp->word);
		if (!str)
			return (NULL);
		*head = (*head)->next;
		free(tmp->word);
		free(tmp);
	}
	cmd = ft_split(str, ' ');
	if (!cmd)
		return (free(str), NULL);
	free(str);
	return (cmd);
}

/*
Possible error cases :
1. If there is no word after the operator (except for $?)
2. What about the type none? When does it occur?
Looks like it never occurs, so might get rid of it.

Note : we're after the parsing, so if there is any syntax error,
the  execution isnt done.
*/
__int8_t	get_operator(t_tokens **head, char **op_str)
{
	t_tokens 	*tmp;
	__int8_t	type;

	if (!(*head))
		return (-1);
	tmp = *head;
	type = -1;
	*head = (*head)->next;
	if (tmp->type >= INREDIR && tmp->type <= PIPE)
		type = tmp->type;
	if (type != -1)
	{
		if (tmp->next)
			*op_str = tmp->next->word;
		else if (type == OPERATOR)
			return (free(tmp->word), free(tmp), type);
		else
			return(free(tmp->word), free(tmp), -1);
		free(tmp->word);
		free(tmp);
		tmp = *head;
		*head = (*head)->next;
		free(tmp);
		return (type);
	}
	return (free_tokens(tmp), -1); //probably never gets to here
}

void	prep_execution(t_tokens **head)
{
	char		**cmd_array;
	char		*op_str;
	__int8_t	type;

	cmd_array = get_cmd(head);
	if (!cmd_array)
		return (free_tokens(*head));
	op_str = NULL;
	type = get_operator(head, &op_str);
	if (!op_str)
		return(free_tokens(*head), free_arrs((void **)cmd_array));
	/*
		pipe function
		here_doc
		builtins
		where to do the redirections ?
	*/
	print_strs(cmd_array);
	printf("\n");
	printf("type of op_str is %d and str is = %s\n", type, op_str);
	free_arrs((void **)cmd_array);
	free(op_str);
}