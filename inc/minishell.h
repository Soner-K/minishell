/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:11 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/10 14:24:21 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs.h"

//							UTILS

//				-->utils.c

bool		is_builtin(char *cmd);
short int	count_char(char *str, char c);
t_tokens	*new_node_token(char *word, bool is_head);
char		*merge_strings(char *s1, char *s2, char c);

//				-->cmd_finding.c

char		*find_path(char *cmd, char **env, bool *alloc_fail);
__int8_t	find_cmd_type(t_tokens *head, char **env);

//							PARSING
//				-->create_tokens.c

t_tokens	*create_tokens(char *line);

//				-->get_cmd_array.c
void		set_cmds_arrays(t_tokens **head);

//				-->redirections_setting.c

void		set_redirections_type(t_tokens **head);

//				-->get_cmd_array.c
void		set_id(t_tokens *head);
void		set_cmds_arrays(t_tokens **head);

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

// built-in BUILTIN
int			ft_strcmp(const char *s1, const char *s2);
int			which_builtin(t_tokens *cmds);
void		exec_builtin(int func, t_tokens **cmds, t_env **env);

// built-in UNSET
int			is_unset(char *str);
void		func_unset(t_tokens **cmds, t_env **env);

// built-in CD
int			is_cd(char *str);
void		func_cd(t_tokens *cmds);
void		func_path(int path_int, char *path);
void		func_relative_cd(int path_int);
void		func_absolute_cd(char *dir);

// built-in ECHO
int			is_echo(char *str);
int			print_echo(t_tokens *cmds, int i, int nextline_flag);
void		func_echo(t_tokens *cmds);

// built-in ENV
int			is_env(char *str);
void		func_env(t_tokens *cmds, t_env **env);
void		display_env_list(t_env *env_list);

// built-in EXIT
int			is_exit(char *str);
void		control_alpha(char *s, t_tokens *cmds_list);
void		control_many_args(t_tokens *cmds_list);
void		normal_exit(t_tokens *cmds_list);
void		func_exit(t_tokens **cmds);

// built-in EXPORT
int			check_export_variable(char s);
char		*func_variable(char *s);
char		*func_value(char *s);
char		*func_join_words(char *variable, char *value);
int			is_export(char *str);
t_env		*sort_env(t_env *env_copy, t_env *current);
void		export_without_args(t_env **env);
int			check_variable(t_env **env, char *new_var, char *value);
void		func_export(t_tokens **cmds, t_env **env);

// built-in PWD
int			is_pwd(char *str);
void		func_pwd(t_tokens *cmds);
int			count_arr_length(char **argv);

// env
void		push_env_list(t_env **env_list, const char *str, int len);
void		store_env_list(char **envp, t_env **env_list);
void		delete_one_env(t_env **env_list, char *new_var);
void		replace_one_env(t_env **env_list, char *env_val, char *variable,
				char *value);

// error_handler
void		exit_program(char *s);

#endif