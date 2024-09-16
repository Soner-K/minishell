/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 13:12:07 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/16 15:38:01 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	print_tokens(t_tokens *tokens)
// {
// 	if (!tokens)
// 		return ;
// 	while (tokens)
// 	{
// 		printf("[%d] --> %s ", tokens->type, tokens->word);
// 		if (tokens->id_cmd != -1)
// 			printf("ID : %d\n", tokens->id_cmd);
// 		else
// 			printf("\n");
// 		tokens = tokens->next;
// 	}
// }

static void	print_exec_lst(t_exec *exec)
{
	t_files	*tmp;

	if (!exec)
		return ;
	printf("Printing exec list\n");
	while (exec->next)
	{
		printf("\nCommand's path %s\nCommand array \n", exec->path);
		tmp = exec->files_info;
		print_strs(exec->cmd_array);
		if (tmp->infile_info->name)
		{
			printf("Infle name %s infile rights %d infile type %d\n",
				tmp->infile_info->name, tmp->infile_info->rights,
				tmp->infile_info->type);
		}
		if (tmp->outfile_info->name)
		{
			printf("outfile name %s outfile rights %d outfile type %d\n",
				tmp->outfile_info->name, tmp->outfile_info->rights,
				tmp->outfile_info->type);
		}
		exec = exec->next;
	}
}

int	test_function(int ac, char **av, char **env)
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
		return (printf("tokens creation error"), free(tmp), FAILURE);
	printf("Tokens are : \n");
	print_tokens(head);
	printf("Checking for unclosed quotes...\n");
	ret = check_if_closed_quotes(head);
	if (ret <= 0)
		return (printf("Unclosed quotes\n"), free_tokens(head), free(tmp),
			FAILURE);
	mark_quotes(head);
	printf("Expanding...\n");
	ret = extract_all(head);
	if (ret <= 0)
		return (printf("Error during expand\n"), free_tokens(head), free(tmp),
			FAILURE);
	print_tokens(head);
	printf("Removing quotes, tokens are : \n");
	ret = quotes_remover(head);
	if (ret <= 0)
		return (printf("Error during quotes removal\n"), free_tokens(head),
			free(tmp), FAILURE);
	print_tokens(head);
	printf("Checking for commands...\n");
	ret = find_cmd_type(head, env);
	if (ret <= 0)
		return (printf("Error during command checking\n"), free_tokens(head),
			free(tmp), FAILURE);
	printf("Checking syntax\n");
	ret = full_check(&head);
	if (ret <= 0)
		return (printf("Syntax error\n"), free_tokens(head), free(tmp),
			FAILURE);
	printf("Tokens are : \n");
	print_tokens(head);
	set_cmds_arrays(&head);
	print_tokens(head);
	exec = create_exec_lst(head);
	print_exec_lst(exec);
	// free_tokens(head);
	printf("TEST\n");
	printf("Esec cmmad array %s\n", (exec->cmd_array)[0]);
	free_exec_nodes(exec);
	free(tmp);
	return (SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	test_function(ac, av, env);
}