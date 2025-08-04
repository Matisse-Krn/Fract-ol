/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 12:22:59 by mkerrien          #+#    #+#             */
/*   Updated: 2024/12/28 12:23:02 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Renvoie l'index de 'c' si il est present dans 'str', sinon renvoie -1
static int	is_c_in_str(int c, char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == c)
			return (i);
	}
	if (c == '\0')
		return (i);
	return (-1);
}

static void	*read_joinstash_and_find_nl(int *fd, int *i, char **stash)
{
	int		ret_read;
	char	*buffer;

	*i = -1;
	buffer = ft_calloc(GNL_BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (NULL);
	ret_read = 1;
	while (ret_read != 0)
	{
		ret_read = read(*fd, buffer, GNL_BUFFER_SIZE);
		if (ret_read < 0)
			return (free(*stash), *stash = NULL, free(buffer), buffer = NULL);
		buffer[ret_read] = '\0';
		*stash = ft_strfjoin(*stash, buffer);
		if (!(*stash))
			return (free(buffer), buffer = NULL);
		*i = is_c_in_str('\n', *stash);
		if (*i != -1 || ret_read == 0)
			break ;
	}
	return (free(buffer), buffer = NULL);
}

static int	first_verifications_gnl(int fd, int end, char **stash)
{
	if (fd < 0 || fd >= 1024 || GNL_BUFFER_SIZE <= 0)
	{
		if (stash[fd])
		{
			ft_free_strs(&stash[fd]);
			stash[fd] = NULL;
		}
		return (1);
	}
	if (end)
		return (ft_free_strs(&stash[fd]), 1);
	if (!stash[fd])
	{
		stash[fd] = ft_calloc(GNL_BUFFER_SIZE + 1, sizeof(char));
		if (!stash[fd])
			return (1);
	}
	return (0);
}

char	*get_next_line(int fd, int end)
{
	static char	*stash[1024];
	char		*line;
	int			i;

	if (first_verifications_gnl(fd, end, stash))
		return (NULL);
	if (read_joinstash_and_find_nl(&fd, &i, &stash[fd]), !stash[fd])
		return (stash[fd] = NULL);
	if (i != -1)
		line = ft_substr(stash[fd], 0, i + 1);
	else
		line = ft_substr(stash[fd], 0, ft_strlen(stash[fd]));
	if (!line)
		return (free(stash[fd]), stash[fd] = NULL);
	if (i != -1)
		ft_memmove(stash[fd], stash[fd] + i +1, ft_strlen(stash[fd]) - (i + 1));
	else
		stash[fd][0] = '\0';
	return (stash[fd][ft_strlen(stash[fd]) - (i + 1)] = '\0', line);
}

/*
#include <fcntl.h>
#include <stdio.h>

int	main(int argc, char **argv)
{
	int		fd;
	int		i;
	char	*ret_val;

	if (argc < 2)
	{
		printf("ERROR. Usage : ./<a.out> <your_file1_name> \
<your_file2_name> ...\n");
		return (1);
	}
	i = 1;
	while (i < argc)
	{
		fd = open(argv[i], O_RDONLY);
		if (fd < 0)
		{
			printf("ERROR OPENING FILE %s\n", argv[i]);
			return (1);
		}
		printf("----------\nfd = %d || file = %s\n----------\n", fd, argv[i]);
		ret_val = "";
		while (ret_val != NULL)
		{
			ret_val = get_next_line(fd);
			printf("%s", ret_val);
			free(ret_val);
		}
		close(fd);
		i++;
	}
	return (0);
}*/
/*
1- Verifier que fd >= 0, que GNL_BUFFER_SIZE est positif, et que read(fd, 0, 0) \
retourne une valeur >= 0;
2- Assigner '\0' comme dernier element de buffer[];
3- Calloc 'stash' + protection;
4- 


|| LOGIQUE DU PROGRAMME ||

A - Lire via fd et ecrire dans 'buffer' (read)
B - Transferer contenu de 'buffer' a la suite de 'stash' (ft_strjoin)
C - Verifier si '\n' present dans 'stash'
	C.1 - Si '\n' present dans 'stash':
			- Extraire contenu de 'stash' jusqu'au '\n' (inclu) vers
			  'line' (ft_substr)
			?- Placer '\0' a la fin de 'line' ?
			- Dans 'stash', deplacer contenu apres le '\n' vers
			  son debut (ft_memmove)
			- Replacer '\0' apres ces caracteres dans 'stash'
			- Retourner ligne complete ('line')
	C.2 - Si '\n' absent de 'stash' :
			- Verifier si le dernier appel de read a lu quelquechose ou non \
			(ret_read == 0)
				- Si ret_read == 0 :
					- Retourner 'line' tel quel
				- Si ret_read != 0 :
					- Verifier si '\0' present dans 'buffer'
						- Si '\0' present dans 'buffer' :
							- Retourner 'line' tel quel
						- Si '\0' absent de 'buffer'
							- Recommencer depuis l'etape A (read)

				

Liste des fonctions utilisees : ft_substr, ft_strjoin, ft_memmove, ft_strlen, \
								ft_calloc
*/
