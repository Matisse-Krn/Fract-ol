/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 14:25:05 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/14 14:26:14 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

// Renvoie une nouvelle chaine de taille 'len' extraite depuis
// l'index 'start' de 's';
// Si l'index 'start' est superieur ou egal a la taille de 's',
// alors on retourne NULL;
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	s_len;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	if (start >= s_len)
	{
		sub = ft_calloc(1, 1);
		if (!sub)
			return (NULL);
		return (sub);
	}
	if (len > (s_len - start))
		len = s_len - start;
	sub = ft_calloc(sizeof(char), (len + 1));
	if (!sub)
		return (NULL);
	i = -1;
	while (++i < len && start < s_len)
		sub[i] = s[start + i];
	sub[i] = '\0';
	return (sub);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	char	*my_res;

	if (argc != 4)
	{
		if (argc < 4)
			printf("Missing argument (usage : duplicate <str> in a new string, \
from str[<start>]. New string is of <size> max)\n");
		if (argc > 4)
			printf("Too many arguments (usage : duplicate <str> in a new \
string, from str[<start>]. New string is of <size> max)\n");
		return (1);
	}
	my_res = ft_substr((char const *)argv[1], (unsigned int)atoi(argv[2]), \
(size_t)atoi(argv[3]));
	printf("MY RESULT : '%s'\n", my_res);
	printf("'%zu'\n", ft_strlen(my_res));
	return (0);
}
*/
