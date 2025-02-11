/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 03:43:15 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/06 04:54:32 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

static char	*if_malloc_error(char *s)
{
	if (!s)
		malloc_error();
	return (s);
}

static char	*str_append(char *original, char *to_add)
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

char	*get_window_name(t_fractal *fractal)
{
	char	*name;
	char	*width;
	char	*height;

	name = ft_first_l_in_up(fractal->name);
	if_malloc_error(name);
	name = str_append(name, " - ");
	if_malloc_error(name);
	width = ft_itoa(fractal->img.width);
	if_malloc_error(width);
	name = str_append(name, width);
	free(width);
	if_malloc_error(name);
	name = str_append(name, "*");
	if_malloc_error(name);
	height = ft_itoa(fractal->img.height);
	if_malloc_error(height);
	name = str_append(name, height);
	free(height);
	return (if_malloc_error(name));
}

void	put_strings(t_fractal *fractal)
{
	char	*max_iterations;

	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 5, 10, 0xFFFFFF,
		"Max iterations : ");
	max_iterations = ft_itoa(fractal->max_iterations);
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr,
		105, 10, 0xFFFFFF, max_iterations);
	free (max_iterations);
}
