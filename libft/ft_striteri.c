/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 00:23:10 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/18 01:33:26 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	size_t	i;
	size_t	s_len;

	if (!s || !f)
		return ;
	s_len = ft_strlen(s);
	i = -1;
	while (++i < s_len)
		f(i, &s[i]);
	s[i] = '\0';
	return ;
}
/*
#include <stdio.h>

static void	ft_move_c(unsigned int i, char *c)
{
	if (i % 2 == 0)
		*c = *c + 1;
	else
		*c = *c - 1;
	return ;
}

int	main(void)
{
	char	str[] = "Hello World !";

	printf("'%s' => ", str);
	ft_striteri(str, *ft_move_c);
	printf("'%s'\n", str);
	return (0);
}
*/
