/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_and_quit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:40:03 by sokaraku          #+#    #+#             */
/*   Updated: 2024/03/20 11:42:25 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

/**
 * @brief Prints a message to STD_ERROR, frees an array of string
 * and then exit the program.
 * @param msg The message to print.
 * @param strs An array of strings.
 * @returns void.
 */
void	free_and_quit(char *msg, char **strs)
{
	free_arrs((void **)strs);
	ft_putendl_fd("Error", 2);
	ft_putendl_fd(msg, 2);
	exit(EXIT_FAILURE);
}
