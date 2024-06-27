/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:25 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/27 14:42:48 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include "libs.h"

typedef enum e_type
{
	NONE,
	WORD,
	CMD,
	INREDIR,
	OUTREDIR,
	HEREDOC,
	APPENDREDIR,
	SPACE_,
	TAB_,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	OPERATOR,
	PIPE,
}					t_type;

typedef struct t_tokens
{
	t_type			type;
	char			*word;
	char			*path;
	struct t_tokens	*next;
	struct t_tokens	*prev;
	struct t_tokens	*head;
}					t_tokens;

typedef struct s_cmds
{
	char			**cmd;
	t_type			type;
	char			*file_redir;
	char			*here_doc_sep;
	struct s_cmds	*next;
	struct s_cmds	*head;
}					t_cmds;

typedef struct s_args
{
	char			**env;
	t_tokens		*tokens;
	struct s_args	*next;
}					t_args;

#endif