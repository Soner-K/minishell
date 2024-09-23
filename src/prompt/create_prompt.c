/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:20:54 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/23 12:08:20 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_prompt(t_env *env_list)
{
	char	cwd[1024];
	char	*pretty_prompt;
	char	*line;

	(void)env_list;
	getcwd(cwd, sizeof(cwd));
	pretty_prompt = ft_strjoin(cwd, ">");
	if (!pretty_prompt)
		return (NULL);
	line = readline(pretty_prompt);
	if (line == NULL)
	{
		free(pretty_prompt);
		return (NULL);
	}
	free(pretty_prompt);
	add_history(line);
	return (line);
}
