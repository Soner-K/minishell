/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_odd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/07 14:04:40 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/07 14:08:34 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

bool	is_odd(int n)
{
	if (n == 0)
		return (false);
	return (n % 2);
}
