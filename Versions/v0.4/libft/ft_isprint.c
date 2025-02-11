/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:47:21 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/10 18:25:12 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isprint(int c)
{
	if (c >= 32 && c <= 126)
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
			if (ft_isprint(*argv[i]))
				printf("      '%c' is printable.\n", *argv[i]);
			else
				printf("      '%c' is NOT printable.\n", \
				*argv[i]);
			printf("ORIGINAL RESULT : ");
			if (isprint(*argv[i]))
				printf("'%c' is printable.\n\n", *argv[i]);
			else
				printf("'%c' is NOT printable.\n\n", *argv[i]);
			i++;
		}
	}
	return (0);
}
*/
