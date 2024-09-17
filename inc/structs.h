/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:25 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/17 14:03:48 by sumseo           ###   ########.fr       */
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

typedef struct s_fdata
{
	__int8_t		rights;
	t_type			type;
	char			*name;
}					t_fdata;

typedef struct s_files
{
	t_fdata			*infile_info;
	t_fdata			*outfile_info;

}					t_files;

typedef struct t_data
{
	// exit status should be initiated as 0;
	// this value is changed depending on the last cmd executed
	int				exit_status;
	pid_t			*pids;
	char			*limiter;
	// number of command -> how many commands in the total cmd line
	// ls | ls | ls -> 3
	int				total_cmds;
	// how many pids needed for forking. this is for counting purpose ?
	// this should be init as 0 in parsing
	int				counter;
	// number of pipe;
	// so if it is cat | cat ->should be 1
	int				num_pipe;
}					t_data;

typedef struct s_exec
{
	bool			builtin;
	char			*path;
	char			**cmd_array;
	struct s_exec	*next;
	struct s_exec	*prev;
	int				id_cmd;
	int				old_stdin;
	int				old_stdout;
	int				infile;
	int				outfile;
	int				pipe_fdo;
	int				pipe_fdi;
	int				old_infile;
	int				old_outfile;
	t_files			*files_info;
	t_data			*data;
}					t_exec;

typedef struct t_env
{
	char			*variable;
	struct t_env	*next;
	struct t_env	*prev;
}					t_env;

#endif