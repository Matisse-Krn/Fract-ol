/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/03 21:33:51 by mkerrien          #+#    #+#             */
/*   Updated: 2025/08/03 23:47:04 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Copies the null-terminated string `src` into `dst`.
 * The destination buffer must be large enough to hold the source string.
 *
 * @param dst A pointer to the destination buffer.
 * @param src A pointer to the null-terminated source string.
 * @return Returns `dst`.
 */
char	*ft_strcpy(char *dst, const char *src)
{
	size_t	i;

	if (!src)
		return (NULL);
	i = -1;
	while (src[++i])
		dst[i] = src[i];
	dst[i] = '\0';
	return (dst);
}
