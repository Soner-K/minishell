/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:52:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/22 16:54:54 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief 
 * @brief Receives an input line, parses it and returns an execution list.
 * @param line The input line
 * @param error A pointer to a variable storing the kind of error that
 * happened (ALLOCATION_FAILURE, UNCLOSED_QUOTES, SYNTAX_ERROR).
 * @param last_exit Code of the last exit status.
 * @returns NULL if an error occured, with error set appropriately, or the
 * execution list if the parsing was successful.
 */
t_exec	*ft_parse(char *line, __int8_t *error, t_env *env_list, int last_exit)
{
	t_tokens	*tokens;
	t_exec		*exec;

	if (!line[0])
		return (NULL);
	tokens = create_tokens(line);
	if (!tokens)
		return (*error = ALLOCATION_FAILURE, NULL);
	if (quotes_handler(tokens, CLOSED_QUOTES_CHECK) == false)
		return (*error = UNCLOSED_QUOTES, free_tokens(tokens, true), NULL);
	quotes_handler(tokens, QUOTES_MARKING_MODE);
	if (extract_all(tokens, env_list, last_exit) == ALLOCATION_FAILURE)
		return (*error = ALLOCATION_FAILURE, free_tokens(tokens, true), NULL);
	if (quotes_handler(tokens, QUOTES_REMOVING_MODE) == FAILURE)
		return (*error = ALLOCATION_FAILURE, free_tokens(tokens, true), NULL);
	if (full_check(&tokens) == false)
		return (*error = SYNTAX_ERROR, free_tokens(tokens, true), NULL);
	if (set_cmds_arrays(&tokens) == FAILURE)
		return (*error = ALLOCATION_FAILURE, free_tokens(tokens, true), NULL);
	exec = create_exec_lst(tokens, tokens, env_list);
	if (!exec)
		return (*error = ALLOCATION_FAILURE, free_tokens(tokens, false), NULL);
	if (find_cmd_type(exec, env_list) == ALLOCATION_FAILURE)
		return (*error = ALLOCATION_FAILURE, free_tokens(tokens, true), NULL);
	return (free_tokens(tokens, false), exec);
}
