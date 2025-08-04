/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp_safe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/31 01:21:02 by mkerrien          #+#    #+#             */
/*   Updated: 2025/03/31 03:05:03 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/*
 * ft_strncmp_safe - Safely compares up to 'n' characters of two C-strings,
 *                   handling NULL inputs.
 *
 * This function performs a lexicographical comparison of the first `n`
 * characters of the strings `s1` and `s2`, similarly to the standard
 * `strncmp()` function, but includes additional safety checks for NULL pointers.
 * The comparison result is written to the location pointed to by `cmp_result`.
 *
 * The comparison stops when either:
 *   - A differing character is found,
 *   - A null terminator (`'\0'`) is encountered in either string,
 *   - Or `n` characters have been compared.
 *
 * If the strings are equal for the first `n` characters,
 * *cmp_result` will be 0.
 * Otherwise, it will contain the difference between the first differing
 * characters, interpreted as `unsigned char`.
 *
 * @param s1          Pointer to the first null-terminated string
 * @param s2          Pointer to the second null-terminated string
 * @param n           Maximum number of characters to compare
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
 *   - If `n == 0`, the function returns success and sets `*cmp_result = 0`.
 *   - The function assumes ASCII or compatible encoding for comparison.
*/

int	ft_strncmp_safe(const char *s1, const char *s2, size_t n, int *cmp_result)
{
	size_t	i;

	if (!cmp_result)
		return (-1000);
	*cmp_result = INT_MIN;
	if (!s1 && !s2)
		return (-3);
	if (!s1)
		return (-1);
	if (!s2)
		return (-2);
	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i] || !s1[i] || !s2[i])
		{
			*cmp_result = ((unsigned char)s1[i] - (unsigned char)s2[i]);
			return (0);
		}
		i++;
	}
	*cmp_result = 0;
	return (0);
}
/*
#include <stdio.h>

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


void print_string_or_null(const char *s)
{
	if (s == NULL)
		printf("NULL");
	else
		printf("\"%s\"", s);
}

void test_strcmp(const char *s1, const char *s2)
{
	int	result;
	int	status;

	printf("== ft_strcmp_safe(");
	print_string_or_null(s1);
	printf(", ");
	print_string_or_null(s2);
	printf(") ==\n");

	status = ft_strcmp_safe(s1, s2, &result);
	printf("Return: %d | cmp_result: %d\n", status, result);
	printf("\n-----------------------------\n\n");
}

void test_strncmp(const char *s1, const char *s2, size_t n)
{
	int	result;
	int	status;

	printf("== ft_strncmp_safe(");
	print_string_or_null(s1);
	printf(", ");
	print_string_or_null(s2);
	printf(", %zu) ==\n", n);

	status = ft_strncmp_safe(s1, s2, n, &result);
	printf("Return: %d | cmp_result: %d\n", status, result);
	printf("\n-----------------------------\n\n");
}

int main(void)
{
	printf("\nFT_STRCMP_SAFE TESTS :\n\n\n\n\n");
	
	// Tests pour ft_strcmp_safe
	test_strcmp("Hello", "Hello");
	test_strcmp("Hello", "HellO");
	test_strcmp("Apple", "Banana");
	test_strcmp("abc", "abcd");
	test_strcmp(NULL, "Hello");
	test_strcmp("Hello", NULL);
	test_strcmp(NULL, NULL);
	test_strcmp("", "");
	test_strcmp("", "a");
	test_strcmp("a", "");
	
	printf("\n\n\n\nFT_STRNCMP_SAFE TESTS :\n\n\n\n\n\n");
	
	// Tests pour ft_strncmp_safe
	test_strncmp("Hello", "Hello", 5);
	test_strncmp("Hello", "HellO", 5);
	test_strncmp("Hello", "HellO", 4);
	test_strncmp("abc", "abcd", 3);
	test_strncmp("abc", "abcd", 5);
	test_strncmp("short", "shorter", 10);
	test_strncmp("shorter", "short", 10);
	test_strncmp("", "", 3);
	test_strncmp("", "a", 1);
	test_strncmp("a", "", 1);
	test_strncmp(NULL, "Test", 4);
	test_strncmp("Test", NULL, 4);
	test_strncmp(NULL, NULL, 4);
	test_strncmp("Hello", "Hello", 0);
	test_strncmp("Different", "Difference", 9);
	test_strncmp("SamePrefix", "SamePrefixPlus", 10);
	test_strncmp("SamePrefixPlus", "SamePrefix", 10);

	return (0);
}
*/
