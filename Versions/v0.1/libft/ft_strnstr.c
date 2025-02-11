/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:25:19 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/13 14:50:29 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	d;

	if (!*little)
		return ((char *)big);
	else if (len == 0)
		return (NULL);
	d = 0;
	i = 0;
	while (big[i] && d <= len - 1)
	{
		i = d;
		j = 0;
		while (big[i] == little[j] && little[j])
		{
			if (!little[j + 1] && i < len)
				return ((char *)&big[d]);
			i++;
			j++;
		}
		d++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <bsd/string.h>
int	  main(int argc, char **argv)
{
	char	*str;
	char	*to_find;
	char	*my_res;
	char	*o_res;
	size_t	x;

	if (argc < 4 || argc > 4)
	{
		if (argc < 4)
			printf("Missing argument (usage : in <str> search \
<to_find> in first <x> bytes of str)\n");
		if (argc > 4)
			printf("Too many arguments (usage : in <str> search \
<to_find> in first <x> bytes of str)\n");
		return (1);
	}
	str = (char *)argv[1];
	to_find = (char *)argv[2];
	x = (size_t)atoi(argv[3]);
	my_res = ft_strnstr(str, to_find, x);
	printf("MY RESULT : '%s'\n", my_res);
	o_res = strnstr(str, to_find, x);
	printf("\nORIGINAL RESULT : '%s'\n", o_res);
	if (my_res != o_res)
		printf("\nERROR !\n");
	return (0);
}
*/
