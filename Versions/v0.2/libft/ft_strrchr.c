/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/12 00:06:07 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/12 02:50:13 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*str;
	char			*res;
	unsigned char	u_c;

	u_c = (unsigned char)c;
	if (u_c == '\0')
		return ((char *)s + ft_strlen(s));
	str = (char *)s - 1;
	res = NULL;
	while (*(++str))
	{
		if (*str == u_c)
			res = str;
	}
	return (res);
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
	if (!ft_strrchr((const char *)str, (int)*argv [2]))
		printf("'%c' not found in '%s'.\n", *argv[2], str);
	else
		printf("'%c' found : '%s'", *argv[2], ft_strrchr((const char *)str, \
(int)*argv[2]));
	printf("\n\nORIGINAL RESULT :\n");
	if (!strrchr((const char *)str, (int)*argv [2]))
		printf("'%c' not found in '%s'.\n", *argv[2], str);
	else
		printf("'%c' found : '%s'", *argv[2], strrchr((const char *)str, \
(int)*argv[2]));
	return (0);
}
*/
