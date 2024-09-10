/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:25 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/10 10:26:59 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libs.h"

/**
 * @param INREDIR
 * @param OUTREDIR
 * @param HEREDOC
 * @param APPENDREDIR
 * @param PIPE
 * @param EXPAND
 * @param WORD
 * @param SPACE_
 * @param TAB_
 * @param NONE
 */
typedef enum e_type
{
	INREDIR,
	OUTREDIR,
	HEREDOC,
	APPENDREDIR,
	PIPE,
	EXPAND,
	WORD,
	SPACE_,
	TAB_,
	NONE,
}					t_type;

/**
 * @param quotes Signed char acting as a boolean. Takes the value 1 if
 * there is quotes inside a node, and 0 otherwise.
 * @param type The type of token (see t_type).
 * @param word The word (or content) of the node.
 * @param path If a variable is a command, the path to the executable.
 * (not used for now).
 * @param next Pointer to the next node.
 * @param prev Pointer to the previous node.

	* @param head Pointer to the head of the list. (Need to check if the adress pointed
 * is valid throughout all the program, since the head of the list moves a lot.)
 *
 */
typedef struct t_tokens
{
	__int8_t		quotes;
	t_type			type;
	char			*word;
	char			*path;
	struct t_tokens	*next;
	struct t_tokens	*prev;
	struct t_tokens	*head;
	// just for blocking the error
	char			**cmd_array;
	int				old_stdin;
	int				old_stdout;
}					t_tokens;

typedef struct t_env
{
	char			*variable;
	struct t_env	*next;
	struct t_env	*prev;

}					t_env;

#endif