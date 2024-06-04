/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 16:12:23 by sokaraku          #+#    #+#             */
/*   Updated: 2024/02/07 13:38:38 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

/**
 * @brief Writes a number in STDOUT.
 * @param nb The number to write.
 * @param size A pointer to a value containing the number of octets written
 * in the STDOUT.
 * @returns void.
 */
void	ft_putnbr_long(long nb, int	*size)
{
	if (nb < 0)
	{
		nb *= -1;
		ft_putchar_fd('-', 1);
		(*size)++;
	}
	if (nb / 10)
	{
		(*size)++;
		ft_putnbr_long(nb / 10, size);
	}
	else
		(*size)++;
	ft_putchar_fd((nb % 10) + '0', 1);
}

/**
 * @brief Writes a string in the STDOUT.
 * @param str The string to write.
 * @param size A pointer to a value containing the number of octets written
 * in the STDOUT.
 * @returns void.
 */
void	ft_putstr(char *str, int *size)
{
	if (!str)
	{
		ft_putstr_fd("(null)", 1);
		(*size) += 6;
		return ;
	}
	(*size) += ft_strlen(str);
	while (*str)
		ft_putchar_fd(*str++, 1);
}

/**
 * @brief Writes a number in hexadecimal format in the STDOUT.
 * @param nb The number to write.
 * @param c A character containing X or x, so that the format is adjusted
 * (capital letters or not).
 * @param p A binary equal to 1 if an adress needs to be written, 0 otherwise.
 * @param size A pointer to a value containing the number of octets written
 * in the STDOUT.
 * @returns void.
 */
void	to_hex(unsigned long nb, char c, char p, int *size)
{
	char	*base;

	if (nb == 0 && p == 1)
	{
		(*size) += 5;
		ft_putstr_fd("(nil)", 1);
		return ;
	}
	if (c == 'X')
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (p == 1)
	{
		(*size) += 2;
		ft_putstr_fd("0x", 1);
	}
	if (nb / 16)
	{
		(*size)++;
		to_hex(nb / 16, c, 0, size);
	}
	else
		(*size)++;
	ft_putchar_fd(base[nb % 16], 1);
}
