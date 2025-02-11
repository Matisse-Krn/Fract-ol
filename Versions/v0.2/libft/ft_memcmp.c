/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 21:04:38 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/12 21:06:17 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = -1;
	while (++i < n)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	}
	if (i < n)
		return (str1[i] - str2[i]);
	return (0);
}
/*
#include <stdio.h>
#include <string.h>
int	main(int argc, char **argv)
{
	int	res;
	int	o_res;

	if (argc < 4 || argc > 4)
	{
		if (argc < 4)
			printf("Missing argument (usage : compare <str1> and <str2> \
in <size> bytes)");
		else if (argc > 4)
			printf("Too many arguments (usage : compare <str1> and <str2> \
in <size> bytes)");
		return (1);
	}
	res = ft_strncmp((const char *)argv[1], (const char *)argv[2], \
atoi(argv[3]));
	o_res = strncmp((const char *)argv[1], (const char *)argv[2], \
atoi(argv[3]));
	printf("MY RESULT :\n");
	if (res < 0)
		printf("<str1> is less than <str2> (%d)\n", res);
	else if (res > 0)
		printf("<str1> is greater than <str2> (%d)\n", res);
	else
		printf("<str1> and <str2> are equal (%d)\n", res);
	printf("\nORIGINAL RESULT :\n");
	if (o_res < 0)
		printf("<str1> is less than <str2> (%d)\n", o_res);
	else if (o_res > 0)
		printf("<str1> is greater than <str2> (%d)\n", o_res);
	else
		printf("<str1> and <str2> are equal (%d)\n", o_res);
	if (res != o_res)
		printf("\nERROR !\n");
	return (0);
}
*/
