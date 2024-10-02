/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/10/02 17:43:47 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		g_signal;

int	arg_check(int argc, char **argv)
{
	if (argc > 1)
		return (1);
	if (argv[1] != NULL)
		return (1);
	return (0);
}

void	p(t_exec *exec)
{
	while (exec)
	{
		printf("infile is %s\n", exec->files_info->infile_info->name);
		if (exec->cmd_array)
			printf("cmd array 0 %s\n", exec->cmd_array[0]);
		if (exec->files_info->infile_info->is_heredoc)
			printf("delimiter is %s\n", exec->files_info->infile_info->del);
		if (exec->files_info->infile_info->type)
			printf("TYPE is %u\n", exec->files_info->infile_info->type);
		exec = exec->next;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	int			exit_status;
	t_env		*env_list;
	t_exec		*exec;
	__int8_t	error;
	t_data		*data;

	if (arg_check(argc, argv) > 0)
		return (FAILURE);
	if (!envp)
		exit(EXIT_FAILURE);
	env_list = NULL;
	store_env_list(envp, &env_list);
	init_signal();
	exit_status = 0;
	while (42)
	{
		line = read_prompt(env_list);
		if (!line)
		{
			free_env_list(env_list);
			exit(EXIT_FAILURE);
		}
		if (g_signal)
			exit_status = 128 + g_signal;
		g_signal = 0;
		if (line == NULL)
			break ;
		data = NULL;
		exec = ft_parse(line, &error, env_list, exit_status);
		p(exec);
		if (!exec)
		{
			if (error == SYNTAX_ERROR)
				exit_status = 2;
			continue ;
		}
		data = exec->data;
		if (!data)
		{
			free_all(line, exec, env_list, false);
			continue ;
		}
		store_or_free(line, exec, env_list, true);
		if (data->num_pipe < 1)
			exec_shell(&exec, &env_list, envp, data);
		else
			runtime_shell(exec, envp, data, &env_list);
		exit_status = data->exit_status;
		free_all(line, exec, env_list, false);
	}
	free_env_list(env_list);
	rl_clear_history();
	return (exit_status);
}
