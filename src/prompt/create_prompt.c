/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:20:54 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/20 14:20:35 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_prompt(t_env *env_list)
{
	char	cwd[1024];
	char	*pretty_prompt;
	char	*line;

	getcwd(cwd, sizeof(cwd));
	pretty_prompt = ft_strjoin(cwd, ">");
	if (!pretty_prompt)
		return (NULL);
	line = readline(pretty_prompt);
	if (line == NULL)
	{
		free_all(NULL, NULL, env_list, true);
		free(pretty_prompt);
		exit(0);
	}
	free(pretty_prompt);
	add_history(line);
	return (line);
}
