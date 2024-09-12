/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_prompt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 11:20:54 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/12 11:03:11 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*read_prompt(void)
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
		exit(1);
	free(pretty_prompt);
	add_history(line);
	return (line);
}
