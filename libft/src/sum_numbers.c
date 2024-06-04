/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sum_numbers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 15:38:02 by sokaraku          #+#    #+#             */
/*   Updated: 2024/03/21 15:40:46 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	sum_numbers(int n, ...)
{
	int		sum;
	va_list	arg;

	sum = 0;
	va_start(arg, n);
	while (n--)
		sum += va_arg(arg, int);
	va_end(arg);
	return (sum);
}
