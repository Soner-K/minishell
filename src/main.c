/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/16 16:52:02 by sumseo           ###   ########.fr       */
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

	data = NULL;
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
		printf("exec cmd array %s\n", exec->cmd_array[0]);
		// exec_shell(&exec, &env_list, envp, data);
		// free(line);
		// free_exec_nodes(exec);
	}
	return (SUCCESS);
}
