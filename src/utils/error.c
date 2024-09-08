/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:26:29 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/06 13:03:34 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_error(char *message)
{
	ft_putstr_fd(message, 2);
}

void	free_lists(t_tokens *first)
{
	t_tokens	*tmp;

	while (first)
	{
		tmp = first;
		first = first->next;
		free(tmp->word);
		free (tmp);
	}
}
