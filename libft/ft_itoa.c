/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/17 02:10:58 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/17 03:16:15 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static unsigned int	ft_intlen(int n)
{
	unsigned int	size;
	unsigned int	nbr;

	if (n == 0)
		return (1);
	size = 0;
	if (n < 0)
	{
		size++;
		nbr = -n;
	}
	else
		nbr = n;
	while (nbr > 0)
	{
		size++;
		nbr /= 10;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char			*dst;
	unsigned int	l_int;
	unsigned int	nbr;

	l_int = ft_intlen(n);
	dst = ft_calloc(l_int + 1, sizeof(char));
	if (!dst)
		return (NULL);
	nbr = n;
	if (n < 0)
	{
		nbr = -n;
		dst[0] = '-';
	}
	dst[l_int] = '\0';
	if (n == 0)
		dst[0] = '0';
	while (l_int-- > 0 && nbr != 0)
	{
		dst[l_int] = (nbr % 10 + '0');
		nbr /= 10;
	}
	return (dst);
}
/*
#include <stdio.h>
int	main(void)
{
	int		i;

	i = 0;
	printf("'%s'\n", ft_itoa(i));
	return (0);
}
*/
