/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:45:23 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/23 11:54:39 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_env_list(t_env **env_list, const char *str, int len)
{
	t_env	*element;
	t_env	*last;

	last = *env_list;
	element = malloc(sizeof(t_env));
	if (!element)
		return ;
	element->variable = malloc(len + 1);
	if (!element->variable)
	{
		free(element);
		return ;
	}
	ft_strlcpy(element->variable, str, len + 1);
	element->next = NULL;
	if (*env_list == NULL)
	{
		element->prev = NULL;
		*env_list = element;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = element;
	element->prev = last;
}

void	store_env_list(char **envp, t_env **env_list)
{
	int	i;
	int	len;

	i = 0;
	while (envp[i])
	{
		len = ft_strlen(envp[i]);
		push_env_list(env_list, envp[i], len);
		i++;
	}
	(*env_list)->prev = NULL;
}

void	delete_one_env(t_env **env_list, char *variable)
{
	t_env	*current;

	current = *env_list;
	while (current != NULL)
	{
		if (ft_strncmp(variable, current->variable, ft_strlen(variable)) == 0)
		{
			free(current->variable);
			if (*env_list == current)
				*env_list = current->next;
			if (current->prev != NULL)
				current->prev->next = current->next;
			free(current);
			return ;
		}
		current = current->next;
	}
}

void	replace_one_env(t_env **env_list, char *env_val, char *variable,
		char *value)
{
	t_env	*current;
	char	*new_var;

	if (value == NULL || strlen(value) == 0)
		value = "''";
	new_var = malloc(strlen(variable) + strlen(value) + 2);
	if (new_var == NULL)
	{
		perror("Failed to allocate memory for new_var");
		return ;
	}
	strcpy(new_var, variable);
	strcat(new_var, value);
	current = *env_list;
	while (current != NULL)
	{
		if (strcmp(current->variable, env_val) == 0)
		{
			free(current->variable);
			current->variable = new_var;
			return ;
		}
		current = current->next;
	}
	free(new_var);
}

t_env	*sort_env(t_env *env_copy, t_env *current)
{
	int		swapped;
	char	*tmp;

	swapped = 1;
	while (swapped)
	{
		swapped = 0;
		current = env_copy;
		while (current && current->next != NULL)
		{
			if (ft_strncmp(current->variable, current->next->variable, 1) > 0)
			{
				tmp = current->variable;
				current->variable = current->next->variable;
				current->next->variable = tmp;
				swapped = 1;
			}
			current = current->next;
		}
	}
	current = env_copy;
	return (current);
}
