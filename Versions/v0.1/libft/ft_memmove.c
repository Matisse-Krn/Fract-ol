/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:42:15 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/10 18:23:10 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest == src || n == 0)
		return (dest);
	if (dest > src)
	{
		i = n;
		while (i > 0)
		{
			i--;
			((char *)dest)[i] = ((char *)src)[i];
		}
	}
	else
	{
		i = 0;
		while (i < n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	buffer1[] = "Hello world !";
	char	buffer2[] = "Hello world !";
	size_t	size;

	size = 5;
	ft_memmove(buffer1, buffer1 + 6, size);
	memmove(buffer2, buffer2 + 6, size);
	printf("My function :		'%s'\n", buffer1);
	printf("Original function :	'%s'\n", buffer2);
	return (0);
}
*/
