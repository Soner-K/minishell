/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 12:02:58 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/30 16:15:41 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Frees the environment list.
 * @param env_list The head of the environment list.
 * @returns void.
 */
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

/**
 * @brief Stores or frees the line, the execution list and the environment list.
 * @param line The line to store or free.
 * @param exec The head of the execution list.
 * @param store A boolean being true (1) if the line, the execution list and the
 * environment list must be stored, and false (0) otherwise.
 * @param free_env A boolean being true (1) if the environment list must be
 * freed, and false (0) otherwise.
 * @returns void.
 */
void	store_or_free(char *line, t_exec *exec, bool store, bool free_env)
{
	static char		*line_store = NULL;
	static t_exec	*exec_store = NULL;
	static t_env	*env_list_store = NULL;

	if (store)
	{
		line_store = line;
		exec_store = exec;
		// if (exec && exec->data) COME BACK
		env_list_store = exec->data->env_list;
		return ;
	}
	free_all(line_store, exec_store, env_list_store, free_env);
}

/**
 * @brief Frees a list of tokens.
 * @param head The head of the tokens' list.
 * @returns void.
 */
void	free_tokens(t_tokens *tokens_head, bool all, t_exec *exec)
{
	t_tokens	*tmp;
	__int8_t	id_cmd;

	if (!tokens_head)
		return ;
	id_cmd = 0;
	exec = NULL;
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
				id_cmd++;
			}
		}
		free(tmp);
	}
}

/**
 * @brief Frees a list of executions.
 * @param exec_head The head of the executions' list.
 * @param all A boolean being true (1) if all the memory must be freed, and
 * false (0) otherwise.
 * @returns void.
 */
void	free_exec(t_exec *exec_head, bool all)
{
	t_exec	*tmp;

	while (exec_head)
	{
		tmp = exec_head;
		exec_head = exec_head->next;
		if (all)
		{
			free(tmp->files_info->infile_info->name);
			if (tmp->files_info->infile_info->is_heredoc)
				free(tmp->files_info->infile_info->del);
			free(tmp->files_info->outfile_info->name);
			free_arrs((void **)tmp->cmd_array);
		}
		free(tmp->files_info->infile_info);
		free(tmp->files_info->outfile_info);
		free(tmp->files_info);
		free(tmp->path);
		free(tmp);
	}
}

/**
 * @brief Frees all the memory allocated for the shell.
 * @param line The line to free.
 * @param exec The head of the execution list.
 * @param env_list The head of the environment list.
 * @param free_env A boolean being true (1) if the environment list must be
 * freed and false (0) otherwise.
 * @returns void.
 */
void	free_all(char *line, t_exec *exec, t_env *env_list, bool free_env)
{
	if (line)
		free(line);
	if (exec)
	{
		free(exec->data->pids);
		free(exec->data->fd_hd);
		// free_hd_files(exec->data->hd_files);
		// free(exec->data);
		free_exec(exec, true);
	}
	if (free_env)
		free_env_list(env_list);
}
