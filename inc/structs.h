/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:25 by sokaraku          #+#    #+#             */
/*   Updated: 2024/07/12 18:09:56 by sokaraku         ###   ########.fr       */
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
	OPERATOR,
	PIPE,
	SPACE_,
	TAB_,
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

typedef struct s_args
{
	char			**env;
	t_tokens		*tokens;
	struct s_args	*next;
}					t_args;

typedef struct s_files
{
	char	*infile;
	char	*outfile;
	int		fds[2];
	int		pid;
	int		ret;
}			t_files;

#endif