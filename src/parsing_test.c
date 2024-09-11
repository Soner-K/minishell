/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/11 15:28:52 by sokaraku         ###   ########.fr       */
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
		if (tokens->id_cmd != - 1)
			printf("ID : %d\n", tokens->id_cmd);
		else
			printf("\n");
		tokens = tokens->next;
	}
}

void	print_tokens_and_strs(t_tokens *tokens)
{
	if (!tokens)
		return ;
	while (tokens)
	{
		printf("[%d] --> %s STRS : \n", tokens->type, tokens->word);
		print_strs(tokens->cmd_array);
		printf("\n");
		tokens = tokens->next;
	}
}

int main(int ac, char **av, char **env)
{
	int			ret;
	char		*line;
	char		*tmp;
	t_tokens	*head;
	t_exec		*exec;
	(void)ac;
	(void)av;

	line = readline(">>> ");
	tmp = line;
	head = create_tokens(line);
	if (!head)
		return(printf("tokens creation error"), free(tmp), FAILURE);
	printf("Tokens are : \n");
	print_tokens(head);

	mark_quotes(head);

	printf("Expanding...\n");
	ret = extract_all(head);
	if (ret <= 0)
		return(printf("Error during expand\n"), free_tokens(head), free(tmp), FAILURE);
	print_tokens(head);

	printf("Checking for unclosed quotes...\n");
	ret = check_if_closed_quotes(head);
	if (ret < 0)
		return(printf("Unclosed quotes\n"), free_tokens(head), free(tmp), FAILURE);
	printf("Removing quotes, tokens are : \n");
	ret = quotes_remover(head);
	if (ret <= 0)
		return(printf("Error during quotes removal\n"), free_tokens(head), free(tmp), FAILURE);
	print_tokens(head);
	printf("Checking for commands...\n");
	ret = find_cmd_type(head, env);
	if (ret <= 0)
		return(printf("Error during command checking\n"), free_tokens(head), free(tmp), FAILURE);
	printf("Checking syntax\n");
	ret = full_check(&head);
	if (ret <= 0)
		return (printf("Syntax error\n"), free_tokens(head), free(tmp), FAILURE);
	printf("Tokens are : \n");
	print_tokens(head);
	set_cmds_arrays(&head);
	print_tokens(head);
	exec = new_node_exec();
	set_node_exec(exec, head);
	free_tokens(head);
	free(tmp);
}

// /*Will segfault if one of the function sends an error code
// because the tokens will be freed, nothing to be alarmed of,
// a simple reorganization of the main will handle that.
// */
// int	main(int argc, char **argv, char **envp)
// {
// 	char *line;
// 	char *tmp;
// 	t_env *env_list;
// 	t_tokens *head;
// 	env_list = NULL;
// 	if (argc > 1)
// 		exit_program("Minishell does not take arguments.");
// 	if (argv[1] != NULL)
// 		exit_program("Minishell does not take arguments.");

// 	while (42)
// 	{
// 		line = readline(">>> ");
// 		tmp = line;
// 		head = create_tokens(line);
// 		store_env_list(envp, &env_list);
// 		// display_env_list(env_list);
// 		// printf("Tokens are : \n");
// 		print_tokens(head);
// 		// printf("\nChecking redirection syntax : \n");
// 		full_check(&head);
// 		// printf("\nTokens now are : \n");
// 		print_tokens(head);
// 		// printf("\nExpand, tokens are : \n");
// 		mark_quotes(head);
// 		extract_all(head);
// 		print_tokens(head);
// 		// printf("\nRemoving quotes, tokens are : \n");
// 		quotes_remover(head);
// 		print_tokens(head);
// 	}
// 	free(tmp);
// 	free_tokens(head);
// 	free(tmp);
// }
