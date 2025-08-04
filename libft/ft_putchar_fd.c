/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 01:35:35 by mkerrien          #+#    #+#             */
/*   Updated: 2025/03/09 18:49:05 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

int	ft_putchar_fd(char c, int fd)
{
	if (fd < 0)
		return (-1);
	write (fd, &c, 1);
	return (1);
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*file;
	char	c;

	if (argc != 3)
	{
		if (argc < 3)
			printf("Missing argument (usage : write <c> in file <fd>)\n");
		if (argc > 3)
			printf("Too many arguments (usage : write <c> in file <fd>)\n");
		return (1);
	}
	c = *argv[1];
	file = argv[2];
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Error when openning file\n");
		return (1);
	}
	ft_putchar_fd(c, fd);
	if (close(fd) == -1)
	{
		printf("Error when clossing file\n");
		return (1);
	}
	printf("'%c' wroted in '%s'\n", c, file);
	return (0);
}
*/
