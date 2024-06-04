/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:16:13 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/29 12:43:21 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*file_to_keep(int fd, char *keep, int *bytes_read)
{
	char	*tmp;

	while (!ft_check(keep, '\n') && (*bytes_read) > 0)
	{
		tmp = malloc(sizeof(char) * BUFFER_SIZE + 1);
		if (!tmp)
			return (NULL);
		*bytes_read = read(fd, tmp, BUFFER_SIZE);
		tmp[*bytes_read] = 0;
		if ((*bytes_read) < 0)
		{
			free(keep);
			free(tmp);
			return (NULL);
		}
		if ((*bytes_read) > 0)
		{
			keep = ft_fuse(keep, tmp);
			if (!keep)
				return (NULL);
		}
		free(tmp);
	}
	return (keep);
}

char	*keep_to_line(char *keep)
{
	char	*line;
	size_t	i;

	i = 0;
	if (ft_check(keep, '\n'))
		line = malloc(sizeof(char) * ft_check(keep, '\n') + 2);
	else
		line = malloc(sizeof(char) * find_len(keep) + 1);
	if (!line)
		return (NULL);
	while (keep[i] != '\n' && keep[i])
	{
		line[i] = keep[i];
		i++;
	}
	if (keep[i] == '\n')
	{
		line[i] = keep[i];
		i++;
	}
	line[i] = 0;
	return (line);
}

char	*remove_from_keep(char *line, char *keep)
{
	size_t	i;
	size_t	j;
	char	*new_keep;
	char	*to_del;

	i = find_len(line);
	j = find_len(keep);
	to_del = keep;
	if (!line || !keep || (j == i))
	{
		free(keep);
		return (NULL);
	}
	new_keep = malloc(sizeof(char) * (j - i) + 1);
	if (!new_keep)
		return (NULL);
	j = 0;
	while (keep[i])
		new_keep[j++] = keep[i++];
	new_keep[j] = 0;
	free(to_del);
	return (new_keep);
}

char	*get_next_line(int fd, char binary)
{
	char		*line;
	static char	*keep;
	int			bytes_read;

	if (binary == 1)
	{
		free(keep);
		return (NULL);
	}
	bytes_read = 1;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, keep, 0))
		return (NULL);
	if (!ft_check(keep, '\n') || !keep)
		keep = file_to_keep(fd, keep, &bytes_read);
	if (!keep)
		return (NULL);
	line = keep_to_line(keep);
	if (!line)
		return (NULL);
	keep = remove_from_keep(line, keep);
	if (!keep && !line)
		return (NULL);
	return (line);
}

// #include <string.h>

// int	main(void)
// {
// 	int fd;
// 	char *gnl;
//	
//	fd = open("text.txt", O_RDONLY);
// 	gnl = "";
// 	while (gnl)
// 	{
// 		gnl = get_next_line(fd);
// 		printf("%s", gnl);
// 		free(gnl);
// 	}
// 	free(gnl);
// }