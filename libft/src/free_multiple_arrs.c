/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_multiple_arrs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:55:14 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/16 18:55:55 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	free_multiple_arrs(int n, ...)
{
	va_list	arg;

	va_start(arg, n);
	while (n--)
		free_arrs((void **)va_arg(arg, char **));
	va_end(arg);
}
