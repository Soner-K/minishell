/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_strs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:02:19 by sokaraku          #+#    #+#             */
/*   Updated: 2024/09/30 13:30:20 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	print_strs(char **strs)
{
	int	i;

	i = -1;
	if (!strs || !(*strs))
		return ;
	while (strs[++i])
		ft_putendl_fd(strs[i], STDOUT_FILENO);
}
