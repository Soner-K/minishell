/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:11 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/07 17:37:15 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs.h"

void		add_token(t_test **lst, t_test *to_add);
void		free_tokens(t_test *head);
short int	skip_tab_spaces(char *str);
t_test		*new_token(char *word, bool is_head);
t_test		*last_token(t_test *lst);

__int8_t	find_one_token(char c);
__int8_t	find_token(char *str);
bool		is_separator(char c);

t_test		*create_tokens(char *line);
t_test		*merge_tokens(t_test *head);

#endif