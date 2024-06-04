/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tty.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 16:17:17 by sokaraku          #+#    #+#             */
/*   Updated: 2024/05/31 17:04:49 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

char	*getenv(const char *name);
/*
Renvoie l'adresse, dans l'environnement, de la variable name (pas de malloc).
Renvoie NULL si elle n'existe pas.
*/

int		isatty(int fd);
/*
Renvoie 1 si le fd est un terminal (STDOUT par ex) et 0 sinon.
*/

char	*ttyname(int fd);
/*
Renvoie le path du fd associe a un terminal.
Si le fd n'est pas associe a un terminal, renvoie NULL.
Si le path n'existe pas, renvoie NULL.
*/

int		ttyslot(void);
/*
sah jsp a quoi ca sert
*/

int main(void)
{
	char	*str = getenv("USER");
	printf("user is %s\n", str);
	printf("isatty(STDOUT_FILENO) = %d\n", isatty(STDOUT_FILENO));
	printf("isatty(3) = %d\n", isatty(3));
	printf("%s", ttyname(STDOUT_FILENO));
}