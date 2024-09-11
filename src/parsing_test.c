/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/11 14:08:11 by sumseo           ###   ########.fr       */
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

/*Will segfault if one of the function sends an error code
because the tokens will be freed, nothing to be alarmed of,
a simple reorganization of the main will handle that.
*/
int	main(int argc, char **argv, char **envp)
{
	char		*line;
	char		*tmp;
	t_env		*env_list;
	t_tokens	*head;

	env_list = NULL;
	if (argc > 1)
		exit_program("Minishell does not take arguments.");
	if (argv[1] != NULL)
		exit_program("Minishell does not take arguments.");
	while (42)
	{
		init_signal();
		line = read_prompt();
		if (line == NULL)
			continue ;
		tmp = line;
		head = create_tokens(line);
		store_env_list(envp, &env_list);
		display_env_list(env_list);
		printf("Tokens are : \n");
		// print_tokens(head);
		// printf("\nChecking redirection syntax : \n");
		full_check(&head);
		// printf("\nTokens now are : \n");
		// print_tokens(head);
		// printf("\nExpand, tokens are : \n");
		mark_quotes(head);
		extract_all(head);
		// print_tokens(head);
		// printf("\nRemoving quotes, tokens are : \n");
		quotes_remover(head);
		printf("Last CHECK \n");
		print_tokens(head);
		printf("Last CHECK \n");
		// just for testing multi command and pipe
		if (head->type > 0)
		{
			exec_shell(&head, &env_list, envp);
			printf("It is a normal command\n");
		}
		// It is only one command -> built-in check
		// it if is multiple commands -> built-in check
	}
	free(tmp);
	free_tokens(head);
	free(tmp);
	// rl_clear_history();
}
