/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 16:20:21 by sokaraku          #+#    #+#             */
/*   Updated: 2024/07/24 19:56:51 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
The tokenized list should be the input for doing the expand.
{words}$VAR{word} will give one token, not multiples, so should be okay

The protection in the beginning of the functions is_inside_singles_quotes
and valid_expand_syntax won't be necessary in the final version
*/

bool	is_inside_single_quotes(char *str)
{
	short int	quotes_count;
	short int	i;

	if (!str)
		return (true);
	quotes_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && quotes_count % 2 == 0)
			return (false);
		if (str[i] == '\'')
			quotes_count++;
		i++;
	}
	return (true);
}

// bool	valid_expand_syntax(char *str)
// {
// 	__int8_t	checks;
// 	short int	i;

// 	if (!str)
// 		return (false);
// 	checks = 0;
// 	i = 1;
// 	if (str[i] && (ft_isalpha(str[i]) || str[i] == '_' || str[i] == '?'))
// 		checks++;
// 	while (str[i])
// }