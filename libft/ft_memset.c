/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 00:02:07 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/10 18:39:04 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = (unsigned char)c;
		i++;
	}
	return (s);
}
/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char		area1[] = "123456789", area2[] = "123456789";
	size_t		i;
	int			x = 33, size = 11;

	printf("MY FUNCTION :\nInitial string = '%s'\n", area1);
	ft_memset(area1, x, size);
	printf("After my function (replace '%d' first bytes) : '", size);
	i = 0;
	while (i < sizeof(area1))
	{
		putchar(area1[i]);
		i++;
	}
	printf("'\n\n");
	i = 0;
	printf("ORIGINAL FUNCTION :\nInitial string = '%s'\n", area2);
	memset(area2, x, size);
	printf("After original function (replace '%d' first bytes) : '", size);
	while (i < sizeof(area2))
	{
		putchar(area2[i]);
		i++;
	}
	printf("'\n");
	return (0);
}
*/
