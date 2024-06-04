/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:59:10 by sokaraku          #+#    #+#             */
/*   Updated: 2023/12/21 09:35:24 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*dest_2;
	unsigned char	*src_2;

	if (!dest && !src)
		return (NULL);
	i = 0;
	dest_2 = (unsigned char *)dest;
	src_2 = (unsigned char *)src;
	while (n)
	{
		if (dest_2 <= src_2)
			dest_2[i] = src_2[i];
		else
			dest_2[n - 1] = src_2[n - 1];
		i++;
		n--;
	}
	return (dest);
}
