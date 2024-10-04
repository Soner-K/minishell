/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:09:42 by sumseo            #+#    #+#             */
/*   Updated: 2024/10/04 12:42:05 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pwd(char *str)
{
	char	*echo;
	int		i;

	i = 0;
	echo = "pwd";
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

void	func_pwd(void) //MODIFIED pwd always print directory no matter the args
{
	char	cwd[1024];
	// int		count_cmds;

	// count_cmds = count_arr_length(cmds->cmd_array);
	// if (count_cmds < 2)
	// {
	getcwd(cwd, sizeof(cwd));
	printf("%s\n", cwd);
	// }
	// else
	// 	printf("pwd: too many arguments\n");
}

int	count_arr_length(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
		i++;
	return (i);
}
