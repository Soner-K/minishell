/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:34:03 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/12 20:26:11 by sokaraku         ###   ########.fr       */
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
	if (token->type == INREDIR || token->type == HEREDOC)
		files->infile = token->word;
	if (token->type == HEREDOC)
		files->is_heredoc = true;
	if (token->type == OUTREDIR || token->type == APPENDREDIR)
		files->outfile = token->word;
}

/**
 * @brief Sets the rights of the infile and outfile.
 * @param files A pointer to the structure containing the file informations.
 * @param r The read rights.
 * @param w The write rights.
 * @param ex The execute rights.
 * @returns void.
 */
void	set_files_rights(t_files *files, __int8_t r, __int8_t w, __int8_t ex)
{
	if (files->infile && access(files->infile, F_OK) == -1)
		files->rights_infile = NO_FILE_FOUND;
	if (files->infile && !access(files->infile, R_OK))
		r = READ_ONLY;
	if (files->infile && !access(files->infile, W_OK))
		w = WRITE_ONLY;
	if (files->infile && !access(files->infile, X_OK))
		ex = EXECUTE_ONLY;
	if (files->infile && files->rights_infile != NO_FILE_FOUND)
		files->rights_infile = r + w + ex;
	r = 0;
	w = 0;
	ex = 0;
	if (files->outfile && access(files->outfile, F_OK) == -1)
		files->rights_outfile = NO_FILE_FOUND;
	if (files->outfile && !access(files->outfile, R_OK))
		r = READ_ONLY;
	if (files->outfile && !access(files->outfile, W_OK))
		w = WRITE_ONLY;
	if (files->outfile && !access(files->outfile, X_OK))
		ex = EXECUTE_ONLY;
	if (files->outfile && files->rights_outfile != NO_FILE_FOUND)
		files->rights_outfile = r + w + ex;
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
	if (!files->infile)
		files->rights_infile = NO_FILE_FOUND;
	if (!files->outfile)
		files->rights_outfile = NO_FILE_FOUND;
	//necessary? COME BACK
}

/**
 * @brief Sets the node of the execution list
 * @param exec A pointer to the structure containing the execution informations.
 * @param token A pointer to the current token.
 * @returns SUCCESS (1) if the node was set, and FAILURE (0) otherwise.
 */
__int8_t	set_node_exec(t_exec *exec, t_tokens *token)
{
	t_files	*tmp;
	int		id_cmd;

	id_cmd = token->id_cmd;
	if (!token || !exec)
		return (FAILURE);
	tmp = exec->files_info;
	exec->builtin = (token->type == BUILTIN);
	exec->path = token->path;
	if (token->type == INREDIR || token->type == HEREDOC)
		tmp->infile = token->word;
	if (token->type == OUTREDIR || token->type == APPENDREDIR)
		tmp->outfile = token->word;
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
t_exec	*create_exec_lst(t_tokens *head)
{
	t_exec	*itr;
	
	t_exec	*exec;
	int		id_cmd;

	id_cmd = 0;
	exec = new_node_exec();
	if (!exec)
		return (free_tokens(head), NULL); // COME BACK
	itr = exec;
	while (head)
	{
		while (head && head->id_cmd == -1)
			head = head->next;
		while (head && head->id_cmd == id_cmd)
		{
			if (head->type >= INREDIR && head->type <= APPENDREDIR)
				set_files_info(itr->files_info, head);
			if (head->type == CMD || head->type == BUILTIN)
				set_node_exec(itr, head);
			head = head->next;
		}
		id_cmd++;
		if (itr != exec)
			lst_addback_exec(&exec, itr);
		itr = itr->next;
		if (head)
		{
			itr = new_node_exec();
			if (!itr)
				return (free_tokens(head), NULL); // COME BACK
		}
	}
	return (exec);
}
