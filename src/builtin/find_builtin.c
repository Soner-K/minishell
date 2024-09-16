/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 18:41:15 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/14 17:26:19 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	which_builtin(t_exec *cmds)
{
	if (is_echo(cmds->cmd_array[0]) == 1)
		return (1);
	else if (is_pwd(cmds->cmd_array[0]) == 1)
		return (2);
	else if (is_cd(cmds->cmd_array[0]) == 1)
		return (3);
	else if (is_env(cmds->cmd_array[0]) == 1)
		return (4);
	else if (is_exit(cmds->cmd_array[0]) == 1)
		return (5);
	else if (is_unset(cmds->cmd_array[0]))
		return (6);
	else if (is_export(cmds->cmd_array[0]))
		return (7);
	else
		return (0);
}

void	exec_builtin(int func, t_exec **cmds, t_env **env)
{
	if (func == 1)
		func_echo(*cmds);
	else if (func == 2)
		func_pwd(*cmds);
	else if (func == 3)
		func_cd(*cmds);
	else if (func == 4)
		func_env(*cmds, env);
	else if (func == 5)
		func_exit(cmds);
	else if (func == 6)
		func_unset(cmds, env);
	else if (func == 7)
		func_export(cmds, env);
}
