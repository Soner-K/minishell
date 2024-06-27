/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:11:25 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/27 15:18:30 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


					/*					WORK IN PROGRESS
- Need to account for builtins inside the get_cmd function (Or before?)
- Need to test check_redir_and_heredoc
- get_cmds_list not finished
- Might need to rethink the way I do get_cmd : Instead of copying the nodes content,
I can just point to that content and only free the list (not its word's component).			
					
*/

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
/*free tokens here in caseof malloc failure ?*/
char	**get_cmd(t_tokens **head, t_cmds *node)
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
	if (*head && (*head)->type != NONE)
	{
		
		node->type = (*head)->type;
	}
	free(str);
	return (cmd);
}

/**
 * @brief Frees all the malloc'd componend of a list of type t_cmds.
 * @param head A double pointer to the head of the list.
 * @returns void.
 */
void	free_all_cmds(t_cmds *head)
{
	t_cmds	*tmp;

	if (head)
		return ;
	while (head)
	{
		tmp = head;
		head = head->next;
		free_arrs((void **)tmp->cmd);
		free(tmp);
	}
}
/**
 * @brief If a token node contains a redirection or a heredoc, 
 * stores the name of the file thats being redirected to, or
 * the delimiter if given a heredoc. 
 * @param head Double pointer to the head of the tokens list. A double
 * pointer is used to free the memory of the copied nodes and move the
 * head of the list accordingly.
 * @param node Pointer to a cmds node.
 * @returns True (1) if the redirection's file or the heredoc's delimiter
 * is successfuly copied, and false (0) otherwise.
 */
bool	check_redir_and_heredoc(t_tokens **head, t_cmds *node)
{
	t_tokens	*tmp;

	if (node->type < INREDIR || node->type > APPENDREDIR)
		return (true);
	tmp = *head;
	(*head) = (*head)->next;
	if (node->type == HEREDOC)
	{
		node->here_doc_sep = ft_strdup((*head)->word);
		if (!node->here_doc_sep)
			return (free(tmp->word), free(tmp), false);
	}
	if (node->type == INREDIR || node->type == OUTREDIR
		|| node->type == APPENDREDIR)
	{
		node->file_redir = ft_strdup((*head)->word);
		if (!node->file_redir)
			return (free(tmp->word), free(tmp), false);
	}
	tmp = *head;
	(*head) = (*head)->next;
	free(tmp->word);
	free(tmp);
	return (true);
}

__int8_t	find_operator(t_tokens *head, t_cmds *node)
{
	if (!head)
		return (false);
	while (head)
	{
		if (is_valid_separator(head->word))
		{
			if (head->type == HEREDOC)
			{
				node->here_doc_sep = ft_strdup(head->word);
				if (!node->here_doc_sep)
					return (-1);
			}
			else if (head->type != PIPE)
			{
				node->file_redir = ft_strdup(head->word);
				if (!node->file_redir)
					return (-1);
			}
			node->type = head->type;
			return (true);
		}
		head = head->next;
	}
	return (false);
}

/*In progress*/
//adding a variable to precise what the error is?
t_cmds	*get_cmds_list(t_tokens **head)
{
	t_cmds *lst;
	t_cmds *cmds_head;

	if (!(*head))
		return (NULL);
	lst = new_node_cmd(1);
	if (!lst)
		return (NULL);
	cmds_head = lst;
	while (head)
	{
		if (find_operator(*head, lst) == -1)
			return (free_tokens(*head), free_all_cmds(cmds_head), NULL);
		if (is_valid_separator((*head)->word))
			*head = (*head)->next;
		if (!(*head))
			break ;
		
	}
	return (cmds_head);
}
