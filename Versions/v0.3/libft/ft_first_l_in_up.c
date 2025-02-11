/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_first_l_in_up.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/05 18:36:55 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/05 19:32:11 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 *			Converts the first character of a string to uppercase, 
 *					  if it was previously lowercase.
 *
 *
 *		- Takes a string as input.
 *		- Duplicates the string using `ft_strdup`.
 *		- If the first character is a lowercase letter (between 'a' and 'z'),
 *		  it is converted to uppercase.
 *		- Returns the newly allocated string, whether modified or not.
 *
 *	Returns :
 *		- A new dynamically allocated string with the modification applied.
 *		- NULL if no string is passed (`NULL` input) or if `ft_strdup` fails.
 *
 *	Examples :
 *		- "hello world !"	->	"Hello world !"
 *		- "Hello"	->	"Hello"
 *		- ".hello"	->	".hello"
 *		- "123abc"	->	"123abc"	(first character is not a letter)
 *		- ""	->	""				(empty string remains unchanged)
 *		- NULL	->	NULL			(invalid input)
*/

char	*ft_first_l_in_up(char *s)
{
	char	*res;

	if (!s)
		return (NULL);
	res = ft_strdup(s);
	if (!res)
		return (NULL);
	if (res[0] >= 'a' && res[0] <= 'z')
		res[0] -= 32;
	return (res);
}
/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		i;
	char	*res;

	i = 0;
	if (argc > 1)
	{
		while (i < argc - 1)
		{
			res = ft_first_l_in_up(argv[++i]);
			printf("%s\n", res);
			free (res);
		}
	}
	else
		printf("Usage : ./a.out <arg1> <arg2> <arg3> ...\n");
}
*/
