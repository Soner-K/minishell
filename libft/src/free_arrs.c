/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_arrs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 11:19:01 by sokaraku          #+#    #+#             */
/*   Updated: 2024/03/21 13:58:08 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"
//careful with arrays that arent strings
void	free_arrs(void **arrs)
{
	int	i;

	i = 0;
	if (!arrs)
		return ;
	while (arrs[i])
	{
		free(arrs[i]);
		i++;
	}
	free(arrs);
}
