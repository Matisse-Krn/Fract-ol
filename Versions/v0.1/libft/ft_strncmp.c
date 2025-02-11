/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 13:35:30 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/12 14:41:18 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		else if (!s1[i] || !s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
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
			printf("Missing argument (usage : compare <str1> and <str2> in \
<size> bytes)");
		else if (argc > 4)
			printf("Too many arguments (usage : compare <str1> and <str2> in \
<size> bytes)");
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
