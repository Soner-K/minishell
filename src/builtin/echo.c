/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:06:26 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/10 10:30:44 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_echo(char *str)
{
	char	*echo;
	int		i;

	i = 0;
	echo = "echo";
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

int	print_echo(t_tokens *cmds, int i, int nextline_flag)
{
	while (cmds->cmd_array[i])
	{
		printf("%s", cmds->cmd_array[i]);
		i++;
	}
	if (!nextline_flag)
	{
		printf("\n");
		return (2);
	}
	else
		return (1);
}

void	func_echo(t_tokens *cmds)
{
	int	nextline_flag;
	int	i;
	int	j;

	nextline_flag = 0;
	i = 1;
	while (cmds->cmd_array[i] && cmds->cmd_array[i][0] == '-')
	{
		j = 1;
		while (cmds->cmd_array[i][j] == 'n')
			j++;
		if (cmds->cmd_array[i][j] == '\0')
		{
			nextline_flag = 1;
			i++;
		}
		else
			break ;
	}
	if (print_echo(cmds, i, nextline_flag) == 2)
		return ;
}
