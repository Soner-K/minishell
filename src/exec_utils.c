/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:51:59 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/25 17:55:00 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

short int	get_array_size(t_tokens *head)
{
	short int	size;

	if (!head)
		return (0);
	size = 0;
	while (head)
	{
		if (is_valid_separator(head->word))
		{
			return (size);
		}
		size++;
		head = head->next;
	}
	printf("%d\n", size);
	return (size);
}

void	free_cmd_array(char **strs, short int size)
{
	short int	i;

	i = 0;
	while (size--)
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
/*
						/////	CAREFUL	\\\\\\\
Need to work on keeping information on what was
the separator (redir, pipe, here_doc...)*/
void	ignore_separator(t_tokens **head)
{
	t_tokens	*tmp;

	if (!(*head) || !head)
		return ;
	while (*head && is_valid_separator((*head)->word))
	{
		tmp = *head;
		*head = (*head)->next;
		free_one_token(tmp);
	}
}
/* - do error function if malloc failure. Check in the calling function
 why cmd array returned NULL (can be malloc failure but also
 end of list).
 - dont forget to store the token type.
 - check if strs is well freed in case of malloc failure
 - better to point to the already existing string instead of strdup?
 But memory handling might become more tedious.
*/
char	**get_cmd_array(t_tokens **head_tokens, t_cmds *cmds)
{
	char		**cmd;
	short int	array_size;
	short int	i;
	t_tokens	*tmp;

	ignore_separator(head_tokens);
	array_size = get_array_size(*head_tokens);
	if (array_size == 0)
		return (NULL);
	cmd = malloc(sizeof(char *) * (array_size + 1));
	if (!cmd)
		return (NULL);
	cmd[array_size] = NULL;
	i = 0;
	cmds->size = array_size;
	while (array_size)
	{
		tmp = *head_tokens;
		*head_tokens = (*head_tokens)->next;
		cmd[i] = ft_strdup(tmp->word);
		if (!cmd[i])
			free_cmd_array(cmd, array_size + i);
		i++;
		array_size--;
		free_one_token(tmp);
	}
	return (cmd);
}

t_cmds	*get_cmds_list(t_tokens **head)
{
	t_cmds	*cmds;

	if (!(*head))
		return (NULL);
	cmds = new_node_cmd(1);
	while (*head)
	{
		cmds->cmd = get_cmd_array(head, cmds);
		// if (!cmds->cmd)
		// 	free_cmds()
		if (*head)
			cmds->next = new_node_cmd(0);
		else
			break ;
		// if (!cmds->next)
			// free_cmds
		cmds = cmds->next;
	}
	return (cmds->head);
}