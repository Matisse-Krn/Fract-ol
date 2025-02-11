/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_tolower.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 02:40:11 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/09 02:56:30 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_str_tolower(char *s)
{
	int	i;

	if (!s)
		return ;
	i = -1;
	while (s[++i])
	{
		if (s[i] >= 'A' && s[i] <= 'Z')
			s[i] += 32;
	}
	return ;
}
/*
static void	main_test(char *s)
{
	char *str;

	if (!s)
		return ;
	str = ft_strdup(s);
	if (!str)
		return ;
	ft_printf("Initial	: '%s'\n", str);
	ft_str_tolower(str);
	ft_printf("Final	: '%s'\n\n", str);
	free(str);
}

int	main(void)
{
	main_test("Coucou");
	main_test("CoUcou");
	main_test("cOucou");
	main_test("Cou1cou");
	main_test("Cou1cou.");
	main_test("/Cou1cou");
	main_test("Cou1cou\t");
	main_test("\tCou1cou");
	main_test("\tCou1cou\t");
	return (0);
}
*/
