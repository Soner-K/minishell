/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:30 by sumseo            #+#    #+#             */
/*   Updated: 2024/10/04 15:28:57 by sokaraku         ###   ########.fr       */
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

void	control_alpha(t_exec *cmds_list)
{
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(cmds_list->cmd_array[1], STDERR_FILENO);
	ft_putstr_fd(" numeric argument required", STDERR_FILENO);
	if (cmds_list->old_stdin != -1)
		close(cmds_list->old_stdout);
	if (cmds_list->old_stdout != -1)
		close(cmds_list->old_stdin);
	store_or_free(NULL, NULL, false, true);
	exit(2);
}

void	normal_exit(t_exec *cmds_list)
{
	int	exit_status;

	printf("exit\n");
	if (cmds_list->old_stdin != -1)
		close(cmds_list->old_stdout);
	if (cmds_list->old_stdout != -1)
		close(cmds_list->old_stdin);
	if (!cmds_list->cmd_array[1])
	{
		store_or_free(NULL, NULL, false, true);
		exit(0);
	}
	exit_status = ft_atol(cmds_list->cmd_array[1]);
	exit((unsigned char) exit_status);
}

void	func_exit(t_exec **cmds)
{
	int		i;
	char	*tmp;

	i = -1;
	tmp = (*cmds)->cmd_array[1];
	if (!tmp)
		return (normal_exit(*cmds));
	if (tmp && (*cmds)->cmd_array[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", STDERR_FILENO);
		(*cmds)->data->exit_status = 1;
		return ;
	}
	while (tmp[++i])
	{
		if (ft_isalpha(tmp[i]))
			control_alpha(*cmds);
	}
	i = -1;
	while (tmp[++i])
	{
		if (!ft_isdigit(tmp[i]) && tmp[i] != '-' && tmp[i] != '+')
			control_alpha(*cmds);
	}
	normal_exit(*cmds);
}
