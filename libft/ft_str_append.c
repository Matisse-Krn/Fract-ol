/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_append.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/04 01:47:38 by mkerrien          #+#    #+#             */
/*   Updated: 2025/08/04 01:48:01 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Concatenates two strings into a new allocated string.
 * Frees the original string and returns the newly created string.
 * 
 * @param original The base string to append to.
 * @param to_add The string to append at the end.
 * @return A newly allocated string containing the concatenation,
		or NULL if an input is NULL.
 * 
 * Memory:
	- The original string is freed after concatenation.
	- The caller is responsible for freeing the returned string.
*/
char	*str_append(char *original, char *to_add)
{
	char	*new_str;
	char	*tmp;

	if (!original || !to_add)
		return (NULL);
	tmp = original;
	new_str = ft_strjoin(tmp, to_add);
	free(tmp);
	return (new_str);
}
