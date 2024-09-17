/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 23:29:23 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/17 14:52:16 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_cmds(t_exec *cmds_list)
{
	int	total_cmd;

	total_cmd = 0;
	while (cmds_list)
	{
		if (cmds_list->cmd_array)
			total_cmd++;
		cmds_list = cmds_list->next;
	}
	return (total_cmd);
}
