/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/17 15:25:02 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	arg_check(int argc, char **argv)
{
	if (argc > 1)
		return (1);
	if (argv[1] != NULL)
		return (1);
	return (0);
}
void	free_args(char *line, t_exec *exec)
{
	free(line);
	free_exec_nodes(exec);
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
	init_signal();
	store_env_list(envp, &env_list);
	while (42)
	{
		line = read_prompt();
		exec = ft_parse(line, envp, &error);
		data = exec->data;
		if (data->num_pipe < 1)
			exec_shell(&exec, &env_list, envp, data);
		else
			runtime_shell(exec, envp, data, &env_list);
		printf("DATA EXIT STATUS CHECK %d\n", data->exit_status);
		free(line);
		free_exec_nodes(exec);
	}
	return (SUCCESS);
}
