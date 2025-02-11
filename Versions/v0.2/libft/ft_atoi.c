/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 16:41:16 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/13 17:01:12 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char	*nptr)
{
	int	i;
	int	s_count;
	int	result;

	i = 0;
	s_count = 1;
	result = 0;
	while (nptr[i] == ' ' || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '-')
	{
		s_count *= -1;
		i++;
	}
	else if (nptr[i] == '+')
		i++;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		result = result * 10 + (nptr[i] - '0');
		i++;
	}
	return (result * s_count);
}
/*
#include <stdlib.h>
#include <stdio.h>
int	main(int argc, char **argv)
{
	int	  my_res;
	int	  o_res;

	if (argc < 2 || argc > 2)
	{
		if (argc < 2)
			printf("Missing argument (usage : change <str> to int)\n");
		else if (argc > 2)
			printf("Too many arguments (usage : change <str> to int)\n");
		return (1);
	}
	my_res = ft_atoi(argv[1]);
	o_res = atoi(argv[1]);
	printf("MY RESULT :		'%d'\nORIGINAL RESULT :	'%d'\n", my_res, o_res);
	if (my_res != o_res)
		printf("\nERROR !\n");
	return (0);
}
*/
