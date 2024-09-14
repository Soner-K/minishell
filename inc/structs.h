/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:25 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/12 20:48:37 by sokaraku         ###   ########.fr       */
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
 * @param id_cmd The id of the command.
 * @param type The type of token (see t_type).
 * @param word The word (or content) of the node.
 * @param cmd_array The array of commands.
 * @param path If a variable is a command, the path to the executable.
 * (not used for now).
 * @param next Pointer to the next node.
 * @param prev Pointer to the previous node.
 * @param head Pointer to the head of the list.
 *
 */
typedef struct t_tokens
{
	__int8_t		quotes;
	short int		n_quotes;
	int				id_cmd;
	int				old_stdin;
	int				old_stdout;
	t_type			type;
	char			*word;
	char			**cmd_array;
	char			*path;
	struct t_tokens	*next;
	struct t_tokens	*prev;
	struct t_tokens	*head;
}					t_tokens;

/**
 * @param rights_infile The rights of the infile.
 * @param rights_outfile The rights of the outfile.
 * @param is_heredoc Boolean to check if the infile is a heredoc.
 * @param infile The infile.
 * @param outfile The outfile.
 */
typedef struct s_files
{
	__int8_t		rights_infile;
	__int8_t		rights_outfile;
	bool			is_heredoc;
	char			*infile;
	char			*outfile;
}					t_files;

/**
 * @param builtin Boolean to check if the command is a builtin.
 * @param path The path to the executable.
 * @param cmd_array The array of commands.
 * @param files_info The files informations.
 * @param next Pointer to the next node.
 */
typedef struct s_exec
{
	bool			builtin;
	char			*path;
	char			**cmd_array;
	t_files			*files_info;
	struct s_exec	*next;
}					t_exec;

typedef struct t_env
{
	char			*variable;
	struct t_env	*next;
	struct t_env	*prev;

}					t_env;

typedef struct t_data
{
	int				exit_status;
}					t_data;

#endif