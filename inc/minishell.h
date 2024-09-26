/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:11 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/26 18:43:08 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs.h"

// global vraibles for signal
extern int	g_signal;

//							UTILS
//				-->utils.c

bool		is_builtin(char *cmd);
short int	count_char(char *str, char c);
t_tokens	*new_node_token(char *word, bool is_head);
char		*merge_strings(char *s1, char *s2, char c);

//				-->cmd_finding.c

// char		*find_path(char *cmd, char **env, bool *alloc_fail);
__int8_t	find_cmd_type(t_exec *head, t_env *env_list);

//				-->memory_handler.c
void		free_exec(t_exec *exec_head, bool all);
void		free_all(char *line, t_exec *exec, t_env *env_list, bool free_env);
void		free_tokens(t_tokens *head, bool all);
void		store_or_free(char *line, t_exec *exec, bool store, bool free_env);
void		free_env_list(t_env *env_list);

//							PARSING
//				-->create_tokens.c

t_tokens	*create_tokens(char *line);

//				-->ft_parse.c

t_exec		*ft_parse(char *line, __int8_t *error, t_env *env_list,
				int last_exit);
//				-->prep_exec.c

__int8_t	set_node_exec(t_exec *exec, t_tokens *token, int id_cmd);
void		set_files_info(t_files *files, t_tokens *token);
t_exec		*create_exec_lst(t_tokens *head, t_tokens *first, t_env *env_list);

//				-->prep_exec_utils.c

t_exec		*new_node_exec(void);
void		lst_addback_exec(t_exec **head, t_exec *add);
t_data		*set_data_struct(t_tokens *tokens, t_exec *exec, t_env *env_list);
void		all_my_homies_hate_the_norm(t_tokens **head, t_exec *itr,
				int id_cmd);
//				-->redirections_setting.c

void		set_redirections_type(t_tokens **head);

//				-->get_cmd_array.c

__int8_t	set_cmds_arrays(t_tokens **head);

//				-->syntax_checker.c

bool		full_check(t_tokens **head);

//				-->tokenization_utils.c

void		free_one_token(t_tokens *node);
t_tokens	*last_token(t_tokens *lst);
__int8_t	add_token(t_tokens **lst, t_tokens *to_add);

//				-->tokenization_utils2.c

__int8_t	find_one_token(char c);
__int8_t	find_token_type(char *str);
char		is_separator(char c);
short int	skip_tab_spaces(char *str);

//							EXPAND
//				-->expand_utils.c

short int	count_expands(char *str);
void		reset_negative_characters(t_tokens *head);
bool		check_if_edge_characters(char c, bool first_char);
bool		check_expand_syntax(char *str, int *start, int *end);
bool		expand_inside_single_quotes(t_tokens *node);

//				-->str_utils.c

char		*ft_strslice(char *str, int start, int end, bool *alloc_fail);
char		*ft_strreplace(char *str, char *add, int start, int end);

//				-->expand.c

// char		*getenv_from_env_list(char *var, t_env *env_list, t_env *first);
__int8_t	extract_all(t_tokens *head, t_env *env_list, int last_exit_status);

//				-->quotes.c

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
void		free_lists(t_tokens *first);

// 				-->exec_utils.c
int			parse_path(char **cmds, char *path);
void		init_child(t_exec **cmds_list, char **env_copy);
void		exec_shell_builtin(t_exec **cmds_list, int builtin_check,
				t_env **env_list);
void		exec_shell(t_exec **exec_list, t_env **env_list, char **env_copy,
				t_data *data);

//				-->heredoc.c
void		write_heredoc(char *str, int tmp);
void		init_heredoc(t_exec *cmds_list);
void		open_heredoc(t_exec *cmds_list);
void		call_heredoc(t_exec *cmds_list);

//				-->pipe_init.c
int			getfile(t_exec **cmds_list);
void		close_pipe_files(t_exec *cmds_list);
void		wait_pipe_files(t_data *pipe_info);
void		pipe_init(t_data *pipe_info, t_exec *cmds_list, int i);
void		redirection(t_exec *cmds_list, t_data *pipe_info, int i);

//				-->pipe_utils.c
int			count_cmds(t_exec *cmds_list);
void		close_no_file(t_exec *cmds_list);
void		close_parent(t_exec *head, t_data *pipe_info);

//				-->redirect_init.c
void		only_redirection(t_exec **cmds_list);
void		first_cmd(t_exec *cmds_list);
void		last_cmd(t_exec *cmds_list);
void		middle_cmd(t_exec *cmds_list);

//				-->runtime.c
t_data		*init_pipeinfo(t_exec *cmds_list);
void		init_child_pipe(t_exec *cmds_list, char **env_copy);
void		redirect_and_init(t_exec *cmds_list, t_data *data, int i,
				t_env **env_list);
void		exec_pipe(t_exec *cmds_list, char **env_copy, int i,
				t_env **env_list);
void		file_close(t_exec *cmds_list, t_data *data, int fork_id);

// 				-->create_prompt.c
char		*read_prompt(t_env *env_list);
void		runtime_shell(t_exec *cmds_list, char **env_copy, t_data *data,
				t_env **env_list);

// 				-->init_signal.c
void		init_signal(void);
void		sig_handler(int signal);
void		sig_handler_quit(int signal);
void		sig_handler_forks(int signal);
void		sig_handler_wait(int signal);
void		get_status(int fork_id, int status, t_data *data);
void		sig_handler_heredoc(int signal);

// 				-->exit_status.c
void		close_extra_files(t_exec *cmds_list);
void		close_files(t_exec *cmds_list);
void		close_no_file(t_exec *cmds_list);
void		init_pid_array(t_data *pipe_info);
void		store_pid(t_data *pipe_info, pid_t fork_id);
void		wait_pipe_files(t_data *data);

// 				-->runtime_utils.c
void		runtime_signal(void);
void		runtime_free(t_exec *cmds_list);

//				-->handle_heredoc.c
void		launch_heredoc(t_exec **exec_list, t_data *data, char **env_copy,
				t_env **env_list);
#endif