/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 03:43:15 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/09 03:36:36 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

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

static void	get_julia_details(char **name, t_fractal *fractal)
{
	if (fractal->init_c_real[0] != '\0' && fractal->init_c_imag[0] != '\0')
	{
		*name = str_append(*name, fractal->init_c_real);
		if_malloc_error(*name);
		*name = str_append(*name, ",  ");
		if_malloc_error(*name);
		*name = str_append(*name, fractal->init_c_imag);
		if_malloc_error(*name);
		*name = str_append(*name, "    ");
		if_malloc_error(*name);
	}
}

char	*get_window_name(t_fractal *fractal)
{
	char	*name;
	char	*width;
	char	*height;

	name = ft_first_l_in_up(fractal->name);
	if_malloc_error(name);
	name = str_append(name, "    ");
	if_malloc_error(name);
	get_julia_details(&name, fractal);
	name = str_append(name, " -     ");
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

void	put_max_iterations(t_fractal *fractal)
{
	char	*max_iterations;

	max_iterations = ft_itoa(fractal->max_iterations);
	put_a_string(5, 10, "Max iterations : ", fractal);
	put_a_string(105, 10, max_iterations, fractal);
	free (max_iterations);
}

void	put_color_mode(t_fractal *fractal)
{
	put_a_string(5, 40, "Color :", fractal);
	if (fractal->color_mode == 'N')
		put_a_string(55, 40, "Normal", fractal);
	else if (fractal->color_mode == 'R')
		put_a_string(55, 40, "Red", fractal);
	else if (fractal->color_mode == 'G')
		put_a_string(55, 40, "Green", fractal);
	else if (fractal->color_mode == 'B')
		put_a_string(55, 40, "Blue", fractal);
	else if (fractal->color_mode == 'Y')
		put_a_string(55, 40, "Yellow", fractal);
	else if (fractal->color_mode == 'O')
		put_a_string(55, 40, "Orange", fractal);
	else if (fractal->color_mode == 'P')
		put_a_string(55, 40, "Pink", fractal);
	else if (fractal->color_mode == 'C')
		put_a_string(55, 40, "Cyan", fractal);
	put_a_string(100, 40, "||", fractal);
	if (fractal->psy == 'Y')
		put_a_string(120, 40, "Psych. : ON", fractal);
	else if (fractal->psy == 'N')
		put_a_string(120, 40, "Psych. : OFF", fractal);
}
