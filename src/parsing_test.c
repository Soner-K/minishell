/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/12 14:07:38 by sumseo           ###   ########.fr       */
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
	char		*line;
	char		*tmp;
	t_env		*env_list;
	t_tokens	*head;
	t_data		*data;

	env_list = malloc(sizeof(t_env));
	data = malloc(sizeof(t_data));
	if (argc > 1)
		exit_program("Minishell does not take arguments.");
	if (argv[1] != NULL)
		exit_program("Minishell does not take arguments.");
	if (!data | !env_list)
		exit_program("Memory allocation failed\n");
	init_signal();
	init_exit_stat(data);
	while (42)
	{
		line = read_prompt();
		if (line == NULL)
			continue ;
		tmp = line;
		head = create_tokens(line);
		store_env_list(envp, &env_list);
		// display_env_list(env_list);
		full_check(&head);
		mark_quotes(head);
		extract_all(head);
		quotes_remover(head);
		if (head->type > 0)
		{
			printf("Hello world");
			exec_shell(&head, &env_list, envp);
		}
		// It is only one command -> built-in check
		// it if is multiple commands -> built-in check
		free_tokens(head);
		free(tmp);
	}
}
