/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:30 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/19 18:05:15 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_exit(char *str)
{
	char	*echo;
	int		i;

	i = 0;
	echo = "exit";
	while (str[i] && echo[i])
	{
		if (str[i] == echo[i])
			i++;
		else
			return (0);
	}
	if (str[i] == '\0' && echo[i] == '\0')
		return (1);
	return (0);
}

void	control_alpha(char *s, t_exec *cmds_list)
{
	printf("exit : %s: numeric argument required\n", s);
	if (cmds_list->old_stdin != -1)
		close(cmds_list->old_stdout);
	if (cmds_list->old_stdout != -1)
		close(cmds_list->old_stdin);
	store_or_free(NULL, NULL, false, true);
	exit(2);
}

void	control_many_args(t_exec *cmds_list)
{
	if (cmds_list->old_stdin != -1)
		close(cmds_list->old_stdout);
	if (cmds_list->old_stdout != -1)
		close(cmds_list->old_stdin);
	if (ft_isalpha(cmds_list->cmd_array[1][0]))
	{
		printf("exit : too many arugments\n");
		store_or_free(NULL, NULL, false, true);
		exit(1);
	}
	else
		printf("exit : too many arugments\n");
}

void	normal_exit(t_exec *cmds_list)
{
	printf("exit\n");
	if (cmds_list->old_stdin != -1)
		close(cmds_list->old_stdout);
	if (cmds_list->old_stdout != -1)
		close(cmds_list->old_stdin);
	store_or_free(NULL, NULL, false, true);
	exit(0);
}

void	func_exit(t_exec **cmds)
{
	int	i;

	i = 0;
	if (!(*cmds)->cmd_array[1])
		normal_exit((*cmds));
	if ((*cmds)->cmd_array[1] && (*cmds)->cmd_array[2])
	{
		control_many_args((*cmds));
		return ;
	}
	while ((*cmds)->cmd_array[1][i])
	{
		if (ft_isalpha((*cmds)->cmd_array[1][i]))
			control_alpha((*cmds)->cmd_array[1], (*cmds));
		i++;
	}
	i = 0;
	while ((*cmds)->cmd_array[1][i])
	{
		if (!ft_isdigit((*cmds)->cmd_array[1][i]))
			control_alpha((*cmds)->cmd_array[1], (*cmds));
		else
			normal_exit((*cmds));
		i++;
	}
}
