/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/18 03:02:32 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/18 03:13:41 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	size_t	i;

	if (fd < 0)
		return ;
	i = -1;
	while (s[++i])
		ft_putchar_fd(s[i], fd);
	return ;
}
/*
#include <stdio.h>
#include <fcntl.h>

int	main(int argc, char **argv)
{
	int		fd;
	char	*file;
	char	*str;

	if (argc != 3)
	{
		if (argc < 3)
			printf("Missing argument (usage : write <s> in file <fd>)\n");
		if (argc > 3)
			printf("Too many arguments (usage : write <s> in file <fd>)\n");
		return (1);
	}
	str = argv[1];
	file = argv[2];
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
	{
		printf("Error when openning file\n");
		return (1);
	}
	ft_putstr_fd(str, fd);
	if (close(fd) == -1)
	{
		printf("Error when clossing file\n");
		return (1);
	}
	printf("'%s' wroted in '%s'\n", str, file);
	return (0);
}
*/
