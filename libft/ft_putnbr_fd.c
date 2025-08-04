/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 05:10:15 by mkerrien          #+#    #+#             */
/*   Updated: 2025/03/09 19:41:50 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putnbr_fd(int n, int fd)
{
	int	count;

	if (fd < 0)
		return (-1);
	count = 0;
	if (n == -2147483648)
		return (ft_putstr_fd("-2147483648", fd));
	else if (n < 0)
	{
		count += ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		count += ft_putnbr_fd((n / 10), fd);
		count += ft_putnbr_fd((n % 10), fd);
	}
	else
		count += ft_putchar_fd((n + '0'), fd);
	return (count);
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int		fd;
	int		ret;
	fd = 2;

	ret = ft_putnbr_fd(-2147483648, fd);
	printf("\nret = %d char\n", ret);

	ret = ft_putnbr_fd(-42, fd);
	printf("\nret = %d char\n", ret);
	
	ret = ft_putnbr_fd(0, fd);
	printf("\nret = %d char\n", ret);
	
	ret = ft_putnbr_fd(42, fd);
	printf("\nret = %d char\n", ret);
	
	ret = ft_putnbr_fd(2147483647, fd);
	printf("\nret = %d char\n", ret);
	
	return (0);
}
*/
