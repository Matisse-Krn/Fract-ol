/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 20:36:15 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/20 21:55:07 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
}
/*
#include <stdio.h>

static void	ft_del_elem(void *elem)
{
	if (!(elem))
		return ;
	elem = NULL;
}

int	main(void)
{
	t_list	*elem;

	elem = ft_lstnew(malloc(10));
	if (!elem)
		return (1);
	printf("Content address before deletion: %p\n", elem->content);
	ft_lstdelone(elem, ft_del_elem);
	printf("Content address after deletion: %p\n", elem->content);
	printf("Element deleted successfully\n");
	return (0);
}
*/
