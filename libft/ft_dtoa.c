/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dtoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 21:18:45 by mkerrien          #+#    #+#             */
/*   Updated: 2025/08/03 23:57:21 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned long long	ft_get_frac_int(double frac_part, int precision,
										double *int_part)
{
	unsigned long long	frac_int;
	double				scale;
	double				scaled_frac;

	frac_int = 0ULL;
	if (precision > 0)
	{
		scale = pow(10.0, precision);
		scaled_frac = frac_part * scale + 0.5;
		frac_int = (unsigned long long)scaled_frac;
		if (frac_int >= (unsigned long long)scale)
		{
			frac_int = 0ULL;
			*int_part += 1.0;
		}
	}
	else
	{
		if (frac_part >= 0.5)
			*int_part += 1.0;
	}
	return (frac_int);
}

static char	*ft_fill_int_part(char *res, char *int_str, int sign)
{
	char	*res_ptr;
	char	*tmp;

	res_ptr = res;
	if (sign)
		*res_ptr++ = '-';
	tmp = int_str;
	while (*tmp)
		*res_ptr++ = *tmp++;
	free(int_str);
	return (res_ptr);
}

static char	*ft_fill_fraction(char *res_ptr, unsigned long long frac_int,
							int precision)
{
	int	p;

	*res_ptr++ = '.';
	p = precision - 1;
	while (p >= 0)
	{
		res_ptr[p] = '0' + (frac_int % 10ULL);
		frac_int /= 10ULL;
		p--;
	}
	return (res_ptr + precision);
}

static char	*ft_compose_result(int sign, char *int_str,
							unsigned long long frac_int, int precision)
{
	size_t	int_len;
	size_t	size;
	char	*res;
	char	*res_ptr;

	int_len = ft_strlen(int_str);
	size = int_len + 1;
	if (sign)
		size += 1;
	if (precision > 0)
		size += precision + 1;
	res = ft_calloc(size, sizeof(char));
	if (!res)
	{
		free(int_str);
		return (NULL);
	}
	res_ptr = ft_fill_int_part(res, int_str, sign);
	if (precision > 0)
		res_ptr = ft_fill_fraction(res_ptr, frac_int, precision);
	*res_ptr = '\0';
	return (res);
}

char	*ft_dtoa(double n, int precision)
{
	double				int_part;
	double				frac_part;
	unsigned long long	frac_int;
	char				*int_str;
	int					sign;

	if (precision < 0)
		precision = 0;
	if (precision > 15)
		precision = 15;
	sign = (n < 0.0);
	if (sign)
		n = -n;
	frac_part = modf(n, &int_part);
	frac_int = ft_get_frac_int(frac_part, precision, &int_part);
	int_str = ft_ltoa((long long)int_part);
	if (!int_str)
		return (NULL);
	return (ft_compose_result(sign, int_str, frac_int, precision));
}
/**/
/*#include <stdio.h>*/
/*int	main(void)*/
/*{*/
/*	char	*s = ft_dtoa(-0.743643887037151, 15);*/
/**/
/*	printf("%s\n", s);*/
/*	s = ft_dtoa(123456789.012345678910111213, 15);*/
/*	printf("%s\n", s);*/
/*	free(s);*/
/*}*/
