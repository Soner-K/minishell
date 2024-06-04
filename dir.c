/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dir.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 13:41:00 by sokaraku          #+#    #+#             */
/*   Updated: 2024/05/31 14:24:08 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>

typedef unsigned long ino_t;
typedef long off_t;

struct dirent {
    ino_t          d_ino;       // Numero qui identifie un fichier ou un directory
    off_t          d_off;       // "Distance" (octets) jusqu'au prochain fichier ou directory.
    unsigned short d_reclen;    // Taille de la structure.
    unsigned char  d_type;      // Type de fichier (directory, fichier etc)
    char           d_name[256]; // Nom
};


DIR				*opendir(const char *name);
/*
Ouvre un directory (et uniquement un directory) situe a name, et retourne un pointeur de type DIR *. 
Name peut etre un chemin absolu ou relatif.
On manipule pas DIR * directement, c'est les deux autres fonctions qui s'en occupent.
Renvoie le pointeur si le directory est ouvert, NULL sinon.
*/
struct dirent	*readdir(DIR *dirp);
/*
Lis la prochaine entree du directory qu'on a ouvert et renvoie une structure dirent qui contient ses infos.
*/

int	closedir	(DIR *dirp);
/*
Ferme le repo ouvert (libere sa memoire).
*/

int	main(void)
{
	DIR *dir;
	struct dirent *entry;

	dir = opendir("libft");
	entry = readdir(dir);
	printf("Name : %s type %d\n", entry->d_name, entry->d_type);
	entry = readdir(dir);
	printf("Name : %s type %d\n", entry->d_name, entry->d_type);
	entry = readdir(dir);
	printf("Name : %s type %d\n", entry->d_name, entry->d_type);
	entry = readdir(dir);
	printf("Name : %s type %d\n", entry->d_name, entry->d_type);
	entry = readdir(dir);
	printf("Name : %s type %d\n", entry->d_name, entry->d_type);
	closedir(dir);
}