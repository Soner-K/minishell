/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:59:42 by sokaraku          #+#    #+#             */
/*   Updated: 2023/12/21 09:35:55 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	i;
	size_t	j;

	if ((!dest || !src) && (size == 0))
		return ((size_t) NULL);
	j = ft_strlen((const char *)dest);
	if (j > size)
		return (size + ft_strlen(src));
	if (!src)
		return (j);
	if (!size)
		return (ft_strlen(src) + j);
	i = 0;
	while (src[i] && (i + j) < size - 1)
	{
		dest[i + j] = src[i];
		i++;
	}
	dest[i + j] = '\0';
	return (j + ft_strlen(src));
}
