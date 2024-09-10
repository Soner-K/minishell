/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sumseo <sumseo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/24 17:15:01 by sumseo            #+#    #+#             */
/*   Updated: 2024/09/09 12:22:08 by sumseo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	write_heredoc(char *str, int tmp)
{
	ft_putstr_fd(str, tmp);
	ft_putstr_fd("\n", tmp);
}

void	init_heredoc(t_parse *cmds_list)
{
	cmds_list->delimiter = cmds_list->infile_name;
	cmds_list->is_heredoc = 1;
}

void	open_heredoc(t_parse *cmds_list)
{
	char	*str;
	int		tmp;

	tmp = open("tmp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		str = readline(">");
		if (str == NULL)
		{
			printf("heredoc delimited by EOF(`%s')\n", cmds_list->delimiter);
			break ;
		}
		if (ft_strncmp(str, cmds_list->delimiter,
				ft_strlen(cmds_list->delimiter)) == 0
			&& str[ft_strlen(cmds_list->delimiter)] == '\0')
		{
			free(str);
			break ;
		}
		write_heredoc(str, tmp);
		free(str);
	}
	close(tmp);
	open("tmp", O_RDONLY, 0644);
	cmds_list->infile = tmp;
}

void	call_heredoc(t_parse *cmds_list)
{
	init_heredoc(cmds_list);
	open_heredoc(cmds_list);
}
