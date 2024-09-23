/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   runtime_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 11:22:35 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/23 11:33:47 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	runtime_signal(void)
{
	signal(SIGINT, &sig_handler_forks);
	signal(SIGQUIT, SIG_DFL);
}

void	runtime_free(t_exec *cmds_list)
{
	close_no_file(cmds_list);
	if (cmds_list->prev != NULL)
		if (cmds_list->prev->pipe_fdi != -1)
			close(cmds_list->prev->pipe_fdi);
	store_or_free(NULL, NULL, false, true);
	exit(EXIT_FAILURE);
}
