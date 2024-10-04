/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:25 by sokaraku          #+#    #+#             */
/*   Updated: 2024/10/04 19:35:11 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libs.h"

/**
 * @brief Types' enumeration.
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
 * @brief Tokens' structure (linked list).
 * @param quotes Signed char taking the ASCII code of the quote that
 * enclose a word, if there is one.
 * @param id_cmd Identifier of a portion in the input line.
 * @param type The type of token (see t_type).
 * @param word The word (or content) of the node.
 * @param cmd_array The command array, launched in the execution part.
 * @param next Pointer to the next node.
 * @param prev Pointer to the previous node.
 * @param head Pointer to the head of the list.
 *
 */
typedef struct t_tokens
{
	__int8_t		quotes;
	bool			is_directory;	
	int				id_cmd;
	t_type			type;
	char			*word;
	char			**cmd_array;
	struct t_tokens	*next;
	struct t_tokens	*prev;
	struct t_tokens	*head;
}					t_tokens;

/**
 * @brief Information about a file.
 * @param rights The reading, writing and execution rights of a file.
 * @param type The type of file (INREDIR, OUTREDIR, HEREDOC, APPENDREDIR.
 * See t_type).
 * @param name The name of the file.
 */
typedef struct s_fdata
{
	bool			is_heredoc;
	__int8_t		rights;
	t_type			type;
	char			*name;
	char			*final_name;
	char			*del;
}					t_fdata;

/**
 * @brief Information about infile and outfile.
 * @param infile_info Information of an infile (rights, type, name).
 * @param outfile_info Information of an outfile (rights, type, name).
 */
typedef struct s_files
{
	t_fdata			*infile_info;
	t_fdata			*outfile_info;
	bool			opening_failure;
}					t_files;

/**
 * @brief Personal environment of minishell (linked list).
 * @param variable String containing the name and content of
 * an environment variable.
 * @param next Pointer to the next node of the list.
 * @param prev Pointer to the previous node of the list.
 */
typedef struct t_env
{
	char			*variable;
	struct t_env	*next;
	struct t_env	*prev;
}					t_env;

/**
 * @brief Structure containing essential informations for the execution.
 * @param exit_status Exit status of the parsed and executed input line.
 * @param total_cmds Number of commands inside the input line.
 * @param counter
 * @param num_pipe Number of pipes in the input line.
 * @param pids Array of process IDs.
 * @param limiter The limiter of the heredoc.
 * @param env_list Minishell's environment list.
 */
typedef struct t_data
{
	int				exit_status;
	int				total_cmds;
	int				counter;
	int				num_pipe;
	pid_t			*pids;
	char			*limiter;
	t_env			*env_list;
	int				total_hd;
	int				*fd_hd;
	char			**hd_files;
}					t_data;

/**
 * @brief Structure containing essential informations for the execution.
 * @param builtin Boolean indicating if the command is a builtin.
 * @param path The path of the command.
 * @param cmd_array The command array.
 * @param next Pointer to the next node of the list.
 * @param prev Pointer to the previous node of the list.
 * @param old_stdin The old standard input.
 * @param old_stdout The old standard output.
 * @param infile The file descriptor of the infile.
 * @param outfile The file descriptor of the outfile.
 * @param pipe_fdo The write end file descriptor of the pipe.
 * @param pipe_fdi The read end file descriptor of the pipe.
 * @param old_infile The old infile.
 * @param old_outfile The old outfile.
 * @param files_info The files informations.
 * @param data The data structure.
 */
typedef struct s_exec
{
	bool			builtin;
	char			*path;
	char			**cmd_array;
	struct s_exec	*next;
	struct s_exec	*prev;
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

#endif