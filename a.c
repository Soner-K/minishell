/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   a.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sokaraku <sokaraku@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 12:27:56 by sokaraku          #+#    #+#             */
/*   Updated: 2024/07/24 18:07:41 by sokaraku         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*pas besoin de pointeur sur pointeur ici, car on accede a une adresse
depuis la structure, contrairement a des add front.*/

typedef struct s_list
{
	struct s_list	*next;
	int				val;
}t_list;

t_list	*lstnew(int val)
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	new->val = val;
	new->next = NULL;
	return (new);
}

void	add_back(t_list *head, t_list *new)
{
	while (head->next)
		head = head->next;
	head->next = new;
}

void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%d -> ", lst->val);
		lst = lst->next;
	}
}

void	move_head(t_list **head, int nb)
{
	while (nb--)
		*head = (*head)->next;
}

int main(int ac, char **av, char **env)
{
	char	*cmds[3] = {"ls", "'-l'"};
	// t_list	*lst;
	// t_list	*head;

	// lst = lstnew(0);
	// head = lst;
	// for (int i = 1; i < 5; i++)
	// {
	// 	add_back(head, lstnew(i));
	// }
	// print_list(head);
	// add_back(head, lstnew(5));
	// add_back(head, lstnew(6));
	// add_back(head, lstnew(7));
	// add_back(head, lstnew(8));
	// add_back(head, lstnew(9));
	// add_back(head, lstnew(10));
	// printf("\n");
	// print_list(head);
	// move_head(&head, 7);
	// printf("\n");
	// print_list(head);
	execve("/usr/bin/ls", cmds, env);
}