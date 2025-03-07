/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:54:29 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/10 20:44:42 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}
/*
#include <stdio.h>
#include <string.h>
int	main(int argc, char **argv)
{
	if (argc == 1)
	{
		printf("Missing argument.\n");
		return (1);
	}
	if (argc == 2)
	{
		printf("MY RESULT : '%s' length = '%zu'.\n", argv[1], \
		ft_strlen(argv[1]));
		printf("ORIGINAL RESULT : '%s' length = '%zu'.\n", argv[1], \
		strlen(argv[1]));
	}
	else if (argc > 2)
	{
		printf("Too many arguments.\n");
		return (1);
	}
	return (0);
}
*/
