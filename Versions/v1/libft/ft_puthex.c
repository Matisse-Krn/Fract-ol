/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 16:31:12 by mkerrien          #+#    #+#             */
/*   Updated: 2024/12/02 16:31:37 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puthex(unsigned long nbr, const int isupper)
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
		count += ft_puthex(nbr / 16, isupper);
		count += ft_puthex(nbr % 16, isupper);
	}
	if (nbr < 16)
		count += ft_putchar(base[nbr]);
	return (count);
}
