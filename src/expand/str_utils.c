/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 17:13:50 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/22 18:16:56 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Removes a part of a string, starting from index start, and
 * ending at index end.
 * @param str A pointer to a string.
 * @param start Beginning index of the portion to remove.
 * @param end End index of the portion to remove.
 * @param alloc_fail Pointer to a boolean taking the value 1 (true)
 * if an allocation failure occured, and 0 (false) otherwise.
 * @returns The modified string, or NULL in case of an error.
 */
char	*ft_strslice(char *str, int start, int end, bool *alloc_fail)
{
	char	*new;
	int		size;
	int		i;
	int		j;

	if (!str || start > ft_strlen(str) || end > ft_strlen(str) || end < 0
		|| start < 0)
		return (NULL);
	size = ft_strlen(str) - (end - start) + 1;
	new = malloc(size * sizeof(char));
	if (!new)
		return (*alloc_fail = true, NULL);
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

/**
 * @brief Merges two strings, replacing a part of the previous string "str",
 * with a new string "add", starting from index "start" and ending at
 * index "end".
 * @param str The original string.
 * @param add The string to add in str.
 * @param start The beginning index at which to merge the new string.
 * @param end The end index at which the merge of the new string ends.
 * @returns The new string with
 */
char	*ft_strreplace(char *str, char *add, int start, int end)
{
	char	*new;
	int		i;
	int		j;
	int		size;

	i = -1;
	j = 0;
	size = ft_strlen(str) + ft_strlen(add) + count_char(str, -34)
		+ count_char(str, -39) - (end - start - 2) + 1;
	new = malloc(size * sizeof(char));
	if (!new)
		return (NULL);
	while (str[++i] && i < start)
		new[j++] = str[i];
	i = -1;
	while (add && add[++i])
		new[j++] = -add[i];
	i = end;
	while (str[++i])
		new[j++] = str[i];
	new[j] = '\0';
	return (new);
}
