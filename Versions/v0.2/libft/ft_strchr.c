/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 20:58:28 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/12 00:40:45 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s - 1;
	while (*(++str) != (char)c)
	{
		if (!*str)
			return (0);
	}
	return ((char *)str);
}
/*
#include <stdio.h>
#include <string.h>
int	main(int argc, char **argv)
{
	char	*str = argv[1];

	if (argc < 3 || argc > 3)
	{
		if (argc < 3)
			printf("Missing argument (usage : in <str> point to <c>)");
		else if (argc > 3)
			printf("Too many arguments (usage : in <str> point to <c>)");
		return (1);
	}
	printf("MY RESULT :\n");
	if (!ft_strchr((const char *)str, (int)*argv [2]))
		printf("'%c' not found in '%s'.\n", *argv[2], str);
	else
		printf("'%c' found : '%s'", *argv[2], ft_strchr((const char *)str, \
(int)*argv[2]));

	printf("\n\nORIGINAL RESULT :\n");
	if (!strchr((const char *)str, (int)*argv [2]))
		printf("'%c' not found in '%s'.\n", *argv[2], str);
	else
		printf("'%c' found : '%s'", *argv[2], strchr((const char *)str, \
(int)*argv[2]));
	return (0);
}
*/
