/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 13:48:11 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/24 18:24:58 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libs.h"

t_tokens	*new_node_token(char *word, bool is_head);
t_cmds		*new_node_cmd(bool is_head);

__int8_t	add_token(t_tokens **lst, t_tokens *to_add);
void		free_one_token(t_tokens *node);
void		free_tokens(t_tokens *head);
short int	skip_tab_spaces(char *str);
t_tokens	*last_token(t_tokens *lst);

__int8_t	find_one_token(char c);
__int8_t	find_token_type(char *str);
char		is_separator(char c);

t_tokens	*create_tokens(char *line);
t_tokens	*merge_tokens(t_tokens *head);

char		*find_path(char *cmd, char **env, bool *alloc_fail);
__int8_t	check_if_cmd(t_tokens *head, char **env);

void		free_cmd_array(char **strs, short int size);
short int	get_array_size(t_tokens *head);
char		**get_cmd_array(t_tokens **head_tokens, t_cmds *cmds_head);
t_cmds		*get_cmds_list(t_tokens **head);
#endif