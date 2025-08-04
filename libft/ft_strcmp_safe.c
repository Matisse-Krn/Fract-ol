/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp_safe.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:17:00 by mkerrien          #+#    #+#             */
/*   Updated: 2025/03/31 03:02:33 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
 * ft_strcmp_safe - Safely compares two C-strings, handling NULL inputs.
 *
 * This function compares the strings `s1` and `s2` lexicographically,
 * similarly to the standard `strcmp()` function, but includes additional
 * safety checks for NULL pointers. The result of the comparison is written
 * to the location pointed to by `cmp_result`.
 *
 * The function returns a status code indicating success or the type of error
 * encountered. In the case of a successful comparison, `cmp_result` will
 * contain:
 *   - A negative value if s1 < s2
 *   - Zero if s1 and s2 are equal
 *   - A positive value if s1 > s2
 *
 * @param s1          Pointer to the first null-terminated string
 * @param s2          Pointer to the second null-terminated string
 * @param cmp_result  Pointer to an int where the comparison result
 *						will be stored
 *
 * @return int        Status code:
 *                      0     -> Success
 *                     -1     -> s1 is NULL, s2 is not
 *                     -2     -> s2 is NULL, s1 is not
 *                     -3     -> Both s1 and s2 are NULL
 *                    -1000   -> cmp_result is NULL (invalid argument)
 *
 * Notes:
 *   - If either `s1` or `s2` is NULL, no comparison is performed,
 *     and `cmp_result` is not modified (remains INT_MIN).
 *   - The function assumes ASCII or compatible encoding for comparison.
*/

int	ft_strcmp_safe(const char *s1, const char *s2, int *cmp_result)
{
	if (!cmp_result)
		return (-1000);
	*cmp_result = INT_MIN;
	if (!s1 && !s2)
		return (-3);
	if (!s1)
		return (-1);
	if (!s2)
		return (-2);
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	*cmp_result = (unsigned char)*s1 - (unsigned char)*s2;
	return (0);
}
