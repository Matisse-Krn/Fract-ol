/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 18:28:46 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/11 18:30:02 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
		return (c + 32);
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
		printf("| '%s' => '%c' |", argv[i], ft_tolower(*argv[i]));
		i++;
	}
	i = 1;
	printf("\n\nORIGINAL RESULT :\n");
	while (i < argc)
	{
		printf("| '%s' => '%c' |", argv[i], tolower(*argv[i]));
		i++;
	}
	printf("\n");
	return (0);
}
*/
