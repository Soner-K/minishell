/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:52:04 by sokaraku          #+#    #+#             */
/*   Updated: 2024/10/04 20:45:56 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_env_and_quit(t_env *env_list);

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
	t_tokens	*t;
	t_exec		*e;

	t = create_tokens(line);
	if (!t)
		return (free_env_and_quit(env_list), NULL);
	if (quotes_handler(t, CLOSED_QUOTES_CHECK) == false)
		return (*error = UNCLOSED_QUOTES, free_tokens(t, true), NULL);
	quotes_handler(t, QUOTES_MARKING_MODE);
	if (extract_all(t, env_list, last_exit) == ALLOCATION_FAILURE)
		return (free_tokens(t, true), free_env_and_quit(env_list), NULL);
	if (quotes_handler(t, QUOTES_REMOVING_MODE) == FAILURE)
		return (free_tokens(t, true), free_env_and_quit(env_list), NULL);
	if (full_check(&t) == false)
		return (*error = SYNTAX_ERROR, free_tokens(t, true), NULL);
	if (set_cmds_arrays(&t) == ALLOCATION_FAILURE)
		return (free_tokens(t, true), free_env_and_quit(env_list), NULL);
	e = create_exec_lst(t, t, env_list);
	if (!e)
		return (free_tokens(t, true), free_env_and_quit(env_list), NULL);
	if (find_cmd_type(e, env_list) == ALLOCATION_FAILURE)
		return (free_tokens(t, true), free_env_and_quit(env_list), NULL);
	return (free_tokens(t, false), *error = SUCCESS, e);
}

static void	free_env_and_quit(t_env *env_list)
{
	free_env_list(env_list);
	exit(EXIT_FAILURE);
}
