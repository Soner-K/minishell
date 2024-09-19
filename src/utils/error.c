/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:26:29 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/19 12:47:42 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


void	free_lists(t_tokens *first)
{
	t_tokens	*tmp;

	while (first)
	{
		tmp = first;
		first = first->next;
		free(tmp->word);
		free(tmp);
	}
}


void	free_env_list(t_env *env_list)
{
	t_env *temp;

	while (env_list)
	{
		temp = env_list;
		env_list = env_list->next;
		free(temp->variable);
		free(temp);
	}
}