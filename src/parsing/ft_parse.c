/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:52:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/17 09:40:52 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Receives an input line, parses it and returns an execution list.
 * @param line The input line
 * @param envp The environment variable
 * @param error A pointer to a variable storing the kind of error that
 * happened (ALLOCATION_FAILURE, UNCLOSED_QUOTES, SYNTAX_ERROR).
 * @returns NULL if an error occured, with error set appropriately, or the
 * execution list if the parsing was successful.
 */
t_exec	*ft_parse(char *line, char *envp[], __int8_t *error)
{
	t_tokens	*tokens;
	t_exec		*exec;

	tokens = create_tokens(line);
	if (!tokens)
		return (*error = ALLOCATION_FAILURE, NULL);
	if (quotes_handler(tokens, CLOSED_QUOTES_CHECK) == false)
		return (*error = UNCLOSED_QUOTES, free_tokens(tokens), NULL);
	quotes_handler(tokens, QUOTES_MARKING_MODE);
	if (extract_all(tokens) == ALLOCATION_FAILURE)
		return (*error = ALLOCATION_FAILURE, free_tokens(tokens), NULL);
	if (quotes_handler(tokens, QUOTES_REMOVING_MODE) == FAILURE)
		return (*error = ALLOCATION_FAILURE, free_tokens(tokens), NULL);
	if (find_cmd_type(tokens, envp) == ALLOCATION_FAILURE)
		return (*error = ALLOCATION_FAILURE, free_tokens(tokens), NULL);
	if (full_check(&tokens) == false)
		return (*error = SYNTAX_ERROR, free_tokens(tokens), NULL);
	if (set_cmds_arrays(&tokens) == FAILURE)
		return (*error = ALLOCATION_FAILURE, free_tokens(tokens), NULL);
	exec = create_exec_lst(tokens);
	printf("EXEC %s\n", exec->cmd_array[0]);
	if (!exec)
		return (*error = ALLOCATION_FAILURE, free_tokens(tokens), NULL);
	return (exec);
}
