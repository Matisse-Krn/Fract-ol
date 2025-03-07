/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:05:33 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/20 03:14:13 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}
/*
#include <stdio.h>

static void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%s -> ", (char *)lst->content);
		lst = lst->next;
	}
	printf("NULL\n");
}

int	main(void)
{
	t_list	*head;
	t_list	*new_elem1;
	t_list	*new_elem2; // Création de quelques éléments de la liste

	head = NULL; // Liste vide au départ
	new_elem1 = ft_lstnew("World");
	new_elem2 = ft_lstnew("Hello");
    // Affichage initial
	printf("Liste initiale : ");
	print_list(head);
    // Ajout de 'new_elem1' en tête de liste
	ft_lstadd_front(&head, new_elem1);
	printf("Après ajout de 'World' : ");
	print_list(head);
    // Ajout de 'new_elem2' en tête de liste
	ft_lstadd_front(&head, new_elem2);
	printf("Après ajout de 'Hello' : ");
	print_list(head);
	return (0);
}
*/
