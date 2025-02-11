/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 13:41:36 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/14 14:03:35 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strdup(const char *s)
{
	char	*dup;
	int		i;

	dup = malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!dup)
		return (NULL);
	i = -1;
	while (s[++i])
		dup[i] = s[i];
	dup[i++] = '\0';
	return (dup);
}
/*
#include <stdio.h>
#include <string.h>
int	main(int argc, char **argv)
{
	char	*my_res;
	char	*o_res;	

	if (argc != 2)
	{
		if (argc < 2)
			printf("Missing argument (usage : duplicate <str> \
in a new string)\n");
		if (argc > 2)
			printf("Too many arguments (usage : duplicate <str> \
in a new string)\n");
		return (1);
	}
	my_res = ft_strdup((const char *)argv[1]);
	o_res = strdup((const char *)argv[1]);
	printf("MY RESULT : '%s'\nORIGINAL RESULT : '%s'\n", my_res, o_res);
	if (my_res != o_res)
		printf("ERROR !\n");
	return (0);
}
*/
