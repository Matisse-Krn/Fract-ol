/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:05:00 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/10 18:20:45 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (c);
	return (0);
}
/*
#include <stdio.h>
#include <ctype.h>
int	main(int argc, char **argv)
{
	int	i = 1;

	if (argc <= 1)
	{
		printf("Missing argument.\n");
		return (1);
	}
	if (argc > 1)
	{
		while (i < argc)
		{
			printf("\nMY RESULT : ");
			if (ft_isalpha(*argv[i]))
				printf("      '%c' is alpha.\n", *argv[i]);
			else
				printf("      '%c' is not alpha.\n", *argv[i]);
			printf("ORIGINAL RESULT : ");
			if (isalpha(*argv[i]))
				printf("'%c' is alpha.\n", *argv[i]);
			else
				printf("'%c' is not alpha.\n", *argv[i]);
			i++;
		}
	}
	return (0);
}
*/
