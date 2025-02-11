/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_bits.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 17:37:08 by mkerrien          #+#    #+#             */
/*   Updated: 2025/01/07 18:16:34 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

unsigned char	reverse_bits(unsigned char octet)
{
	unsigned char	out;
	int				i;

	i = -1;
	out = '0';
	while (++i < 8)
	{
		out <<= 1;
		if (octet % 2 == 1)
			out += 1;
		octet >>= 1;
	}
	return (out);
}
/*
#include <stdio.h>

int	main(void)
{
	unsigned char octet;
	unsigned char res;

	octet = 253;
	printf("Init :  %d\n", octet);
	res = reverse_bits(octet);
	printf("Res  :  %d\n", res);
	return (0);
}
*/
