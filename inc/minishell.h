/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:11 by sokaraku          #+#    #+#             */
/*   Updated: 2024/07/18 19:13:43 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs.h"

//				-->utils.c

t_tokens	*new_node_token(char *word, bool is_head);
bool		is_valid_separator(char *sep);
char		*merge_strings(char *s1, char *s2);

//				-->tokenization_utils.c

void		free_one_token(t_tokens *node);
void		free_tokens(t_tokens *head);
t_tokens	*last_token(t_tokens *lst);
__int8_t	add_token(t_tokens **lst, t_tokens *to_add);

//				-->tokenization_utils2.c

__int8_t	find_one_token(char c);
__int8_t	find_token_type(char *str);
char		is_separator(char c);
short int	skip_tab_spaces(char *str);

//				-->create_tokens.c

t_tokens	*create_tokens(char *line);

//				-->path_finding.c

char		*find_path(char *cmd, char **env, bool *alloc_fail);
__int8_t	check_if_cmd(t_tokens *head, char **env);

//				-->exec_utils.c

char		**get_cmd(t_tokens **head);
void		prep_execution(t_tokens **head);
int			do_pipe(t_tokens **head, char **env);

//				-->parsing.c

// bool		check_operators(t_tokens *node);
// void		set_redirections(t_tokens **head);
// bool		check_redirections(t_tokens **head);
// bool		check_redirection_syntax(t_tokens *head);
bool		check_all_redirections(t_tokens **head);
#endif