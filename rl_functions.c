/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_functions.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 14:17:29 by sokaraku          #+#    #+#             */
/*   Updated: 2024/05/31 18:24:59 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

char *readline(const char *prompt);
/*
Comme un gnl ; lis une ligne depuis le terminal et la retourne, sans le \n final
La ligne renvoye est malloc. prompt sert a afficher quelque chose en attente de 
l'input par l'utilisateur.
*/

void add_history (const char *string);
/*
Ajoute une chaine de caractere a un historique. A utiliser avec readline
pour creer un historique des commandes. Fleche haut permet de remonter l'historique
(pas besoin de gerer de signaux).
*/

void rl_clear_history (void);
/*
Supprime tout l'historique.
*/

int rl_on_new_line(void);
/*
Informe que le display doit etre sur une nouvelle ligne (par exemple apres un ctrl C).
*/

void rl_redisplay (void);
/*
Ecrit a nouveau le prompt de readline
*/

void rl_replace_line (const char *text, int clear_undo);
/*
jsp
*/

void	sigint_handler(int sig)
{
	rl_on_new_line(); //on indique qu'on passe sur une nouvelle ligne
	printf("\n");
	rl_redisplay(); // on reecrit le prompt de readline
}

void	sigtstop_handler(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	printf("\n");
	rl_redisplay();
}

int	main(void)
{
	int 	i = 0;
	char	*str;
	signal(SIGINT, sigint_handler);
	signal(SIGTSTP, sigtstop_handler);

	while (i < 5)
	{
		str = readline(">>>> "); //fleche haut pour retrouver l'historique
		if (str)
			add_history(str);
		i++;
		free(str);
		//utilise ctrl C
	}
	rl_clear_history();
	printf("history cleared (rl_clear_history)\n");
	i = 0;
	while (i++ != 1)
		str = readline(">>>> ");
}

