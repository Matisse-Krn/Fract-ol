/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 14:41:27 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/12 14:44:53 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	size_t			i;

	ptr = (unsigned char *)s;
	i = -1;
	while (++i < n)
	{
		if (ptr[i] == (unsigned char)c)
			return ((void *)(ptr + i));
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int	main(int argc, char **argv)
{
	void	*str;
	size_t	size;
	void	*my_res;
	void	*o_res;

	if (argc < 3 || argc > 3)
	{
		if (argc < 3)
			printf("Missing argument (usage : in a given memory block, \
search <c>; block of memory <size>)");
		else if (argc > 3)
			printf("Too many arguments (usage : in a given memory block, \
search <c>; block of memory <size>)");
		return (1);
	}
	size = strtoul(argv[2], NULL, 10);
	str = ft_calloc(1, size);
	if (!str)
	{
		printf("ft_calloc problem.");
		return (1);
	}
	//To place 'c' in the memory block, for the test.
	((unsigned char *)str)[5] = (unsigned char)*argv[1];
	my_res = ft_memchr(str, (int)*argv[1], size);
	o_res = memchr(str, (int)*argv[1], size);
	printf("MY RESULT :\n");
	if (!my_res)
		printf("'%c' not found in mem-block '%p' of size '%zu'.\n", \
*argv[1], str, size);
	else
		printf("'%c' found in '%p' and is at '%p' adress", *argv[1], \
str, my_res);
	printf("\nORIGINAL RESULT :\n");
	if (!o_res)
		printf("'%c' not found in mem-block '%p' of size '%zu'.\n", *argv[1], \
str, size);
	else
		printf("'%c' found in '%p' and is at '%p' adress\n", *argv[1], \
str, o_res);
	free((void *)str);
	return (0);
}
*/
