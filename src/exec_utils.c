/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 16:04:42 by sokaraku          #+#    #+#             */
/*   Updated: 2024/07/12 18:27:14 by sokaraku         ###   ########.fr       */
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
	if (*head && (*head)->type == PIPE)
	{
		tmp = *head;
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

bool	is_pipe_exec(t_tokens *head)
{
	if (!head)
		return (false);
	while (head)
	{
		if (head->type ==  PIPE)
			return (true);
		head = head->next;
	}
	return (false);
}

short int	number_of_pipes(t_tokens *head)
{
	short int	n;

	n = 0;
	while (head)
	{
		if (head->type == PIPE)
			n++;
		head = head->next;
	}
	return (n);
}

int	child(t_tokens **head, char **env, int fds[2], bool last)
{
	char	*path;
	char	**cmds;
	bool	alloc_fail;

	cmds = get_cmd(head);
	path = find_path(cmds[0], env, &alloc_fail);
	close(fds[0]);
	if (last == 0)
		dup2(fds[1], STDOUT_FILENO);
	close(fds[1]);
	execve(path, cmds, env);
	return (0);
}


/*
free tokens after error (pipe, fork, dup)
Need to add the redirections handler, because get_cmd will return
NULL if it encounters a redirection (TLDR : get_cmd ignoring redirections)
do function if no pipe
*/
int	do_pipe(t_tokens **head, char **env)
{
	t_files	utils;
	int		i;
	int		n;

	i = 0;
	n = number_of_pipes(*head);
	while (i <= n)
	{
		if (pipe(utils.fds) == -1)
			exit(EXIT_FAILURE);
		utils.pid = fork();
		if (utils.pid == -1)
			exit(EXIT_FAILURE);
		if (utils.pid == 0)
			child(head, env, utils.fds, i == n);
		else
		{
			while ((*head) && (*head)->type != PIPE)
				*head = (*head)->next;
			if (*head && (*head)->type == PIPE)
				*head = (*head)->next;
			close(utils.fds[1]);
			if (dup2(utils.fds[0], STDIN_FILENO) == -1)
				exit(EXIT_FAILURE);
			close(utils.fds[0]);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}