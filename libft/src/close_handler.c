/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 18:56:34 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/16 19:03:47 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	close_handler(int size, ...)
{
	va_list	arg;
	int		fd;

	va_start(arg, size);
	while (size--)
	{
		fd = va_arg(arg, int);
		if (fd >= 0)
			close(fd);
	}
	va_end(arg);
}
