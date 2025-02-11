/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 03:14:34 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/20 04:07:00 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	if (!lst)
		return (0);
	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
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
	printf("List is size '%d'\n", ft_lstsize(head));
	return (0);
}
*/
