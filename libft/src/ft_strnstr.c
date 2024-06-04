/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:59:54 by sokaraku          #+#    #+#             */
/*   Updated: 2023/12/21 09:36:11 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*str;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!big && len <= 0)
		return (NULL);
	if ((!big[0] && !little[0]) || ((!little[0]) && big[0]))
		return ((char *)big);
	while (big[i] && i < len)
	{
		while (big[i + j] == little[j])
		{
			if (little[j + 1] == '\0' && i + j < len)
			{
				str = (char *)&big[i];
				return (str);
			}
			j++;
		}
		i++;
		j = 0;
	}
	return (NULL);
}
