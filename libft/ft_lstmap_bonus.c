/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/25 17:06:51 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/25 17:07:55 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_elem = ft_lstnew(f(lst->content));
		if (!new_elem)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_elem);
		lst = lst->next;
	}
	return (new_list);
}
/*
#include <stdio.h>

static void	*ft_addtwo(void *n)
{
	if (!n)
		return (NULL);
	*(int *)n += 2;
	return (n);
}

static void	ft_del_content(void *content)
{
	free(content);
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
	printf("Initial list :\n");
	print_list(head);
	ft_lstmap(head, &ft_addtwo, &ft_del_content);
	printf("\nDuplicated list, after add of 2 from 'element1' :\n");
	print_list(head);
	ft_lstclear(&head, free);
	return (0);
}
*/
