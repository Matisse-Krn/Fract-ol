/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 20:07:21 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/10 18:28:01 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	size_t	i;
	char	*ptr;

	i = 0;
	ptr = (char *)s;
	while (i < n)
		ptr[i++] = 0;
	return ;
}
/*
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int	main(void)
{
	char	area1[] = "123456789";
	char	area2[] = "123456789";
	int		i;
	int		size;

	size = 5;
	i = 0;
	printf("MY FUNCTION :\n");
	printf("initial string = '%s'\n", area1);
	ft_bzero(area1, size);
	while (area1[i] == '\0')
		i++;
	printf("After my function (erase '%d' first bytes) : \
'%s'\n", size, area1 + i);
	printf("\n\n");
	i = 0;
	printf("ORIGINAL FUNCTION :\n");
	printf("initial string = '%s'\n", area2);
	bzero(area2, size);
	while (area2[i] == '\0')
		i++;
	printf("After original function (erase '%d' first bytes) : \
'%s'\n", size, area2 + i);
	return (0);
}
*/
