/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:11 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/09 15:32:13 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs.h"

//							UTILS
//				-->utils.c

short int	count_char(char *str, char c);
t_tokens	*new_node_token(char *word, bool is_head);
char		*merge_strings(char *s1, char *s2);

//				-->cmd_finding.c

char		*find_path(char *cmd, char **env, bool *alloc_fail);
__int8_t	check_if_cmd(t_tokens *head, char **env);

//							PARSING
//				-->create_tokens.c

t_tokens	*create_tokens(char *line);

//				-->redirections_setting.c

void		set_redirections_type(t_tokens **head);

//				-->syntax_checker.c

bool		full_check(t_tokens **head);

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

//							EXPAND
//				-->expand_utils.c

bool		check_if_edge_characters(char c, bool first_char);
bool		check_expand_syntax(char *str, short int *start, short int *end);
bool		expand_inside_single_quotes(char *str);
char		*ft_strslice(char *str, int start, int end, bool *alloc_fail);
char		*ft_strreplace(char *str, char *add, int start, int end);

//				-->expand.c

__int8_t	extract_variable(t_tokens *node);
__int8_t	extract_all(t_tokens *head);

//				-->quotes.c

__int8_t	check_if_closed_quotes(t_tokens *head);
__int8_t	quotes_remover(t_tokens *head);
void		mark_quotes(t_tokens *head);

#endif