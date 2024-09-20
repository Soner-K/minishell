/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_signal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 12:42:20 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/20 16:17:44 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sig_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 1);
		rl_on_new_line();
		rl_redisplay();
		g_signal = 2;
	}
}

void	init_signal(void)
{
	signal(SIGINT, sig_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	get_status(int fork_id, int status, t_data *data)
{
	waitpid(fork_id, &status, 0);
	if (WIFEXITED(status))
		data->exit_status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		data->exit_status = WTERMSIG(status) + 128;
}

void	sig_handler_quit(int signal)
{
	(void)signal;
	ft_putstr_fd("Quit (core dumped)\n", STDOUT_FILENO);
}

void	sig_handler_forks(int signal)
{
	(void)signal;
	g_signal = signal;
	close(0);
}

void	sig_handler_wait(int signal)
{
	(void)signal;
	g_signal = signal;
}