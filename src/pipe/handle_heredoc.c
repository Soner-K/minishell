/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 21:03:52 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/26 16:28:58 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc_count(t_exec *exec)
{
	int		count;
	t_exec	*current;

	count = 0;
	current = exec;
	while (current)
	{
		if (current->files_info->infile_info->type == HEREDOC)
			count++;
		current = current->next;
	}
	printf("total count %d\n", count);
	return (count);
}
void	launch_heredoc(t_exec **exec_list, t_data *data, char **env_copy,
		t_env **env_list)
{
	int	total;
	int	i;

	(void)data;
	(void)exec_list;
	(void)env_copy;
	(void)env_list;
	printf("HERE DOC LAUNCED\n");
	total = heredoc_count(*exec_list);
	i = 0;
	while (i < total && *exec_list != NULL)
	{
		open_heredoc(*exec_list);
		printf("current heredoc infile %d\n", (*exec_list)->infile);
		exec_list = &(*exec_list)->next;
		// (*exec_list)->files_info->infile_info->type = INREDIR;
	}
}
