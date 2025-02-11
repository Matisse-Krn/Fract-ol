/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 16:20:43 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/25 17:06:35 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
	}
	return ;
}
/*
#include <stdio.h>

static void	ft_addtwo(void *n)
{
	if (!n)
		return ;
	*(int *)n += 2;
}

static void	print_list(t_list *lst)
{
	while (lst)
	{
		printf("%d -> ", *(int *)(lst->content));
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
	int		*val1;
	int		*val2;
	int		*val3;

	val1 = malloc(sizeof(int));
	val2 = malloc(sizeof(int));
	val3 = malloc(sizeof(int));
	*val1 = 1;
	*val2 = 2;
	*val3 = 3;
	element1 = ft_lstnew(val1);
	element2 = ft_lstnew(val2);
	element3 = ft_lstnew(val3);
	head = NULL;
	ft_lstadd_front(&head, element3);
	ft_lstadd_front(&head, element2);
	ft_lstadd_front(&head, element1);
	printf("Initial list, before applying +2 :\n");
	print_list(head);
	ft_lstiter(head, ft_addtwo);
	printf("\nList after add of 2 from 'element1' :\n");
	print_list(head);
	ft_lstclear(&head, free);
	return (0);
}
*/
