/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ltoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 23:07:04 by mkerrien          #+#    #+#             */
/*   Updated: 2025/08/03 23:56:36 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_zero_str(void)
{
	char	*str;

	str = ft_calloc(2, sizeof(char));
	if (!str)
		return (NULL);
	str[0] = '0';
	str[1] = '\0';
	return (str);
}

static unsigned long long	ft_abs_val(long long n, int *sign)
{
	*sign = (n < 0);
	if (*sign)
		return ((unsigned long long)(-(n + 1)) + 1ULL);
	return ((unsigned long long)n);
}

static size_t	ft_count_digits_ull(unsigned long long un)
{
	size_t	len;

	if (un == 0ULL)
		return (1);
	len = 0;
	while (un > 0ULL)
	{
		len++;
		un /= 10ULL;
	}
	return (len);
}

static void	ft_write_ull_to_str(char *str, unsigned long long un, size_t len)
{
	while (un > 0ULL)
	{
		str[--len] = (char)('0' + (un % 10ULL));
		un /= 10ULL;
	}
}

char	*ft_ltoa(long long n)
{
	char				*str;
	unsigned long long	un;
	size_t				len;
	int					sign;

	if (n == 0)
		return (ft_zero_str());
	un = ft_abs_val(n, &sign);
	len = ft_count_digits_ull(un);
	if (sign)
		len += 1;
	str = ft_calloc((len + 1), sizeof(char));
	if (!str)
		return (NULL);
	str[len] = '\0';
	ft_write_ull_to_str(str, un, len);
	if (sign)
		str[0] = '-';
	return (str);
}
