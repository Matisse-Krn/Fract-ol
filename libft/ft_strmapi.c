/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 21:19:18 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/17 22:24:23 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	size_t	i;
	size_t	s_len;
	char	*str;

	if (!s || !f)
		return (NULL);
	s_len = ft_strlen(s);
	str = ft_calloc(s_len + 1, sizeof(char));
	if (!str)
		return (NULL);
	i = -1;
	while (++i < s_len)
		str[i] = f(i, s[i]);
	str[i] = '\0';
	return (str);
}
/*
#include <stdio.h>

static char	ft_move_c(unsigned int i, char c)
{
	char	str;

	if (i % 2 == 0)
		str = c + 1;
	else
		str = c - 1;
	return (str);
}

int	main(void)
{
	char	*src;
	char	*dst;

	src = "abc";
	dst = ft_strmapi(src, *ft_next_c);
	printf("'%s' => '%s'\n", src, dst);
	free(dst);
	return (0);
}
*/
