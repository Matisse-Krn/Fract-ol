/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:40:52 by mkerrien          #+#    #+#             */
/*   Updated: 2025/03/09 18:41:09 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putunbr_fd(unsigned int nb, int fd)
{
	int		count;

	count = 0;
	if (nb > 9)
		count += ft_putunbr_fd(nb / 10, fd);
	count += ft_putchar_fd((nb % 10) + '0', fd);
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
