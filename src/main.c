/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/10/04 22:13:32 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal;

int	arg_check(int argc, char **argv, char **envp)
{
	if (argc > 1)
		return (1);
	if (argv[1] != NULL)
		return (1);
	if (!envp)
		return (1);
	return (0);
}

__int8_t	do_next_iteration(char *line, t_exec *exec, __int8_t err, int *exit)
{
	if (!exec)
	{
		if (err == SYNTAX_ERROR)
			*exit = 2;
		return (true);
	}
	if (!exec->cmd_array[0])
	{
		free_all(line, exec, NULL, false);
		return (true);
	}
	return (false);
}

void	clean_all(t_env *env_list)
{
	free_env_list(env_list);
	rl_clear_history();
}

void	run_minishell(t_env *env_list, char **envp, t_exec *exec)
{
	if (exec->data->num_pipe < 1)
		exec_shell(&exec, &env_list, envp, exec->data);
	else
		runtime_shell(exec, envp, exec->data, &env_list);
}

void	no_line_exit(t_env *env_list)
{
	free_env_list(env_list);
	exit(EXIT_FAILURE);
}

void	loop(t_env *env_list, int exit_status, char **envp)
{
	char		*line;
	t_exec		*exec;
	t_data		*data;
	__int8_t	error;

	while (42)
	{
		line = read_prompt(env_list);
		if (!line)
			clean_all(env_list);
		if (g_signal)
			exit_status = 128 + g_signal;
		g_signal = 0;
		data = NULL;
		exec = ft_parse(line, &error, env_list, exit_status);
		if (do_next_iteration(line, exec, error, &exit_status))
			continue ;
		if (!exec->data)
		{
			free_all(line, exec, env_list, false);
			continue ;
		}
		store_or_free(line, exec, true, false);
		run_minishell(env_list, envp, exec);
		exit_status = exec->data->exit_status;
		free_all(line, exec, env_list, false);
	}
}

int	main(int argc, char **argv, char **envp)
{
	int		exit_status;
	t_env	*env_list;

	if (arg_check(argc, argv, envp) > 0)
		return (FAILURE);
	env_list = NULL;
	store_env_list(envp, &env_list);
	init_signal();
	exit_status = 0;
	loop(env_list, exit_status, envp);
	clean_all(env_list);
	return (exit_status);
}
