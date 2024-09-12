/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 15:34:03 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/12 13:07:35 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static void	add_back(t_exec **head, t_exec *add)
// {
// 	t_exec	*tmp;

// 	if (!(*head))
// 	{
// 		*head = add;
// 		return ;
// 	}
// 	tmp = *head;
// 	while ((tmp->next))
// 		tmp = tmp->next;
// 	tmp->next = add;
// }

t_exec	*new_node_exec(void)
{
	t_files	*files_info;
	t_exec	*exec_node;

	exec_node = malloc(sizeof(t_exec));
	files_info = malloc(sizeof(t_files));
	if (!exec_node || !files_info)
		return (NULL);
	exec_node->builtin = false;
	exec_node->path = NULL;
	exec_node->cmd_array = NULL;
	exec_node->next = NULL;
	exec_node->files_info = files_info;
	files_info->is_heredoc = false;
	files_info->infile = NULL;
	files_info->outfile = NULL;
	files_info->rights_infile = -1;
	files_info->rights_outfile = -1;
	return (exec_node);
}

void	set_files_names(t_files *files, t_tokens *token)
{
	if (token->type == INREDIR || token->type == HEREDOC)
		files->infile = token->word;
	if (token->type == HEREDOC)
		files->is_heredoc = true;
	if (token->type == OUTREDIR || token->type == APPENDREDIR)
		files->outfile = token->word;
}

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
	files->rights_outfile = r + w + ex;
}

__int8_t	set_node_exec(t_exec *exec, t_tokens *token)
{
	t_files	*tmp;

	if (!token || !exec)
		return (FAILURE);
	tmp = exec->files_info;
	exec->builtin = (token->type == BUILTIN);
	exec->path = token->path;
	exec->cmd_array = token->cmd_array;
	tmp->is_heredoc = (token->type == HEREDOC);
	if (token->type == INREDIR || token->type == HEREDOC)
		tmp->infile = token->word;
	if (token->type == OUTREDIR || token->type == APPENDREDIR)
		tmp->outfile = token->word;
	// set_files_info(exec->files_info, 0, 0, 0);
	return (SUCCESS);
}

t_exec	*create_exec_lst(t_tokens *head)
{
	t_exec *lst;
	int id_cmd;

	id_cmd = 0;
	lst = NULL;
	while (head)
	{
		lst = new_node_exec();
		if (!lst)
			return (free_tokens(head), NULL); // COME BACK
		while (head && head->id_cmd == id_cmd)
		{
			if (head->type == CMD || head->type == BUILTIN)
			{
				printf("workiing in progress");
			}
		}
	}
	return (NULL);
}