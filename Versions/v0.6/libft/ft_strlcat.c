/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 05:38:26 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/10 21:30:55 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

//size_t  ft_strlen(const char *s);

size_t	ft_strlcat(char *dst, const char *src, size_t siz)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dst);
	j = -1;
	if (siz < i || siz == 0)
		return (siz + ft_strlen(src));
	while (src[++j] && (i + j) < (siz - 1))
		dst[i + j] = src[j];
	dst[i + j] = '\0';
	return (i + ft_strlen(src));
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>
int	main(int argc, char **argv)
{
	size_t		size;
	size_t		l_dst;
	char		init_dst1[ft_strlen(argv[1]) + 1];
	char		init_dst2[ft_strlen(argv[1]) + 1];
	const char	*src;

	if (argc > 4 || argc < 4)
	{
		if (argc > 4)
			printf("Too many arguments.\n");
		if (argc < 4)
			printf("Missing arguments (<dst> <src> <siz>).\n");
		return (1);
	}
	size = (size_t)strtoul(argv[3], NULL, 10);
	l_dst = ft_strlen(argv[1]) + 1;
	src = (const char *)argv[2];
	ft_strlcpy(init_dst1, (const char *)argv[1], l_dst);
	ft_strlcpy(init_dst2, (const char *)argv[1], l_dst);
	printf("MY RESULT :\n'%s' + '%s' (%zu) = ", init_dst1, src, size);
	ft_strlcat(init_dst1, src, size);
	printf("'%s'.\n", init_dst1);
	printf("\nORIGINAL RESULT :\n'%s' + '%s' (%zu) = ", init_dst2, src, size);
	strlcat(init_dst2, src, size);
	printf("'%s'.\n", init_dst2);
	return (0);
}
*/
