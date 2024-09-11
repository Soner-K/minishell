/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:42:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/11 13:16:53 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signal)
{
	char	cwd[1024];
	char	*pretty_prompt;

	if (signal == SIGINT)
	{
		getcwd(cwd, sizeof(cwd));
		pretty_prompt = ft_strjoin(cwd, "$");
		printf("%s ^C\n", pretty_prompt);
		// printf("\n%s", pretty_prompt);
	}
	else if (signal == SIGTERM)
	{
		exit_program("exit");
	}
}
void	init_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGTERM, sig_handler);
	signal(SIGQUIT, sig_handler);
}