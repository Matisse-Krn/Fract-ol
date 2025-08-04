/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/09 02:33:16 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/10 20:45:07 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t siz)
{
	size_t	i;

	if (siz == 0)
		return (ft_strlen(src));
	i = -1;
	while (++i < siz - 1 && src[i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (ft_strlen(src));
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <bsd/string.h>
//	Compile with '-lbsd' option
int	main(int argc, char **argv)
{
	char	*dest1;
	char	*dest2;
	size_t	size = strtoul(argv[2], NULL, 10);

	if (argc < 3 || argc > 3)
	{
		if (argc < 3)
			printf("Missing arguments.\n");
		if (argc > 3)
			printf("Too many arguments.\n");
		return (1);
	}
	size = strtoul(argv[2], NULL, 10);
	dest1 = ft_calloc(size, sizeof(size_t));
	dest2 = ft_calloc(size, sizeof(size_t));
	if (argc == 3)
	{
		printf("MY RESULT :\nInitial '%s' length : '%zu'.\n", argv[1], \
			ft_strlcpy(dest1, argv[1], size));
		printf("ft_strlcpy return : '%s' ('%zu').\n", dest1, ft_strlen(dest1));
		printf("\nORIGINAL RESULT :\nInitial '%s' length is '%zu'.\n", \
			argv[1], strlcpy(dest2, argv[1], size));
		printf("strlcpy return : '%s' ('%zu').\n", dest1, ft_strlen(dest2));
	}
	return (0);
}
*/
