/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:20:54 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/26 18:35:18 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_prompt(t_env *env_list)
{
	char	cwd[1024];
	char	*pretty_prompt;
	char	*line;

	getcwd(cwd, sizeof(cwd));
	pretty_prompt = ft_strjoin(cwd, "> ");
	if (!pretty_prompt)
	{
		free_env_list(env_list);
		exit(EXIT_FAILURE);
	}
	line = readline(pretty_prompt);
	if (!line)
	{
		free(pretty_prompt);
		free_env_list(env_list);
		exit(EXIT_FAILURE);
	}
	free(pretty_prompt);
	add_history(line);
	return (line);
}
