/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 14:58:14 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/22 19:00:13 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*tmp;

	if (!lst || !del)
		return ;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		del((*lst)->content);
		free(*lst);
		*lst = tmp;
	}
	*lst = NULL;
}
/*
#include <stdio.h>

static void	ft_del_elem(void *elem)
{
	if (!(elem))
		return ;
	elem = NULL;
}

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
	t_list	*element1;
	t_list	*element2;
	t_list	*element3;

	element1 = ft_lstnew("!");
	element2 = ft_lstnew("World");
	element3 = ft_lstnew("Hello");
	head = NULL;
	ft_lstadd_front(&head, element1);
	ft_lstadd_front(&head, element2);
	ft_lstadd_front(&head, element3);
	printf("Initial list, before clearing :\n");
	print_list(head);
	element3->next = NULL;
	ft_lstclear(&element2, ft_del_elem);
	printf("\nList after clearing from 'element2' :\n");
	print_list(head);
	return (0);
}
*/
