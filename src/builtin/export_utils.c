/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 18:49:28 by sumseo            #+#    #+#             */
/*   Updated: 2024/10/04 15:29:22 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define INVALID_IDENTIFIER "!@#%^&*()-+{}[]|:;'\",<>./? \t\n\v\f\r"

bool	is_invalid_char(char c)
{
	__int8_t	i;

	i = -1;
	while (INVALID_IDENTIFIER[++i])
	{
		if (INVALID_IDENTIFIER[i] == c)
			return (true);
	}
	return (false);
}

int	check_export_variable(char *s)
{
	int	i;
	int	count;

	i = -1;
	while (s[++i])
	{
		if (s[i] == '=')
			break ;
	}
	count = i;
	i = -1;
	while (s[++i] && i < count)
	{
		if (is_invalid_char(s[i]))
			return (FAILURE);
	}
	return (SUCCESS);
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
	free_arrs((void **)split_var);
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
	value = ft_strdup(split_var[1]);
	free_arrs((void **)split_var);
	if (!value)
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
