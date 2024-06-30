/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 14:25:38 by sokaraku          #+#    #+#             */
/*   Updated: 2024/06/30 22:12:08 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * @brief Create a new node tailored for a list of tokens.
 * @param word The word that will be stored in the created node.
 * @param is_head A boolean being true (1) if the created node will be the
 * head of a list, and false (0) otherwise.
 * @returns The created node.
 */
t_tokens	*new_node_token(char *word, bool is_head)
{
	t_tokens			*new;
	static t_tokens	*head = NULL;

	new = malloc(sizeof(t_tokens));
	if (!new)
		return (NULL);
	new->word = word;
	new->path = NULL;
	new->next = NULL;
	new->prev = NULL;
	new->type = NONE;
	if (is_head)
		head = new;
	new->head = head;
	return (new);
}

bool	is_valid_separator(char *sep)
{
	short int	sep_len;

	sep_len = ft_strlen(sep);
	if (!ft_strncmp(">>", sep, sep_len))
		return (true);
	if (!ft_strncmp("<<", sep, sep_len))
		return (true);
	if (!ft_strncmp(">", sep, sep_len))
		return (true);
	if (!ft_strncmp("<", sep, sep_len))
		return (true);
	if (!ft_strncmp("|", sep, sep_len))
		return (true);
	return (false);
}

/**
 * @brief A simple strjoin, but it also puts a space between the two strings,
 to facilitate the split afterwards.
 * @param s1 A pointer to the first string to copy.
 * @param s2 a pointer to the second string to copy.
 * @returns The merged strings, with a space in the middle.
 * Returns NULL if the allocation failed or if the two strings are NULL.
 */
char	*merge_strings(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*new;

	i = 0;
	j = 0;
	if (!s1 && !s2)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2)) + 2);
	if (!new)
		return (NULL);
	while (s1 && s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	if (s1)
		new[i++] = ' ';
	while (s2 && s2[j])
		new[i++] = s2[j++];
	new[i] = 0;
	free(s1);
	return (new);
}
