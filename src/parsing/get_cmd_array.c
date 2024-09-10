/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmd_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:22:13 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/10 12:46:29 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_id(t_tokens *head)
{
	int	id_cmd;

	id_cmd = 0;
	while (head)
	{
		if (head->type == PIPE)
		{
			head = head->next;
			id_cmd++;
		}
		else if (head->type >= INREDIR && head->type <= APPENDREDIR)
			head = head->next;
		else
		{
			head->id_cmd = id_cmd;
			head = head->next;
		}
	}
}

__int8_t	get_cmd_array(t_tokens **node, int id)
{
	char		*joined_cmds;
	char		**cmd_array;
	t_tokens	*tmp;

	tmp = *node;
	joined_cmds = NULL;
	while (tmp && (tmp->id_cmd != -1 && tmp->id_cmd == id))
	{
		joined_cmds = merge_strings(joined_cmds, tmp->word, -32);
		if (!joined_cmds)
			return (ALLOCATION_FAILURE);
		tmp = tmp->next;
	}
	cmd_array = ft_split(joined_cmds, -32);
	if (!cmd_array)
		return (free(joined_cmds), ALLOCATION_FAILURE);
	while (*node != tmp)
	{
		(*node)->cmd_array = cmd_array;
		(*node) = (*node)->next;
	}
	free(joined_cmds);
	return (SUCCESS);
}

void	set_cmds_arrays(t_tokens **head)
{
	t_tokens	*first;
	__int8_t	ret;

	first = *head;
	ret = SUCCESS;
	while (*head)
	{
		ret = get_cmd_array(head, (*head)->id_cmd);
		if (ret != SUCCESS)
			return ; //COME BACK
	}
	*head = first;
}
