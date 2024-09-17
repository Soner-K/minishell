/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 10:45:23 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/17 16:38:29 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	push_env_list(t_env **env_list, const char *str, int len)
{
	t_env	*element;
	t_env	*last;

	last = *env_list;
	element = malloc(sizeof(t_env));
	element->variable = malloc(len + 1);
	ft_strlcpy(element->variable, str, len + 1);
	element->next = NULL;
	if (*env_list == NULL)
	{
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

void	delete_one_env(t_env **env_list, char *var_to_delete)
{
	t_env	*current;
	t_env	*next;
	char	*variable_and;

	variable_and = ft_strjoin(var_to_delete, "=");
	if (!variable_and)
		return ;
	current = *env_list;
	while (current != NULL)
	{
		next = current->next;
		if (ft_strnstr(current->variable, variable_and,
				ft_strlen(current->variable)))
		{
			free(current->variable);
			if (*env_list == current)
				*env_list = next;
			if (current->prev != NULL)
				current->prev->next = next;
			if (next != NULL)
				next->prev = current->prev;
			free(current);
			free(variable_and);
			return ;
		}
		current = next;
	}
	free(variable_and);
}

void	replace_one_env(t_env **env_list, char *env_val, char *variable,
		char *value)
{
	t_env	*current;
	char	*new_var;

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
