/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/16 12:16:49 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_exec	*parsing_init(t_tokens *head, char **envp, t_exec *exec, char *tmp)
{
	int	ret;

	// if (!head)
	// 	return (printf("tokens creation error"), free(tmp), FAILURE);
	printf("Tokens are : \n");
	print_tokens(head);
	mark_quotes(head);
	printf("Expanding...\n");
	ret = extract_all(head);
	if (ret <= 0)
		// return (printf("Error during expand\n"), free_tokens(head),
		free(tmp),
			// 	FAILURE);
			print_tokens(head);
	printf("Checking for unclosed quotes...\n");
	ret = check_if_closed_quotes(head);
	// if (ret < 0)
	// return (printf("Unclosed quotes\n"), free_tokens(head), free(tmp),
	// 	FAILURE);
	printf("Removing quotes, tokens are : \n");
	ret = quotes_remover(head);
	// if (ret <= 0)
	// return (printf("Error during quotes removal\n"), free_tokens(head),
	// 	free(tmp), FAILURE);
	print_tokens(head);
	printf("Checking for commands...\n");
	ret = find_cmd_type(head, envp);
	// if (ret <= 0)
	// return (printf("Error during command checking\n"), free_tokens(head),
	// 	free(tmp), FAILURE);
	printf("Checking syntax\n");
	ret = full_check(&head);
	// if (ret <= 0)
	// 	return (printf("Syntax error\n"), free_tokens(head), free(tmp),
	// 		FAILURE);
	printf("Tokens are : \n");
	print_tokens(head);
	set_cmds_arrays(&head);
	print_tokens(head);
	exec = new_node_exec();
	set_node_exec(exec, head);
	return (exec);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		*tmp;
	t_env		*env_list;
	t_data		*data;
	t_tokens	*head;
	t_exec		*exec;

	env_list = NULL;
	data = NULL;
	exec = NULL;
	if (argc > 1)
		exit_program("Minishell does not take arguments.");
	if (argv[1] != NULL)
		exit_program("Minishell does not take arguments.");
	init_signal();
	store_env_list(envp, &env_list);
	while (42)
	{
		line = read_prompt();
		tmp = line;
		head = create_tokens(line);
		exec = parsing_init(head, envp, exec, tmp);
		// printf("node exec bulilitin check %d\n", exec->builtin);
		// printf("node exec path check %s\n", exec->path);
		// printf("node exec infile info check %s\n", exec->files_info->infile);
		// printf("node exec command check %s\n", exec->cmd_array[0]);
		if (exec->next == NULL)
			exec_shell(&exec, &env_list, envp);
		else
			runtime_shell(exec, envp, data, &env_list);
		free_tokens(head);
		free(tmp);
	}
	rl_clear_history();
}
