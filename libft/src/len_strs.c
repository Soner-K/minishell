/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_strs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 12:39:23 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/29 12:41:33 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	find_len_strs(char **strs)
{
	int	i;

	i = 0;
	if (!(*strs) || !strs)
		return (0);
	while (strs[i])
		i++;
	return (i);
}
