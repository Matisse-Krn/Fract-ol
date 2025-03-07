/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 05:10:15 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/18 05:25:34 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putnbr_fd(int n, int fd)
{
	if (fd < 0)
		return ;
	if (n == -2147483648)
	{
		write(fd, "-2147483648", 11);
		return ;
	}
	else if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = -n;
	}
	if (n > 9)
	{
		ft_putnbr_fd((n / 10), fd);
		ft_putnbr_fd((n % 10), fd);
	}
	else
		ft_putchar_fd((n + '0'), fd);
	return ;
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*file;
	int		nb;

	if (argc != 3)
	{
		if (argc < 3)
			printf("Missing argument (usage : write <n> in file <fd>)\n");
		if (argc > 3)
			printf("Too many arguments (usage : write <n> in file <fd>)\n");
		return (1);
	}
	nb = ft_atoi(argv[1]);
	file = argv[2];
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Error when openning file\n");
		return (1);
	}
	ft_putnbr_fd(nb, fd);
	if (close(fd) == -1)
	{
		printf("Error when clossing file\n");
		return (1);
	}
	printf("'%d' wroted in '%s'\n", nb, file);
	return (0);
}
*/
