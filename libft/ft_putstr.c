/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 18:26:26 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/28 18:28:26 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putstr(char *str)

{
	unsigned int	i;

	if (!str)
	{
		write(1, "(null)", 6);
		return (6);
	}
	i = -1;
	while (str[++i])
		ft_putchar(str[i]);
	return (i);
}
