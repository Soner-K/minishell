/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:25 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/17 10:56:23 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_tokens
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
}					t_tokens;

typedef struct s_test
{
	t_tokens		type;
	char			*word;
	char			*path;
	struct s_test	*next;
	struct s_test	*prev;
	struct s_test	*head;
}					t_test;

typedef struct s_args
{
	char			**env;
	t_test			*tokens;
	struct s_args	*next;
}					t_args;

#endif