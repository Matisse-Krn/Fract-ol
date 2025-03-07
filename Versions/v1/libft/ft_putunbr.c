/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 21:25:28 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/28 21:25:32 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr(unsigned int nb)
{
	int		count;

	count = 0;
	if (nb > 9)
		count += ft_putunbr(nb / 10);
	count += ft_putchar((nb % 10) + '0');
	return (count);
}
/*
int	main(void)
{
	ft_putunbr(-2147483648);
	write (1, "\n", 1);
	ft_putunbr(-42);
	write (1, "\n", 1);
	ft_putunbr(-1);
	write (1, "\n", 1);
	ft_putunbr(0);
	write (1, "\n", 1);
	ft_putunbr(42);
	write (1, "\n", 1);
	ft_putunbr(2147483647);
	write (1, "\n", 1);
	return (0);
}
*/
