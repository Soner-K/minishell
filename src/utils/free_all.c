/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 12:34:34 by sokaraku          #+#    #+#             */
/*   Updated: 2024/10/05 19:24:36 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees all the memory allocated for the shell.
 * @param line The line to free.
 * @param exec The head of the execution list.
 * @param env_list The head of the environment list.
 * @param free_env A boolean being true (1) if the environment list must be
 * freed and false (0) otherwise.
 * @returns void.
 */
void	free_all(char *line, t_exec *exec, t_env *env_list, bool free_env)
{
	if (line)
		free(line);
	if (exec)
		free_exec(exec, true);
	if (free_env)
		free_env_list(env_list);
}
