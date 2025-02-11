/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/14 21:03:46 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/14 21:03:52 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s3;
	size_t	l_s1;
	size_t	l_s2;

	l_s1 = ft_strlen(s1);
	l_s2 = ft_strlen(s2);
	s3 = malloc(sizeof(char) * (l_s1 + l_s2 + 1));
	if (!s3)
		return (NULL);
	ft_strlcpy(s3, s1, l_s1 + 1);
	while (*s2)
		s3[l_s1++] = *s2++;
	s3[l_s1] = '\0';
	return (s3);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	char	*res;

	if (argc != 3)
	{
		if (argc > 3)
			printf("Too many arguments (usage : concatenate <s1> + <s2> in \
a new string)\n");
		if (argc < 3)
			printf("Missing argument (usage : concatenate <s1> + <s2> in \
a new string)\n");
		return (1);
	}
	res = ft_strjoin(argv[1], argv[2]);
	printf("'%s' + '%s' = '%s'\n", argv[1], argv[2], res);
	return (0);
}
*/
