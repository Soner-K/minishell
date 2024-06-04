/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:13:58 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/29 12:42:39 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	static char	*keep[1024];
	int			bytes_read;

	if (binary == 1)
	{
		free(keep[fd]);
		return (NULL);
	}
	bytes_read = 1;
	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, keep[0], 0))
		return (NULL);
	if (!ft_check(keep[fd], '\n') || !(keep[fd]))
		keep[fd] = file_to_keep(fd, keep[fd], &bytes_read);
	if (!(keep[fd]))
		return (NULL);
	line = keep_to_line(keep[fd]);
	if (!line)
		return (NULL);
	keep[fd] = remove_from_keep(line, keep[fd]);
	if (!(keep[fd]) && !line)
		return (NULL);
	return (line);
}

// #include <fcntl.h>
// #include <stdio.h>
// int	main(void)
// {
// 	int fd;
// 	int fd2;
// 	char *gnl;
// 	char *gnl2;

// 	fd = open("text.txt", O_RDONLY);
// 	fd2 = open("text2.txt", O_RDONLY);
// 	gnl = "";
// 	gnl2 = "";
// 	while (gnl || gnl2)
// 	{
// 		gnl = get_next_line(fd);
// 		gnl2 = get_next_line(fd2);
// 		printf("fd = %d %s", fd, gnl);
// 		printf("fd = %d %s", fd2, gnl2);
// 		free(gnl);
// 		free(gnl2);
// 	}
// 	free(gnl);
// 	free(gnl2);
// }