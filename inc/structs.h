/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:25 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/04 16:11:17 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef enum e_tokens
{
	NONE,
	WORD,
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
}				t_tokens;



typedef struct s_test
{
	t_tokens		type;
	char			*word;
	struct s_test	*next;
	struct s_test	*head;
}				t_test;

#endif