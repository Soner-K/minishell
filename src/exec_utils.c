/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/17 09:51:59 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/24 15:48:18 by sokaraku         ###   ########.fr       */
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
			return (printf("%d\n", size), size);
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

/* - do error function if malloc failure. Check in the calling function
 why cmd array returned NULL (can be malloc failure but also
 end of list).
 - dont forget to store the token type.
 - check if strs is well freed in case of malloc failure
 - better to point to the already existing string instead of strdup?
 But memory handling might become more tedious.
*/
char	**get_cmd_array(t_tokens **head)
{
	char		**cmd;
	short int	array_size;
	short int	i;
	t_tokens	*tmp;

	array_size = get_array_size(*head);
	cmd = malloc(sizeof(char *) * (array_size + 1));
	if (!cmd)
		return (NULL);
	cmd[array_size] = NULL;
	i = 0;
	while (array_size)
	{
		tmp = *head;
		*head = (*head)->next;
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
	cmds = new_cmd(1);
	while (*head)
	{
		cmds->cmd = get_cmd_array(head);
		// if (!cmds->cmd)
		// 	free_cmds()
		
	}
}