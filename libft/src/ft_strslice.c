/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strslice.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 18:22:33 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/08 18:49:47 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/**
 * @brief Removes a part of a string, starting from index start, and
 * ending at index end.
 * @param str A pointer to a string.
 * @param start Beginning index of the portion to remove.
 * @param end End index of the portion to remove.
 * @returns The modified string, or NULL in case of an error.
 * (start and or end > to len of str, allocation failure...).
 */
char	*ft_strslice(char *str, int start, int end)
{
	char	*new;
	int		size;
	int		i;
	int		j;

	if (!str || start > ft_strlen(str) || end > ft_strlen(str) || end < 0
		|| start < 0)
		return (NULL);
	size = ft_strlen(str) - (end - start) + 1;
	new = ft_calloc(size, sizeof(char));
	if (!new)
		return (new);
	i = 0;
	j = 0;
	while (str[i] && i < start)
		new[j++] = str[i++];
	i = end + 1;
	while (str[i])
		new[j++] = str[i++];
	new[j] = '\0';
	return (new);
}

int	main(int ac, char **av)
{
	(void)ac;
	char *new;

	new = ft_strslice(av[1], atoi(av[2]), atoi(av[3]));
	printf("new is : %s\n", new);
	free(new);
}