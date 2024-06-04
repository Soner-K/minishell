/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 15:57:19 by sokaraku          #+#    #+#             */
/*   Updated: 2024/05/31 12:59:13 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h> //access
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h> // struct stat
#include <fcntl.h> //open et close

#define FALSE 0
#define TRUE 1
#define PATH "/home/sokaraku/projects/42/minishell" //met un path ici
#define PATH2 "/home/sokaraku/projects/42" //un autre path

int access(const char *pathname, int mode);
/*
Verifie si un fichier est accessible, selon les criteres specifiees dans mode.
Des macros sont dispo pour les utiliser comme mode.
pathname = chemin (absolu ou relatif) vers le fichier.
F_OK : Le fichier existe
W_OK : On a les droits d'ecrire dans le fichier
X_OK : On a les droits d'executer le fichier
R_OK : On a les droits pour lire le fichier
On peut combiner les flags de la facon suivante : F_OK | X_OK
En cas de succes, access renvoie 0, et -1 sinon.
*/

char	*getcwd(char *buf, size_t size);
/*
Renvoie le chemin du repertoire actuel (cwd) sous forme d'une chaine malloc. Le stock aussi dans buf, qui est de taille size.
Si size est trop petit pour accueillir cwd, alors rien n'est fait.
Si buf est trop petit pour accueilir cwd, mais que la valeur de size est suffisante : segfault.
si buf a une taille de 50 octets, que s est un pointeur null et que cwd fait 50 octets :
s = getcwd(NULL, 0) est pareil que getcwd(buf, 50);
Note : Tjr stocker le resultat de getcwd quelque part, vu que la chaine renvoyee est malloc.
*/

int chdir(const char *path);
/*
Change le cwd pour le remplacer par celui qui se trouve dans path.
Renvoie 0 si ca marche, -1 sinon.
Fonctionne avec "../".
Si on est dans home/user/repo/projet alors :
chdir("/home/user/repo") est pareil que chdir("../")
*/


												/* main pour access, getcwd, chdir*/

// int main(void)
// {
// 	__int8_t	exist = FALSE;
// 	char		*s;
// 	char		s2[500];

// 	printf("Absolute path : ");
// 	exist = access(PATH, F_OK);
// 	if (exist == 0)
// 		printf("File exists\n");
// 	else
// 		printf("File doesn't exist\n");
// 	printf("Relative path : ");
// 	exist = access("Makefile", F_OK);
// 	if (exist == 0)
// 		printf("File exists\n");
// 	else
// 		printf("File doesn't exist\n");
// 	s = getcwd(NULL, 0);
// 	printf("s = getcwd and now s is %s\n", s);
// 	getcwd(s2, 500);
// 	printf("just using getcwd %s\n", s2);
// 	free(s);
// 	chdir("PATH2");
// 	s = getcwd(NULL, 0);
// 	printf("Path is %s\n", s);
// 	free(s);
// }


void print_stat(struct stat file_info) {
    printf("File mode: %o\n", file_info.st_mode);
    printf("Inode number: %lu\n", file_info.st_ino);
    printf("ID of device containing the file: %lu\n", file_info.st_dev);
    printf("ID of device (if special file): %lu\n", file_info.st_rdev);
    printf("Number of hard links: %lu\n", file_info.st_nlink);
    printf("User ID of file: %u\n", file_info.st_uid);
    printf("Group ID of file: %u\n", file_info.st_gid);
    printf("File size in bytes: %ld\n", file_info.st_size);
    printf("Time of last access: %ld\n", file_info.st_atime);
    printf("Time of last modification: %ld\n", file_info.st_mtime);
    printf("Time of last status change: %ld\n", file_info.st_ctime);
    printf("Optimal block size for I/O: %ld\n", file_info.st_blksize);
    printf("Number of 512B blocks allocated: %ld\n", file_info.st_blocks);
}

int stat(const char *path, struct stat *buf);
/*
Remplis une structure buf d'informations sur un fichier.
path : chemin vers le fichier pour lequel on veut des infos.
buf : structure de type stat, qui contient des variables d'infos.
*/

int fstat(int fd, struct stat *buf);
/*
Remplis une structure buf d'informations sur un fichier.
fd : le fd du fichier pour lequel on veut les infos.
buf : structure de type stat, qui contient des variables d'infos.
*/

int main(void)
{
	struct stat file_info;
	int			fd;

	stat("Makefile", &file_info);
	print_stat(file_info);
	fd = open("Makefile", O_RDONLY);
	printf("fstat\n\n\n");
	fstat(fd, &file_info);
	print_stat(file_info);
	close(fd);
}