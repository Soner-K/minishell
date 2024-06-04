/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:59:32 by sokaraku          #+#    #+#             */
/*   Updated: 2023/12/21 09:35:43 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strchr(const char *s, int c)
{
	int		i;
	char	*res;

	i = 0;
	if (c == 0)
	{
		res = (char *) &s[ft_strlen(s)];
		return (res);
	}
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
		{
			res = (char *)&s[i];
			return (res);
		}
		i++;
	}
	return (NULL);
}
