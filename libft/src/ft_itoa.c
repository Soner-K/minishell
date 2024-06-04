/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 17:58:52 by sokaraku          #+#    #+#             */
/*   Updated: 2023/12/21 09:34:29 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static void	ft_set(char *sign, short int *i, int *n, long *nb)
{
	*i = 0;
	*nb = *n;
	if (*n < 0)
	{
		(*i)++;
		*nb *= -1;
		*sign = 1;
	}
	else
		*sign = 0;
	if (*n == 0)
		*i = 1;
}

char	*ft_itoa(int n)
{
	char		*str;
	short int	i;
	long		nb;
	char		sign;

	ft_set(&sign, &i, &n, &nb);
	while (n)
	{
		i++;
		n /= 10;
	}
	str = (char *)ft_calloc(i + 1, sizeof(char));
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i--] = nb % 10 + '0';
		nb /= 10;
	}
	if (sign == 1)
		str[0] = '-';
	return (str);
}
