/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:59:01 by sokaraku          #+#    #+#             */
/*   Updated: 2023/12/21 09:35:17 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_2;
	size_t			i;

	i = 0;
	s_2 = (unsigned char *)s;
	while (i < n)
	{
		if (s_2[i] == (unsigned char) c)
			return (&(s_2[i]));
		i++;
	}
	return (NULL);
}
