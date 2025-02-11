/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:52:29 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/20 16:36:50 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*tmp;

	if (!lst || !new)
		return ;
	if (!*lst)
	{
		*lst = new;
		return ;
	}
	tmp = *lst;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
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
	t_list	*new_elem2;
	t_list	*new_back; // Création de quelques éléments de la liste

	new_elem1 = ft_lstnew("World");
	new_elem2 = ft_lstnew("Hello");
	new_back = ft_lstnew("42");
	head = NULL;
	ft_lstadd_front(&head, new_elem1);
	ft_lstadd_front(&head, new_elem2);
	printf("Initial list : ");
	print_list(head);
	ft_lstadd_back(&head, new_back);
	printf("List after adding '42' to the back : ");
	print_list(head);
	return (0);
}
*/
