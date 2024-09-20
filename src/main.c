/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/20 14:29:22 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_signal;

int	arg_check(int argc, char **argv)
{
	if (argc > 1)
		return (1);
	if (argv[1] != NULL)
		return (1);
	return (0);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*env_list;
	t_exec		*exec;
	__int8_t	error;
	t_data		*data;

	if (arg_check(argc, argv) > 0)
		return (FAILURE);
	env_list = NULL;
	store_env_list(envp, &env_list);
	init_signal();
	while (42)
	{
		line = read_prompt(env_list);
		if (g_signal)
			data->exit_status = 128 + g_signal;
		g_signal = 0;
		exec = ft_parse(line, &error, env_list);
		if (!exec)
			continue ;
		data = exec->data;
		store_or_free(line, exec, env_list, true);
		if (data->num_pipe < 1)
			exec_shell(&exec, &env_list, envp, data);
		else
			runtime_shell(exec, envp, data, &env_list);
		printf("DATA EXIT STATUS CHECK %d\n", data->exit_status);
		free_all(line, exec, env_list, false);
	}
	free_env_list(env_list);
	rl_clear_history();
	return (SUCCESS);
}
