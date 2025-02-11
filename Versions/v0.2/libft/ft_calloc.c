/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 19:20:00 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/14 01:53:52 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	ptr = malloc(nmemb * size);
	if (!ptr)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}
/*
#include <stdio.h>
int	main(int argc, char **argv)
{
	void	*my_res;
	void	*o_res;

	if (argc != 3)
	{
		if (argc > 3)
			printf("Too many arguments (usage : allocate memory for an array \
of <nmemb> elements of size <size>)\n");
		if (argc < 3)
			printf("Missing argument (usage : allocate memory for an array of \
<nmemb> elements of size <size>)\n");
		return (1);
	}
	my_res = ft_calloc((size_t)argv[1], (size_t)argv[2]);
	o_res = calloc((size_t)argv[1], (size_t)argv[2]);
	printf("MY RESULT : '%p'\nORIGINAL RESULT : '%p'\n", my_res, o_res);
	if (o_res != my_res)
		printf("ERROR !\n");
	return (0);
}
*/
