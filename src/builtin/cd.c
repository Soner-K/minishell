/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:01 by sumseo            #+#    #+#             */
/*   Updated: 2024/10/04 12:40:09 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define ERR_MESS "minishell: cd: too many arguments\n"

int	is_cd(char *str)
{
	char	*echo;
	int		i;

	i = 0;
	echo = "cd";
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

void	func_cd(t_exec *cmds) //MODIFIED
{
	char	*rel_paths[2];
	int		path_int;
	int		i;

	path_int = 0;
	rel_paths[0] = "..";
	rel_paths[1] = ".";
	i = 0;
	if (!cmds->cmd_array[1])
		return ;
	else if (cmds->cmd_array[2])
		return (cmds->data->exit_status = 1, ft_putstr_fd(ERR_MESS, 2), (void)i);
	else
	{
		while (i < 2)
		{
			if (ft_strcmp(cmds->cmd_array[1], rel_paths[i]) == 0)
			{
				path_int = i + 1;
				break ;
			}
			i++;
		}
	}
	func_path(path_int, cmds->cmd_array[1], cmds);
}

void	func_path(int path_int, char *path, t_exec *cmds) //MODIFIED
{
	if (path_int > 0)
		func_relative_cd(path_int);
	else
		func_absolute_cd(path, cmds);
}

void	func_relative_cd(int path_int)
{
	if (path_int == 1)
		chdir("..");
	else if (path_int == 2)
		chdir(".");
}

void	func_absolute_cd(char *dir, t_exec *cmds) //MODIFIED
{
	DIR	*dir_info;

	dir_info = opendir(dir);
	if (!dir_info)
	{
		ft_putstr_fd("cd: ", STDERR_FILENO);
		ft_putstr_fd(dir, STDERR_FILENO);
		ft_putstr_fd(": No such file or directory\n", STDERR_FILENO);
		cmds->data->exit_status = 1;
	}
	else
		chdir(dir);
}
