/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:34:13 by sokaraku          #+#    #+#             */
/*   Updated: 2024/07/30 19:06:54 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void	print_list(t_tokens *tokens)
{
	if (!tokens)
		return ;
	while (tokens->next)
	{
		printf("[%d] --> %s\n", tokens->type, tokens->word);
		tokens = tokens->next;
	}
	printf("[%d] --> %s\n", tokens->type, tokens->word);
	// printf("BACK\n");
	// while (tokens->prev)
	// {
	// 	printf("[%d] --> %s\n", tokens->type, tokens->word);
	// 	tokens = tokens->prev;
	// }
	// printf("[%d] --> %s\n", tokens->type, tokens->word);
}
/*o need protection in if, cuz add_token checks for null*/
/*redo the function by just creating a new pointer instead of malloc ?*/
t_tokens	*delete_whitespaces(t_tokens *tokens)
{
	t_tokens	*new;
	t_tokens	*tmp;
	short int	i;

	i = 0;
	new = NULL;
	while (tokens)
	{
		if (tokens->type != SPACE_ && tokens->type != TAB_)
		{
			tmp = new_node_token(tokens->word, ++i == 1);
			if (add_token(&new, tmp) == -1)
				return (free_tokens(new->head), NULL);
		}
		tmp = tokens;
		tokens = tokens->next;
		if (tmp->type == SPACE_ || tmp->type == TAB_)
			free(tmp->word);
		free(tmp);
	}
	if (new)
		return (new->head);
	return (NULL);
}

/**
 * @brief Checks if the tokenization process for one token should be stopped
 * (i.e one full token was found).
 * @param str A pointer to a character inside an input string
 * for which to do the check.
 * @param s_q Counter for the number of single quotes.
 * @param d_q Counter for the number of double quotes.
 * @param end A pointer to the index of the last checked character.
 * @returns true (1) if the tokenization can be stopped
 * and false (0) otherwise.
 */
static bool	end_copy(char *str, short int s_q, short int d_q, short int *end)
{
	__int8_t	checks;

	if (!str)
		return (true);
	checks = 0;
	if (!is_odd(s_q) && !is_odd(d_q))
		checks++;
	if (is_separator(*str))
	{
		if (*end != 0 && *(str - 1) != *str)
			checks++;
	}
	if (checks == 2)
		return (true);
	return (false);
}

/**
 * @brief If the first character read in the function get_token is a
 * separator, copies that separator and only that separator until the
 * next different character.
 * @param  line Adress of the pointer to the last read character
 * from the input.
 * @returns A string which size is at least one and containing only
 * one type of separator. If memory allocation fails, returns NULL.
 */
static char	*tokenize_one_separator(char **line)
{
	short int	end;
	char		*str;
	char		sep;

	str = *line;
	sep = **line;
	end = 0;
	while (*str && *str == sep)
	{
		end++;
		str++;
	}
	str = ft_substr(*line, 0, end);
	if (!str)
		return (NULL);
	(*line) += end;
	return (str);
}

/**
 * @brief Finds one token inside an input line.
 * @param line A double pointer to the input string. A double pointer is used
 * to actualize the value pointed by line after each tokenization.
 * @param end A short int that will store the index of the last character to
 * tokenize (norm issue).
 * @param s_q  Single quotes counter (norm issue).
 * @param d_q  Double quotes counter (norm issue).
 * @returns A string composed of the same and adjacent tokens.
 * Returns NULL if allocation failed.
 */
static char	*get_token(char **line, short int end, short int s_q, short int d_q)
{
	char	*str;

	if (is_separator(**line))
	{
		str = tokenize_one_separator(line);
		return (str);
	}
	str = *line;
	while (*str)
	{
		if (*str == '\'')
			s_q++;
		if (*str == '"')
			d_q++;
		if (end_copy(str, s_q, d_q, &end))
			break ;
		str++;
		end++;
	}
	str = ft_substr(*line, 0, end);
	if (!str)
		return (NULL);
	(*line) += end;
	return (str);
}

/**
 * @brief Creates a linked list of tokens, based on an input line read from
 * the command line.
 * @param line The input to tokenize.
 * @returns A list of tokens. Returns NULL if line is null.(null si !line?).
 */
t_tokens	*create_tokens(char *line)
{
	t_tokens	*tokens;
	char		*str;

	str = get_token(&line, 0, 0, 0);
	if (!str)
		return (NULL);
	tokens = new_node_token(str, 1);
	if (!tokens)
		return (NULL);
	tokens->type = find_token_type(tokens->word);
	while (*line)
	{
		str = get_token(&line, 0, 0, 0);
		if (!str)
			return (free_tokens(tokens), NULL);
		if (add_token(&tokens, (new_node_token(str, 0))) == -1)
			return (free_tokens(tokens), NULL);
	}
	tokens = delete_whitespaces(tokens);
	if (!tokens)
		return (NULL);
	return (tokens);
}

bool	check(char *str)
{
	short int i = 0;

	while (str[i])
	{
		if (str[i] == '$')
			return (true);
		i++;
	}
	return (false);
}

void	print_var(char *str, int start, int end)
{
	while (start <= end)
	{
		ft_putchar_fd(str[start], 1);
		start++;
	}
	printf("\n");
}

int	main(int ac, char **av, char **env)
{
	t_tokens	*head;
	t_tokens	*tokens;
	char		*line;
	char		*tmp;
	short int	start;
	short int	end;

	(void)ac;
	(void)av;
	(void)env;
	line = readline(">>> ");
	tmp = line;
	tokens = create_tokens(line);
	head = tokens;
	while (tokens)
	{
		printf("[%d] --> %s\n", tokens->type, tokens->word);
		if (check(tokens->word))
		{
			if (check_expand_syntax(tokens->word, &start, &end))
			{
				printf("start %d et end %d\n", start, end);
				ft_putstr_fd("Expand valid var is = ", 1);
				print_var(tokens->word, start, end);
				extract_variable(tokens);
				printf("%s\n", tokens->word);
			}
			else
				printf("Expand not valid\n");
		}
		tokens = tokens->next;
	}
	printf("\n\n\n\n");
	if (check_all_redirections(&head) == 1)
	{
		tokens = head;
		while (tokens)
		{
			printf("[%d] --> %s\n", tokens->type, tokens->word);
			tokens = tokens->next;
		}
	}
	else
		return (free(tmp), 1);
	
}

// int	main(int ac, char **av, char **env)
// {
// 	t_tokens *tokens;
// 	(void)ac;
// 	(void)av;
// 	(void)env;

// 	while (1)
// 	{
// 		tokens = create_tokens(readline(">>> "));
// 		check_if_cmd(tokens, env);
// 		if (!tokens->next)
// 		{
// 			printf("[%d] --> %s", tokens->type, tokens->word);
// 			if (tokens->path)
// 				printf(" %s\n", tokens->path);
// 			else
// 				printf("\n");
// 			free_tokens(tokens->head);
// 		}
// 		else
// 		{
// 			while (tokens->next)
// 			{
// 				printf("[%d] --> %s", tokens->type, tokens->word);
// 				if (tokens->path)
// 					printf(" %s\n", tokens->path);
// 				else
// 					printf("\n");
// 				tokens = tokens->next;
// 			}
// 			printf("[%d] --> %s\n", tokens->type, tokens->word);
// 			if (tokens->path)
// 				printf(" %s\n", tokens->path);
// 			else
// 				printf("\n");
// 			free_tokens(tokens->head);
// 		}
// 	}
// }