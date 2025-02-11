/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 20:13:40 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/15 20:16:09 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "libft.h"

static unsigned int	ft_count_words(char const *str, char c)
{
	unsigned int	count;
	unsigned int	is_word;
	char			*s;

	if (!str)
		return (0);
	s = (char *)str - 1;
	count = 0;
	is_word = 0;
	while (*(++s))
	{
		if (*s != c && is_word == 0)
		{
			count++;
			is_word = 1;
		}
		if (*s == c)
			is_word = 0;
	}
	return (count);
}

static unsigned int	ft_len_word(char const *str, char c)
{
	unsigned int	len;

	len = 0;
	while (*str && *str != c)
	{
		len++;
		str++;
	}
	return (len);
}

static void	ft_free_all(char **tab, unsigned int index)
{
	while (index > 0)
	{
		index--;
		free(tab[index]);
	}
	free(tab);
}

static void	ft_alloc_write(char const *s, char c, unsigned int nb, char **tab)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (i < nb)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			tab[i] = malloc(sizeof(char) * (ft_len_word(s, c) + 1));
			if (!tab[i])
			{
				ft_free_all(tab, i);
				return ;
			}
			j = 0;
			while (*s && *s != c)
				tab[i][j++] = *(s++);
			tab[i][j] = '\0';
			i++;
		}
	}
	tab[i] = NULL;
}

char	**ft_split(char const *s, char c)
{
	unsigned int	nb_word;
	char			**tab;

	if (!s)
		return (NULL);
	nb_word = ft_count_words(s, c);
	tab = malloc(sizeof(char *) * (nb_word + 1));
	if (!tab)
		return (NULL);
	ft_alloc_write(s, c, nb_word, tab);
	return (tab);
}
/*
#include <stdio.h>

int	main(int argc, char **argv)
{
	char	*str;
	char	sep;
	int		i;
	char	**tab;

	(void)argc;
	i = 0;
	str = argv[1];
	sep = *argv[2];
	str = "Bonjour je m'appelle Matisse.";
	sep = " ";
	tab = ft_split(str, sep);
	while (tab[i] != NULL)
	{
		printf("'%s'\n", tab[i]);
		i++;
	}
	return (0);
}
*/
// 1. compter le nombre de mots
// 2. trouver longueur de chaque mot
// 3. malloc tableau de tableaux (avec longueur des mots ?)
// 4. fonction 'free_all' en cas d'erreur d'allocation
