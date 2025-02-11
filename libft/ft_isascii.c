/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:05:00 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/10 18:40:52 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isascii(int c)
{
	if (c >= 0 && c <= 127)
		return (1);
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
			if (ft_isascii(*argv[i]))
				printf("      '%c' is ascii.\n", *argv[i]);
			else
				printf("      '%c' is NOT ascii.\n", *argv[i]);
			printf("ORIGINAL RESULT : ");
			if (isascii(*argv[i]))
				printf("'%c' is ascii.\n\n", *argv[i]);
			else
				printf("'%c' is NOT ascii.\n\n", *argv[i]);
			i++;
		}
	}
	return (0);
}
*/
