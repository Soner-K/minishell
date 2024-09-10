/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:01 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/10 10:24:46 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	func_cd(t_tokens *cmds)
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
	func_path(path_int, cmds->cmd_array[1]);
}

void	func_path(int path_int, char *path)
{
	if (path_int > 0)
		func_relative_cd(path_int);
	else
		func_absolute_cd(path);
}

void	func_relative_cd(int path_int)
{
	if (path_int == 1)
		chdir("..");
	else if (path_int == 2)
		chdir(".");
}

void	func_absolute_cd(char *dir)
{
	DIR	*dir_info;

	dir_info = opendir(dir);
	if (!dir_info)
		printf("cd: %s: No such file or directory\n", dir);
	else
		chdir(dir);
}
