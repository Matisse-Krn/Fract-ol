/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fcalloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 06:30:34 by mkerrien          #+#    #+#             */
/*   Updated: 2025/04/02 06:38:26 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * ft_fcalloc - Frees and reallocates memory safely.
 *
 * This helper function ensures that a previously allocated pointer is safely
 * freed before being reallocated using ft_calloc(). It prevents memory leaks 
 * by releasing the old memory block pointed to by *ptr before assigning it
 * a newly allocated block of (nmemb * size) bytes, zero-initialized.
 *
 * @param nmemb  Number of elements to allocate.
 * @param size   Size of each element.
 * @param ptr    Double pointer to the memory block to (re)allocate.
 *
 * Example :
 *
 * # size_t	nmemb;
 * # size_t	size;
 * # char	*example;
 * #
 * # ft_fcalloc(nmemb, size, (void **)&line);
*/

void	ft_fcalloc(size_t nmemb, size_t size, void **ptr)
{
	if (*ptr)
	{
		free(*ptr);
		*ptr = NULL;
	}
	*ptr = ft_calloc(nmemb, size);
}
