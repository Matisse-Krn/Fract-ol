/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_int_overflow.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 19:57:12 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/12 19:57:15 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Find the real length of a number represented by a string :
 *		- "2147483647" = 10   ->   "0002147483647" = 10
 *		- "+78" = 2			  ->   "+0078" = 2
 *		- "0" = 1			  ->   -0" = 1
 * Because we use this in 'delete_surplus()' after treating the cases of "-000",
 *	  we can't have an input who 's' = "-0000" (or "+0", "-0", "+00",...)
*/
static int	real_length(char *s)
{
	int		i;
	int		len;

	i = 0;
	len = 0;
	if (s[i] == '+')
		i++;
	if (s[i] == '-')
	{
		len++;
		i++;
	}
	while (s[i] == '0')
		i++;
	while (s[i++])
		len++;
	return (len);
}

/*
 * Return 0 if the value of the int represented by 's' is 0 
 *	  ('+000', '-0000', '+0',...), or return 1
*/
static int	str_is_zero(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	while (s[i] == '0')
		i++;
	if (!s[i])
		return (0);
	return (1);
}

/*
 * Delete all superfluous char :
 *		-	"0045"	 ->  "45"
 *		-	"-0045"  ->  "-45"
 *		-	"+45"	 ->  "45"
 *		-	"+0045"  ->  "45"
 *		-	"-0"	 ->  "0"
*/
static char	*delete_surplus(char *s)
{
	int		i;
	int		j;
	int		len;
	char	*dst;

	if (str_is_zero(s) == 0)
	{
		dst = ft_calloc(2, sizeof(char));
		dst[0] = '0';
		return (dst);
	}
	len = real_length(s);
	dst = ft_calloc(len + 1, sizeof(char));
	i = 0;
	j = 0;
	if (s[i] == '-')
	{
		i++;
		dst[j++] = '-';
	}
	while (s[i] == '0')
		i++;
	while (s[i])
		dst[j++] = s[i++];
	return (dst);
}

/*
 * Check if the element 's' :
 *		- is only constitute by a single '-' or '+' sign at the beginning,
 *		and only digits char after
 *		- is not only a single '+' or '-' without anything else
 * Return 0 if the element is valid, otherwise return 1
*/
static int	check_is_valid_digit(char *s)
{
	int	i;
	int	sign;

	i = -1;
	sign = 0;
	while (s[++i])
	{
		if (!(s[i] >= '0' && s[i] <= '9') && s[i] != '-' && s[i] != '+')
			return (1);
		if (s[i] == '+' || s[i] == '-')
		{
			sign++;
			if (!s[i + 1] || sign > 1)
				return (1);
		}
	}
	return (0);
}

/*
 * 1. Check if the element is valid :
 *		- is only constitute by a single '-' or '+' sign at the beginning,
 *		and only digits char after
 *		- is not only a single '+' or '-' without anything else
 *		- the sign can be followed by a arbitrary amount of '0'
 *		
 *		Examples of valid inputs at this step :
 *				- "+0012"
 *				- "-00012"
 *				- "-00123456789123456789"
 *				- "-12"
 *				- "12"
 *				- "012"
 *				- ...
 *
 * Convert string to integer with 'ft_atoi()' -> 'atoi_res'
 * Convert 'atoi_res' to string with 'ft_itoa()' -> 'itoa_res'
 * Normalize element (“+00045” -> “45”,...), and compare with 'itoa_res'
 *
 * Return -1 if the element is not valid,
 * Return 1 if the element is int overflow,
 * Return 0 if the element is valid and not int overflow
*/
int	ft_check_int_overflow(char *s)
{
	int		atoi_res;
	char	*itoa_res;
	char	*simple_s;

	if (check_is_valid_digit(s) != 0)
		return (-1);
	atoi_res = ft_atoi(s);
	if (atoi_res == 0 && str_is_zero(s) != 0)
		return (-1);
	itoa_res = ft_itoa(atoi_res);
	simple_s = delete_surplus(s);
	s = simple_s;
	if (ft_strcmp(itoa_res, s))
	{
		free(simple_s);
		free(itoa_res);
		return (1);
	}
	free(itoa_res);
	free(simple_s);
	return (0);
}
/*
int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (check_int_overflow(argv[1]) == -1)
			ft_printf("Element '%s' is not valid.\n\n", argv[1]);
		else if (check_int_overflow(argv[1]) == 1)
				ft_printf("Element '%s' is an int overflow.\n\n", argv[1]);
		else if (check_int_overflow(argv[1]) == 0)
				ft_printf("Element '%s' is not an int overflow.\n\n", argv[1]);
	}
	else
		ft_printf("Usage : ./a.out <number_to_check>.\n");
	return (0);
}
*/
