/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:59:49 by sokaraku          #+#    #+#             */
/*   Updated: 2023/12/21 09:36:03 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*bis;
	char			*str;
	unsigned int	i;

	if (!s || !f)
		return (NULL);
	i = 0;
	str = (char *)ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!str)
		return (NULL);
	bis = (char *)s;
	while (bis[i])
	{
		str[i] = f(i, bis[i]);
		i++;
	}
	str[i] = '\0';
	return (str);
}
