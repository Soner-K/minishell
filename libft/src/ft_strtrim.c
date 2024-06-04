/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:59:58 by sokaraku          #+#    #+#             */
/*   Updated: 2023/12/21 09:36:15 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	ft_initialize(char *str, long *i, long *last, long *begin)
{
	*i = 0;
	*begin = 0;
	*last = ft_strlen(str) - 1;
}

static int	ft_inset(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (c == set[i])
			return (1);
		i++;
	}
	return (0);
}

static int	ft_nowhere(char const *s1, char const *set)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1[0] == 0)
		return (0);
	while (s1[i])
	{
		while (set[j])
		{
			if (s1[i] == set[j])
				return (1);
			j++;
		}
		i++;
		j = 0;
	}
	if (s1[1])
		return (1);
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	long	last;
	long	i;
	long	begin;
	char	*new;

	if (!s1)
		return (NULL);
	ft_initialize((char *) s1, &i, &last, &begin);
	while (ft_inset(s1[begin], set) == 1)
		begin++;
	while (ft_inset(s1[last], set) == 1 && last)
		last--;
	if (last == 0 || ft_nowhere(s1, set) == 0)
	{
		new = malloc(sizeof(char));
		*new = '\0';
		return (new);
	}
	new = (char *)ft_calloc((last - begin + 2), sizeof(char));
	if (!new)
		return (NULL);
	while (begin <= last)
		new[i++] = s1[begin++];
	new[i] = '\0';
	return (new);
}
