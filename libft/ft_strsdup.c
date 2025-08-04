/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 02:52:35 by mkerrien          #+#    #+#             */
/*   Updated: 2025/03/27 04:04:57 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_strsdup(const char **tab)
{
	char	**dup;
	int		i;
	int		j;

	if (!tab || !(*tab))
		return (NULL);
	i = -1;
	while (tab[++i])
		;
	dup = ft_calloc(i + 1, sizeof(char *));
	if (!dup)
		return (NULL);
	j = -1;
	while (++j < i && tab[j])
	{
		dup[j] = ft_strdup(tab[j]);
		if (!dup[j])
			return (ft_free_fullstrs(&dup), NULL);
	}
	return (dup);
}
/*
int	main(void)
{
	char  **tab;
	char  **dup;
	int	  i;

	tab = ft_calloc(3, sizeof(char *));
	if (!tab)
		return (1);
	tab[0] = ft_strdup("Hello");
	tab[1] = ft_strdup("world !");
	dup = ft_strsdup((const char **)tab);
	if (!dup)
		return (1);
	i = -1;
	while (dup[++i])
		ft_printf("dup[%d] = '%s'\n", i, dup[i]);
	ft_printf("dup[%d] = '%s'\n", i, dup[i]);
	ft_free_strs(tab);
	ft_free_strs(dup);
	return (0);
}
*/
