/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/26 10:11:25 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/26 13:56:11 by sokaraku         ###   ########.fr       */
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
static bool	is_valid_separator(char *sep)
{
	short int	sep_len;

	sep_len = ft_strlen(sep);
	if (!ft_strncmp(">>", sep, sep_len))
		return (true);
	if (!ft_strncmp("<<", sep, sep_len))
		return (true);
	if (!ft_strncmp(">", sep, sep_len))
		return (true);
	if (!ft_strncmp("<", sep, sep_len))
		return (true);
	if (!ft_strncmp("|", sep, sep_len))
		return (true);
	return (false);
}

/*
						/////	CAREFUL	\\\\\\\
Need to work on keeping information on what was
the separator (redir, pipe, here_doc...)*/
short int	nodes_until_separator(t_tokens *head)
{
	short int	n;

	if (!head)
		return (0);
	n = 0;
	while (head && !is_valid_separator(head->word))
	{
		n++;
		head = head->next;
	}
	return (n);
}
/**
 * @brief A simple strjoin, but it also puts a space between the two strings,
 to facilitate the split afterwards.
 * @param s1 A pointer to the first string to copy.
 * @param s2 a pointer to the second string to copy.
 * @returns The merged strings, with a space in the middle.
 * Returns NULL if the allocation failed.
 */
char	*merge_strings(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (!new)
		return (NULL);
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	if (s1)
		new[i++] = ' ';
	while (s2 && s2[j])
		new[i++] = s2[j++];
	new[i] = 0;
	free(s1);
	return (new);
}

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
char	**get_cmd(t_tokens **head)
{
	t_tokens	*tmp;
	char		*str;
	char		**cmd;
	short int	n;

	str = NULL;
	n = nodes_until_separator(*head);
	while (n--)
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

/**
 * @brief Frees all the malloc'd componend of a list of type t_cmds.
 * @param head A pointer to the head of the list.
 * @returns void.
 */
void	free_cmds(t_cmds *head)
{
	t_cmds	*tmp;

	if (!head)
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
/*In progress*/
t_cmds	*get_cmds_list(t_tokens **head)
{
	t_cmds *lst;
	t_cmds *cmds_head;

	lst = new_node_cmd(1);
	if (!lst)
		return (NULL);
	cmds_head = lst;
	while (*head)
	{
		// if (is_valid_separator((*head)->word))
		lst->type = (*head)->type;
		if (lst->type == HEREDOC)

			lst->cmd = get_cmd(head);
		if (!lst->cmd)
			return (free_cmds(cmds_head), NULL);
	}
}