/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:11:15 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/17 16:23:36 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_unset(char *str)
{
	char	*echo;
	int		i;

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
	char	*found_value;
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
			found_value = ft_strnstr(current->variable, (*cmds)->cmd_array[i],
					ft_strlen((*cmds)->cmd_array[i]));
			if (found_value && found_value == current->variable)
			{
				delete_one_env(env, (*cmds)->cmd_array[i]);
				break ;
			}
			i++;
		}
		current = next;
	}
}
