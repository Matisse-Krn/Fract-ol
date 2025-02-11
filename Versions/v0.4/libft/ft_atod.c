/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 05:54:05 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/06 05:56:11 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_valid_number(const char *str)
{
	int	has_digits;
	int	has_dot;

	if (!str)
		return (0);
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
		*str == '\r' || *str == '\f' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	has_digits = 0;
	has_dot = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			has_digits = 1;
		else if ((*str == '.' || *str == ',') && !has_dot)
			has_dot = 1;
		else
			return (0);
		str++;
	}
	return (has_digits);
}

static const char	*skip_whitespace_and_sign(const char *str, int *sign)
{
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
		*str == '\r' || *str == '\f' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			*sign = -1;
		str++;
	}
	return (str);
}

static double	parse_integer_part(const char **str)
{
	double	result;

	result = 0.0;
	while (**str >= '0' && **str <= '9')
	{
		result = result * 10.0 + (**str - '0');
		(*str)++;
	}
	return (result);
}

static double	parse_fractional_part(const char **str)
{
	double	fraction;
	double	divisor;

	fraction = 0.0;
	divisor = 1.0;
	if (**str == '.' || **str == ',')
	{
		(*str)++;
		while (**str >= '0' && **str <= '9')
		{
			fraction = fraction * 10.0 + (**str - '0');
			divisor *= 10.0;
			(*str)++;
		}
	}
	return (fraction / divisor);
}

/*
 * @brief Convertit une chaîne de caractères en double.
 * @param str La chaîne de caractères contenant le nombre.
 * @return La valeur convertie en double.
*/
double	ft_atod(const char *str)
{
	double	result;
	int		sign;

	if (!str || !is_valid_number(str))
		return (0);
	sign = 1;
	str = skip_whitespace_and_sign(str, &sign);
	result = parse_integer_part(&str);
	result += parse_fractional_part(&str);
	return (sign * result);
}
/*
#include <stdio.h>

int	main(void)
{
	printf("Usage : ./a.out <char *double>\n");
	printf("Précision maximale d'un double : %d \
chiffres significatifs\n", DBL_DIG);
	printf("1.25		  = %.15f\n", ft_atod("1.25"));
	printf("1.3		  = %.15f\n", ft_atod("1.3"));
	printf("123123123.00	  = %.15f\n", ft_atod("123123123.00"));
	printf("12.293123		  = %.15f\n", ft_atod("12.293123"));
	printf("2312312312.123123 = %.15f\n", ft_atod("2312312312.123123"));
	printf("2312312312.12312  = %.15f\n", ft_atod("2312312312.12312"));
	printf("2312312312.1231	  = %.15f\n", ft_atod("2312312312.1231"));
	printf("1.2345678		  = %.15f\n", ft_atod("1.2345678"));
	printf("1.02345678		  = %.15f\n", ft_atod("1.02345678"));
	return (0);
}
*/
