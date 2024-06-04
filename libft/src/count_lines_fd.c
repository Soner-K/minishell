/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_lines_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/29 15:31:07 by sokaraku          #+#    #+#             */
/*   Updated: 2024/03/01 12:56:25 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	count_lines_fd(char *path)
{
	int		i;
	int		tmp_fd;
	char	*tmp;

	i = 0;
	tmp_fd = open(path, O_RDONLY);
	if (tmp_fd == -1)
		return (-1);
	tmp = get_next_line(tmp_fd, 0);
	while (tmp)
	{
		i++;
		if (!tmp)
			break ;
		else
			free(tmp);
		tmp = get_next_line(tmp_fd, 0);
	}
	get_next_line(tmp_fd, 1);
	close(tmp_fd);
	return (i);
}
