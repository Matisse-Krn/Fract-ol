/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_fullstrs.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 03:10:32 by mkerrien          #+#    #+#             */
/*   Updated: 2025/03/27 04:00:14 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_fullstrs(char ***tab)
{
	int	i;

	if (!tab || !(*tab))
		return ;
	i = -1;
	while ((*tab)[++i])
	{
		free((*tab)[i]);
		(*tab)[i] = NULL;
	}
	free(*tab);
	*tab = NULL;
}
