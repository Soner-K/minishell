/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:15 by sumseo            #+#    #+#             */
/*   Updated: 2024/10/04 17:02:12 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_unset(char *str)
{
	char	*echo;
	int		i;

	if (!str)
		return (0);
	i = 0;
	echo = "unset";
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

void	func_unset(t_exec **cmds, t_env **env)
{
	int		i;
	t_env	*current;
	t_env	*next;

	if (!(*cmds)->cmd_array[1])
		return ;
	current = *env;
	while (current)
	{
		next = current->next;
		i = 1;
		while ((*cmds)->cmd_array[i])
		{
			if (ft_strncmp(current->variable, (*cmds)->cmd_array[i],
					ft_strlen((*cmds)->cmd_array[i])) == 0
				&& current->variable[ft_strlen((*cmds)->cmd_array[i])] == '=')
			{
				delete_one_env(env, (*cmds)->cmd_array[i]);
				break ;
			}
			i++;
		}
		current = next;
	}
}
