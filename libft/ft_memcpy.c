/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:18:01 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/10 18:43:24 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (!dest && !src)
		return (NULL);
	i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	source[] = "Hello, world!";
	char	dest1[20];
	char	dest2[20];
	size_t	size;

	size = 7;
	ft_memcpy(dest1, source, size);
	memcpy(dest2, source, size);
	dest1[size] = '\0';
	dest2[size] = '\0';
	printf("My function : '%s'\nOriginal function : '%s'\n", dest1, dest2);
	return (0);
}
*/
