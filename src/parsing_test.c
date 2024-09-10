/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_test.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 15:34:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/10 12:45:28 by sokaraku         ###   ########.fr       */
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

void	print_path(t_tokens *head)
{
	while (head)
	{
		if (head->type == CMD)
			printf("Path of %s is %s\n", head->word, head->path);
		head = head->next;
	}
}

int main(int ac, char **av, char **env)
{
	int			ret;
	char		*line;
	char		*tmp;
	t_tokens	*head;
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
	ret = check_if_cmd(head, env);
	if (ret <= 0)
		return(printf("Error during command checking\n"), free_tokens(head), free(tmp), FAILURE);
	print_tokens(head);
	printf("Checking syntax and setting IDs\n");
	ret = full_check(&head);
	if (ret <= 0)
		return (printf("Syntax error\n"), free_tokens(head), free(tmp), FAILURE);
	printf("Creating commands arrays...\n")
		
	printf("Tokens are : \n");
	print_tokens(head);
	free_tokens(head);
	free(tmp);
}
