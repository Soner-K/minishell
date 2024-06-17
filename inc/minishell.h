/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:11 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/17 14:24:29 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs.h"

__int8_t	add_token(t_test **lst, t_test *to_add);
void		free_tokens(t_test *head);
short int	skip_tab_spaces(char *str);
t_test		*new_token(char *word, bool is_head);
t_test		*last_token(t_test *lst);

__int8_t	find_one_token(char c);
__int8_t	find_token_type(char *str);
char		is_separator(char c);

t_test		*create_tokens(char *line);
t_test		*merge_tokens(t_test *head);

char		*find_path(char *cmd, char **env, bool *alloc_fail);
__int8_t	check_if_cmd(t_test *head, char **env);

#endif