/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 00:46:55 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/15 01:27:35 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	char const		*start;
	char const		*end;
	char			*dst;
	size_t			l_dst;

	if (!s1 || !set)
		return (NULL);
	start = s1;
	while (*start && (ft_strchr(set, *start)))
		start++;
	end = s1 + ft_strlen(s1) - 1;
	while (end > start && ft_strchr(set, *end))
		end--;
	l_dst = end - start + 1;
	dst = ft_calloc(l_dst + 1, sizeof(char));
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, start, l_dst + 1);
	return (dst);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	if (argc != 3)
	{
		if (argc < 3)
			printf("Missing argument (usage : duplicate <s1> without <set> \
characters at the beginning and at the and)\n");
		else if (argc > 3)
			printf("Too many arguments (usage : duplicate <s1> without <set> \
characters at the beginning and at the and)\n");
		return (1);
	}
	printf("<s1> = '%s' || <set> = '%s'\n'%s'\n", argv[1], argv[2], \
ft_strtrim(argv[1], argv[2]));
	return (0);
}
*/
