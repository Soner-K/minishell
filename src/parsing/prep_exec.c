/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:34:03 by sokaraku          #+#    #+#             */
/*   Updated: 2024/10/03 13:33:43 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Sets the names of the infile and outfile.
 * @param files A pointer to the structure containing the file informations.
 * @param token A pointer to the current token.
 * @returns void.
 */
void	set_files_names(t_files *files, t_tokens *token)
{
	if (token->type == HEREDOC)
	{
		files->infile_info->is_heredoc = true;
		files->infile_info->del = token->word;
	}
	if (token->type == INREDIR)
	{
		if (files->infile_info->name)
			free(files->infile_info->name);
		files->infile_info->name = token->word;
		files->infile_info->type = token->type;
	}
	if (token->type == OUTREDIR || token->type == APPENDREDIR)
	{
		files->outfile_info->name = token->word;
		files->outfile_info->type = token->type;
	}
}

/**
 * @brief Sets the rights of the infile and outfile.
 * @param fls A pointer to the structure containing the file informations.
 * @param r The read rights.
 * @param w The write rights.
 * @param ex The execution rights.
 * @returns void.
 */
void	set_files_rights(t_files *fls, __int8_t r, __int8_t w, __int8_t ex)
{
	if (fls->infile_info->name && access(fls->infile_info->name, F_OK) == -1)
		fls->infile_info->rights = NO_FILE_FOUND;
	if (fls->infile_info->name && !access(fls->infile_info->name, R_OK))
		r = READ_ONLY;
	if (fls->infile_info->name && !access(fls->infile_info->name, W_OK))
		w = WRITE_ONLY;
	if (fls->infile_info->name && !access(fls->infile_info->name, X_OK))
		ex = EXECUTE_ONLY;
	if (fls->infile_info->name && fls->infile_info->rights != NO_FILE_FOUND)
		fls->infile_info->rights = r + w + ex;
	r = 0;
	w = 0;
	ex = 0;
	if (fls->outfile_info->name && access(fls->outfile_info->name, F_OK) == -1)
		fls->outfile_info->rights = NO_FILE_FOUND;
	if (fls->outfile_info->name && !access(fls->outfile_info->name, R_OK))
		r = READ_ONLY;
	if (fls->outfile_info->name && !access(fls->outfile_info->name, W_OK))
		w = WRITE_ONLY;
	if (fls->outfile_info->name && !access(fls->outfile_info->name, X_OK))
		ex = EXECUTE_ONLY;
	if (fls->outfile_info && fls->outfile_info->rights != NO_FILE_FOUND)
		fls->outfile_info->rights = r + w + ex;
}

/**
 * @brief Sets the file informations (names and rights).
 * @param files A pointer to the structure containing the file informations.
 * @param token A pointer to the current token.
 * @returns void.
 */
void	set_files_info(t_files *files, t_tokens *token)
{
	set_files_names(files, token);
	set_files_rights(files, 0, 0, 0);
	if (!files->infile_info)
		files->infile_info->rights = NO_FILE_FOUND;
	if (!files->outfile_info)
		files->outfile_info->rights = NO_FILE_FOUND;
}

/**
 * @brief Sets the node of the execution list
 * @param exec A pointer to the structure containing the execution informations.
 * @param token A pointer to the current token.
 * @returns SUCCESS (1) if the node was set, and FAILURE (0) otherwise.
 */
__int8_t	set_node_exec(t_exec *exec, t_tokens *token, int id_cmd)
{
	t_files	*tmp;

	if (!token || !exec)
		return (FAILURE);
	tmp = exec->files_info;
	exec->builtin = (token->type == BUILTIN);
	if (token->type == INREDIR || token->type == HEREDOC)
		tmp->infile_info->name = token->word;
	if (token->type == OUTREDIR || token->type == APPENDREDIR)
		tmp->outfile_info->name = token->word;
	exec->infile = -1;
	exec->outfile = -1;
	while (token && token->id_cmd != id_cmd)
		token = token->next;
	if (token)
		exec->cmd_array = token->cmd_array;
	return (SUCCESS);
}

/**
 * @brief Creates the executions list, with informations like
 * the path of the command, the command array, and the files informations.
 * @param head A pointer to the head of the linked list of tokens.
 * @returns A pointer to the head of the list if the allocation succeeded,
 * and NULL otherwise.
 */
t_exec	*create_exec_lst(t_tokens *head, t_tokens *first, t_env *env_list)
{
	t_exec		*itr;
	t_exec		*exec;
	int			id_cmd;

	id_cmd = 0;
	exec = new_node_exec();
	if (!exec)
		return (NULL);
	itr = exec;
	while (head)
	{
		all_my_homies_hate_the_norm(&head, itr, id_cmd);
		id_cmd++;
		if (itr != exec)
			lst_addback_exec(&exec, itr);
		itr = itr->next;
		if (head)
		{
			itr = new_node_exec();
			if (!itr)
				return (free_exec(exec, true), NULL);
		}
	}
	set_data_struct(first, exec, env_list);
	return (exec);
}
