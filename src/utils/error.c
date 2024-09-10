/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 14:26:29 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/10 11:08:37 by sumseo           ###   ########.fr       */
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
		free(tmp);
	}
}

void	exit_program(char *s)
{
	printf("%s\n", s);
	exit(EXIT_FAILURE);
}