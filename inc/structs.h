/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:25 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/10 13:11:07 by sumseo           ###   ########.fr       */
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
 * @param WORD
 * @param EXPAND
 * @param BUILTIN
 * @param CMD
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
	WORD,
	BUILTIN,
	CMD,
	SPACE_,
	TAB_,
	NONE,
}					t_type;

/**
 * @param quotes Signed char acting taking the ASCII code of the quote that
 * enclose a word, if there is one.
 * @param n_quotes The number of quotes enclosing a word. Allows to check
 * if quotes are closed.
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
	short int		n_quotes;
	int				id_cmd;
	t_type			type;
	char			*word;
	char			*path;
	char			**cmd_array;
	struct t_tokens	*next;
	struct t_tokens	*prev;
	struct t_tokens	*head;
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