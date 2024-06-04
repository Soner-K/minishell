/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:59:20 by sokaraku          #+#    #+#             */
/*   Updated: 2023/12/21 10:37:33 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../../includes/libft.h"
# include <stdarg.h>

void	to_hex(unsigned long nb, char c, char p, int *size);
void	ft_putstr(char *str, int *size);
void	ft_putnbr_long(long nb, int	*size);

int		ft_printf(const char *str, ...);

#endif
