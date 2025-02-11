/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 22:37:21 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/10 18:24:21 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_isalnum(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') \
	|| (c >= '0' && c <= '9'))
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
			if (ft_isalnum(*argv[i]))
				printf("      '%c' is alphanum.\n", *argv[i]);
			else
				printf("      '%c' is not alphanum.\n", \
				*argv[i]);
			printf("ORIGINAL RESULT : ");
			if (isalnum(*argv[i]))
				printf("'%c' is alphanum.\n", *argv[i]);
			else
				printf("'%c' is not alphanum.\n", *argv[i]);
			i++;
		}
	}
	return (0);
}
*/
