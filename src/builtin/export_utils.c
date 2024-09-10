/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:49:28 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/10 10:27:07 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_export_variable(char s)
{
	if (s == '_' || ft_isalpha(s))
		return (1);
	else
	{
		printf("export : '%c' : not a valid identifier\n", s);
		return (0);
	}
}

char	*func_variable(char *s)
{
	char	*variable;
	char	**split_var;
	char	*variable_join;

	split_var = ft_split(s, '=');
	if (split_var == NULL)
		return (NULL);
	variable = split_var[0];
	if (variable == NULL)
	{
		free(split_var);
		return (NULL);
	}
	variable_join = ft_strjoin(variable, "=");
	free(split_var);
	if (variable_join == NULL)
		return (NULL);
	return (variable_join);
}

char	*func_value(char *s)
{
	char	*value;
	char	**split_var;

	split_var = ft_split(s, '=');
	if (split_var == NULL)
		return (NULL);
	value = split_var[1];
	free(split_var);
	if (value == NULL)
		return (NULL);
	return (value);
}

char	*func_join_words(char *variable, char *value)
{
	char	*joined_string;

	if (variable == NULL || value == NULL)
		return (NULL);
	joined_string = ft_strjoin(variable, value);
	if (joined_string == NULL)
		return (NULL);
	return (joined_string);
}
