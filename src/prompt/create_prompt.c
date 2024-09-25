/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:20:54 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/24 17:15:46 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_prompt(void)
{
	char	cwd[1024];
	char	*pretty_prompt;
	char	*line;

	getcwd(cwd, sizeof(cwd));
	pretty_prompt = ft_strjoin(cwd, "> ");
	if (!pretty_prompt)
		exit(EXIT_FAILURE);
	line = readline(pretty_prompt);
	if (!line)
	{
		free(pretty_prompt);
		exit(EXIT_FAILURE);
	}
	free(pretty_prompt);
	add_history(line);
	return (line);
}
