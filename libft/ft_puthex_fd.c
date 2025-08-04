/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:42:28 by mkerrien          #+#    #+#             */
/*   Updated: 2025/03/09 18:52:13 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex_fd(unsigned long nbr, const int isupper, int fd)
{
	char	*base;
	int		count;

	count = 0;
	if (isupper == 0)
		base = "0123456789abcdef";
	else
		base = "0123456789ABCDEF";
	if (nbr >= 16)
	{
		count += ft_puthex_fd(nbr / 16, isupper, fd);
		count += ft_puthex_fd(nbr % 16, isupper, fd);
	}
	if (nbr < 16)
		count += ft_putchar_fd(base[nbr], fd);
	return (count);
}
