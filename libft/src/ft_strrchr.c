/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:59:56 by sokaraku          #+#    #+#             */
/*   Updated: 2023/12/21 09:36:13 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*ptr;
	int		i;

	i = ft_strlen(s) - 1;
	while (i >= 0)
	{
		if (s[i] == (unsigned char) c)
		{
			ptr = (char *)&s[i];
			return (ptr);
		}
		i--;
	}
	if (c == 0)
	{
		i = ft_strlen(s);
		ptr = (char *)&s[i];
		return (ptr);
	}
	return (NULL);
}
