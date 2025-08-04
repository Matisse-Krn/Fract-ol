/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/03 01:06:51 by mkerrien          #+#    #+#             */
/*   Updated: 2025/03/09 18:50:08 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_fd(void *ptr, int fd)
{
	int	count;

	count = 0;
	if (!ptr)
		return (ft_putstr_fd("(nil)", fd));
	count += ft_putstr_fd("0x", fd);
	count += ft_puthex_fd((unsigned long)ptr, 0, fd);
	return (count);
}
