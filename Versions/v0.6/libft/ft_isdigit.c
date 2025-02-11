/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:31:07 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/10 18:24:54 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
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
			if (ft_isdigit(*argv[i]) != 0)
				printf("      '%c' is digit.\n", *argv[i]);
			else
				printf("      '%c' is not digit.\n", *argv[i]);
			printf("ORIGINAL RESULT : ");
			if (isdigit(*argv[i]) != 0)
				printf("'%c' is digit.\n", *argv[i]);
			else
				printf("'%c' is not digit.\n", *argv[i]);
			i++;
		}
	}
	return (0);
}
*/
