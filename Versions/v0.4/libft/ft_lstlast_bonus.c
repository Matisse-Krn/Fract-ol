/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 04:07:13 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/20 04:26:33 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
/*
#include <stdio.h>

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
	printf("The last element is '%s'\n", (char *)ft_lstlast(head)->content);
	return (0);
}
*/
