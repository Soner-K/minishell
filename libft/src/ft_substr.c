/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 18:00:00 by sokaraku          #+#    #+#             */
/*   Updated: 2023/12/21 09:36:17 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static	size_t	ft_pars(char const *s, unsigned int *start, size_t *len)
{
	size_t	len_s;

	len_s = ft_strlen(s);
	if ((*start) > len_s)
	{
		*len = 0;
		return (1);
	}
	if ((*len) >= len_s)
	{
		if (*start < *len && (*len - *start) < len_s)
			*len -= *start;
		else
			*len = len_s;
	}
	return (0);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	i;

	if (!s)
		return (NULL);
	if (ft_pars(s, &start, &len))
	{
		new = ft_calloc(1, sizeof(char));
		new[0] = '\0';
	}
	else
		new = ft_calloc(len + 1, sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (len-- && s[start])
		new[i++] = s[start++];
	new[i] = '\0';
	return (new);
}
