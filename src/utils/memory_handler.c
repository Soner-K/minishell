/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:02:58 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/20 12:55:32 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_env_list(t_env *env_list)
{
	t_env	*tmp;

	while (env_list)
	{
		tmp = env_list;
		env_list = env_list->next;
		free(tmp->variable);
		free(tmp);
	}
}

void	store_or_free(char *line, t_exec *exec, bool store, bool free_env)
{
	static char		*line_store = NULL;
	static t_exec	*exec_store = NULL;
	static t_env	*env_list_store = NULL;

	if (store)
	{
		line_store = line;
		exec_store = exec;
		env_list_store = exec->data->env_list;
		return ;
	}
	free_all(line_store, exec_store, env_list_store, free_env == true);
}

void	free_all(char *line, t_exec *exec, t_env *env_list, bool free_env)
{
	if (line)
		free(line);
	if (exec)
	{
		free(exec->data->pids);
		free(exec->data);
		free_exec(exec, true);
	}
	if (free_env)
		free_env_list(env_list);
}

/**
 * @brief Free a list of tokens.
 * @param head The head of the tokens' list.
 * @returns void.
 */
void	free_tokens(t_tokens *tokens_head, bool all)
{
	t_tokens	*tmp;
	__int8_t	id_cmd;

	if (!tokens_head)
		return ;
	id_cmd = 0;
	while (tokens_head)
	{
		tmp = tokens_head;
		tokens_head = tokens_head->next;
		if (all)
			free(tmp->word);
		else if (all == false && tmp->type > APPENDREDIR)
			free(tmp->word);
		if (all && id_cmd == tmp->id_cmd)
		{
			if (tmp->cmd_array)
			{
				free_arrs((void **)tmp->cmd_array);
				id_cmd++; // COME BACK check id code everywhere
			}
		}
		free(tmp);
	}
}

// need to free data struct outside
void	free_exec(t_exec *exec_head, bool all)
{
	t_exec *tmp;

	while (exec_head)
	{
		tmp = exec_head;
		exec_head = exec_head->next;
		if (all)
			free(tmp->files_info->infile_info->name);
		free(tmp->files_info->infile_info);
		if (all)
			free(tmp->files_info->outfile_info->name);
		free(tmp->files_info->outfile_info);
		free(tmp->files_info);
		free(tmp->path);
		if (all)
			free_arrs((void **)tmp->cmd_array);
		free(tmp);
	}
}