/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:11 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/17 13:03:15 by sumseo           ###   ########.fr       */
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

//				-->ft_parse.c

t_exec		*ft_parse(char *line, char *envp[], __int8_t *error);

//				-->prep_exec.c

t_exec		*create_exec_lst(t_tokens *head);

//				-->prep_exec_utils.c

t_exec		*new_node_exec(void);
void		lst_addback_exec(t_exec **head, t_exec *add);
void		free_exec_nodes(t_exec *head);

//				-->redirections_setting.c

void		set_redirections_type(t_tokens **head);

//				-->get_cmd_array.c
void		set_id(t_tokens *head);
__int8_t	set_cmds_arrays(t_tokens **head);

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
__int8_t	quotes_handler(t_tokens *head, __int8_t mode);

// 				-->find_builtin.c
int			which_builtin(t_exec *cmds);
void		exec_builtin(int func, t_exec **cmds, t_env **env);

// 				-->unset.c
int			is_unset(char *str);
void		func_unset(t_exec **cmds, t_env **env);

// 				-->cd.c
int			is_cd(char *str);
void		func_cd(t_exec *cmds);
void		func_path(int path_int, char *path);
void		func_relative_cd(int path_int);
void		func_absolute_cd(char *dir);

// 				-->echo.c
int			is_echo(char *str);
int			print_echo(t_exec *cmds, int i, int nextline_flag);
void		func_echo(t_exec *cmds);

// 				-->env.c
int			is_env(char *str);
void		func_env(t_exec *cmds, t_env **env);
void		display_env_list(t_env *env_list);

// 				-->exit.c
int			is_exit(char *str);
void		control_alpha(char *s, t_exec *cmds_list);
void		control_many_args(t_exec *cmds_list);
void		normal_exit(t_exec *cmds_list);
void		func_exit(t_exec **cmds);

// 				-->export.c
int			is_export(char *str);
t_env		*sort_env(t_env *env_copy, t_env *current);
void		export_without_args(t_env **env);
int			check_variable(t_env **env, char *new_var, char *value);
void		func_export(t_exec **cmds, t_env **env);

//				-->export_utils.c
int			check_export_variable(char s);
char		*func_variable(char *s);
char		*func_value(char *s);
char		*func_join_words(char *variable, char *value);

// 				-->pwd.c
int			is_pwd(char *str);
void		func_pwd(t_exec *cmds);
int			count_arr_length(char **argv);

// 				-->env_utils.c
void		push_env_list(t_env **env_list, const char *str, int len);
void		store_env_list(char **envp, t_env **env_list);
void		delete_one_env(t_env **env_list, char *new_var);
void		replace_one_env(t_env **env_list, char *env_val, char *variable,
				char *value);

//				-->error.c
void		exit_program(char *s);

// 				-->exec_utils.c
int			parse_path(char **cmds, char *path);
void		init_child(t_exec **cmds_list, char **env_copy);
void		exec_shell_builtin(t_exec **cmds_list, int builtin_check,
				t_env **env_list);
void		exec_shell(t_exec **exec_list, t_env **env_list, char **env_copy,
				t_data *data);

//				-->heredoc.
void		write_heredoc(char *str, int tmp);
void		init_heredoc(t_exec *cmds_list);
void		open_heredoc(t_exec *cmds_list);
void		call_heredoc(t_exec *cmds_list);

//				-->pipe_init.c
int			getfile(t_exec **cmds_list);
void		close_pipe_files(t_exec *cmds_list);
void		wait_pipe_files(t_data *pipe_info);
void		pipe_init(t_data *pipe_info, t_exec *cmds_list, int i,
				t_data *data);
void		redirection(t_exec *cmds_list, t_data *pipe_info, int i);

//				-->pipe_utils.c
void		pipe_null_check(void);
int			count_cmds(t_exec *cmds_list);
void		close_no_file(t_exec *cmds_list);
void		close_parent(t_exec *head, t_data *pipe_info);

//				-->redirect_init.c
void		heredoc_check(t_exec *cmds_list);
void		only_redirection(t_exec **cmds_list);
void		first_cmd(t_exec *cmds_list);
void		last_cmd(t_exec *cmds_list);
void		middle_cmd(t_exec *cmds_list);

//				-->runtime.c
t_data		*init_pipeinfo(t_exec *cmds_list);
void		init_child_pipe(t_exec *cmds_list, t_data *pipe_info,
				char **env_copy, int i);
// 				-->create_prompt.c
char		*read_prompt(void);

// 				-->init_signal.c
void		init_signal(void);
void		sig_handler(int signal);
void		close_extra_files(t_exec *cmds_list);
void		close_files(t_exec *cmds_list);
void		runtime_shell(t_exec *cmds_list, char **env_copy, t_data *data,
				t_env **env_list);

// 				-->debugging.c
void		print_tokens(t_tokens *tokens);
void		print_var(char *str, int start, int end);
void		init_pid_array(t_data *pipe_info);
void		store_pid(t_data *pipe_info, pid_t fork_id);
#endif