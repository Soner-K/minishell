/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/17 13:58:41 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_env		*env_list;
	t_exec		*exec;
	__int8_t	error;
	t_data		*data;

	env_list = NULL;
	if (argc > 1)
		exit_program("Minishell does not take arguments.");
	if (argv[1] != NULL)
		exit_program("Minishell does not take arguments.");
	init_signal();
	store_env_list(envp, &env_list);
	while (42)
	{
		line = read_prompt();
		exec = ft_parse(line, envp, &error);
		data = exec->data;
		printf("Exec shell called\n");
		exec_shell(&exec, &env_list, envp, data);
		runtime_shell(exec, envp, data, &env_list);
		free(line);
		free_exec_nodes(exec);
	}
	return (SUCCESS);
}
