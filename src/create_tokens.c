/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_tokens.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 17:34:13 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/10 15:44:02 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		if (*end != 0)
		{
			if (*(str - 1) != *str)
				checks++;
		}
	}
	if (checks == 2)
		return (true);
	return (false);
}

/**
 * @brief If the first character
 * @param
 * @returns
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
	end += skip_tab_spaces(str);
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
	char		*str;

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
	end += skip_tab_spaces(str);
	str = ft_substr(*line, 0, end);
	if (!str)
		return (NULL);
	return ((*line) += end, str);
}

/**
 * @brief Creates a linked list of tokens, based on an input line read from
 * the command line.
 * @param line The input to tokenize.
 * @returns A list of tokens. Returns NULL if line is null.(null si !line?).
 */
t_test	*create_tokens(char *line)
{
	t_test	*tokens;
	char	*str;

	str = get_token(&line, 0, 0, 0);
	if (!str)
		return (NULL);
	tokens = new_token(str, 1);
	tokens->type = find_token_type(tokens->word);
	while (*line)
	{
		str = get_token(&line, 0, 0, 0);
		if (!str)
			return (free_tokens(tokens->head), NULL);
		tokens->next = new_token(str, 0);
		if (!tokens->next)
			return (free_tokens(tokens->head), NULL);
		tokens = tokens->next;
		tokens->type = find_token_type(tokens->word);
	}
	return (tokens->head);
}

int	main(void)
{
	t_test	*head;
	t_test	*tokens;
	char	*line;

	line = readline(">>> ");
	tokens = create_tokens(line);
	head = tokens;
	while (tokens)
	{
		printf("[%d] --> %s\n", tokens->type, tokens->word);
		tokens = tokens->next;
	}
	free(line);
	free_tokens(head);
}

// int main(void)
// {
// 	t_test	*tokens;

// 	while (1)
// 	{
// 		tokens = create_tokens(readline(">>> "));
// 		while (tokens->next)
// 		{
// 			printf("[%d] --> %s\n", tokens->type, tokens->word);
// 			tokens = tokens->next;
// 		}
// 		printf("[%d] --> %s\n", tokens->type, tokens->word);
// 		free_tokens(tokens->head);
// 	}
// }