/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 05:06:36 by mkerrien          #+#    #+#             */
/*   Updated: 2025/03/09 05:10:36 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*'ft_strjoin()' classique, mais qui 'free(s1)' avant de retourner 's3'*/
char	*ft_strfjoin(char *s1, char *s2)
{
	char	*s3;
	size_t	l_s1;
	size_t	l_s2;
	size_t	i;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		l_s1 = 0;
	else
		l_s1 = ft_strlen(s1);
	l_s2 = ft_strlen(s2);
	s3 = ft_calloc((l_s1 + l_s2 + 1), sizeof(char));
	if (!s3)
		return (NULL);
	i = -1;
	while (++i < l_s1 && s1[i])
		s3[i] = s1[i];
	while (*s2)
		s3[l_s1++] = *s2++;
	s3[l_s1] = '\0';
	free(s1);
	s1 = NULL;
	return (s3);
}
