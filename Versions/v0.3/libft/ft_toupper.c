/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 17:49:29 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/11 17:49:37 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c - 32);
	return (c);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(int argc, char **argv)
{
	int	i;

	if (argc < 2)
	{	
		printf("Missing argument (at least one is expected).\n");
		return (1);
	}
	i = 1;
	printf("MY RESULT :\n");
	while (i < argc)
	{
		printf("| '%s' => '%c' |", argv[i], ft_toupper(*argv[i]));
		i++;
	}
	i = 1;
	printf("\n\nORIGINAL RESULT :\n");
	while (i < argc)
	{
		printf("| '%s' => '%c' |", argv[i], toupper(*argv[i]));
		i++;
	}
	printf("\n");
	return (0);
}
*/
