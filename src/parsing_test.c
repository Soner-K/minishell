/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/14 17:12:43 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// bool	check(char *str)
// {
// 	short int	i;

// 	i = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 			return (true);
// 		i++;
// 	}
// 	return (false);
// }

void	print_var(char *str, int start, int end)
{
	while (start <= end)
	{
		ft_putchar_fd(str[start], 1);
		start++;
	}
	printf("\n");
}

void	print_tokens(t_tokens *tokens)
{
	if (!tokens)
		return ;
	while (tokens)
	{
		printf("[%d] --> %s ", tokens->type, tokens->word);
		if (tokens->id_cmd != -1)
			printf("ID : %d\n", tokens->id_cmd);
		else
			printf("\n");
		tokens = tokens->next;
	}
}

// void	print_tokens_and_strs(t_tokens *tokens)
// {
// 	char		*line;
// 	char		*tmp;
// 	t_env		*env_list;
// 	t_tokens	*head;

// 	env_list = NULL;
// 	if (argc > 1)
// 		exit_program("Minishell does not take arguments.");
// 	if (argv[1] != NULL)
// 		exit_program("Minishell does not take arguments.");
// 	init_signal();
// 	while (42)
// 	{
// 		line = read_prompt();
// 		if (line == NULL)
// 			continue ;
// 		tmp = line;
// 		head = create_tokens(line);
// 		store_env_list(envp, &env_list);
// 		// display_env_list(env_list);
// 		// printf("Tokens are : \n");
// 		// print_tokens(head);
// 		// printf("\nChecking redirection syntax : \n");
// 		full_check(&head);
// 		// printf("\nTokens now are : \n");
// 		// print_tokens(head);
// 		// printf("\nExpand, tokens are : \n");
// 		mark_quotes(head);
// 		extract_all(head);
// 		// print_tokens(head);
// 		// printf("\nRemoving quotes, tokens are : \n");
// 		quotes_remover(head);
// 		// printf("Last CHECK \n");
// 		// print_tokens(head);
// 		// printf("Last CHECK \n");
// 		// just for testing multi command and pipe
// 		if (head->type > 0)
// 		{
// 			exec_shell(&head, &env_list, envp);
// 			// printf("It is a normal command\n");
// 		}
// 		// It is only one command -> built-in check
// 		// it if is multiple commands -> built-in check
// 		free(tmp);
// 		free_tokens(head);
// 		free(tmp);
// 	}
// 	// rl_clear_history();
// 	if (!tokens)
// 		return ;
// 	while (tokens)
// 	{
// 		printf("[%d] --> %s STRS : \n", tokens->type, tokens->word);
// 		print_strs(tokens->cmd_array);
// 		printf("\n");
// 		tokens = tokens->next;
// 	}
// }

int	main(int argc, char **argv, char **envp)
{
	int ret;
	char *line;
	char *tmp;
	t_env *env_list;
	// t_data *data;
	t_tokens *head;
	t_exec *exec;
	env_list = malloc(sizeof(env_list));
	if (!env_list)
		return (0);
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
		if (!head)
			return (printf("tokens creation error"), free(tmp), FAILURE);
		// printf("Tokens are : \n");
		// print_tokens(head);
		// mark_quotes(head);
		// printf("Expanding...\n");
		ret = extract_all(head);
		if (ret <= 0)
			return (printf("Error during expand\n"), free_tokens(head),
				free(tmp), FAILURE);
		// print_tokens(head);
		// printf("Checking for unclosed quotes...\n");
		ret = check_if_closed_quotes(head);
		if (ret < 0)
			return (printf("Unclosed quotes\n"), free_tokens(head), free(tmp),
				FAILURE);
		// printf("Removing quotes, tokens are : \n");
		ret = quotes_remover(head);
		if (ret <= 0)
			return (printf("Error during quotes removal\n"), free_tokens(head),
				free(tmp), FAILURE);
		// print_tokens(head);
		// printf("Checking for commands...\n");
		ret = find_cmd_type(head, envp);
		if (ret <= 0)
			return (printf("Error during command checking\n"),
				free_tokens(head), free(tmp), FAILURE);
		// printf("Checking syntax\n");
		ret = full_check(&head);
		if (ret <= 0)
			return (printf("Syntax error\n"), free_tokens(head), free(tmp),
				FAILURE);
		// printf("Tokens are : \n");
		// print_tokens(head);
		set_cmds_arrays(&head);
		// print_tokens(head);
		exec = new_node_exec();
		set_node_exec(exec, head);
		printf("node exec check %s\n", exec->cmd_array[0]);
		printf("node exec check %s\n", exec->cmd_array[1]);
		exec_shell(&exec, &env_list, envp);
		// printf("node next check %s\n", exec->next->cmd_array[0]);

		free_tokens(head);
		free(tmp);
	}
}