/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 16:14:01 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/29 12:43:26 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 20
# endif

# include <stdlib.h>
# include <unistd.h>

size_t	find_len(char const *s);
int		ft_check(char const *s, char c);
char	*ft_fuse(char *s1, char *s2);

char	*file_to_keep(int fd, char *keep, int *bytes_read);
char	*keep_to_line(char *keep);
char	*remove_from_keep(char *line, char *keep);
char	*get_next_line(int fd, char binary);
#endif