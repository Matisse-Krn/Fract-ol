/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 23:00:31 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/19 23:04:56 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new_element;

	new_element = ft_calloc(1, sizeof(t_list));
	if (!new_element)
		return (NULL);
	new_element->content = content;
	new_element->next = NULL;
	return (new_element);
}
/*
#include <stdio.h>

int	main(void)
{
	char	*content;
	t_list	*new_node;

	content = "Hello World !";
	new_node = ft_lstnew(content);
	if (new_node)
	{
		printf("Content: %s\n", (char *)new_node->content);
		printf("Next: %p\n", new_node->next);
	}
	else
		printf("Memory allocation failed.\n");
	free(new_node);
	return (0);
}
*/
