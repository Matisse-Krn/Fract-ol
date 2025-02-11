/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:52:56 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/09 03:23:05 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

//	fractal->shift_x -= 0.25 * fractal->zoom_rate;
void	displacement(char direction, t_fractal *fractal)
{
	if (direction == 'L')
	{
		ft_putstr_fd("Going left\n", 1);
		fractal->shift_x -= 0.25 * fractal->zoom_rate;
	}
	else if (direction == 'R')
	{
		ft_putstr_fd("Going right\n", 1);
		fractal->shift_x += 0.25 * fractal->zoom_rate;
	}
	else if (direction == 'U')
	{
		ft_putstr_fd("Going up\n", 1);
		fractal->shift_y += 0.25 * fractal->zoom_rate;
	}
	else if (direction == 'D')
	{
		ft_putstr_fd("Going down\n", 1);
		fractal->shift_y -= 0.25 * fractal->zoom_rate;
	}
	fractal_rendering(fractal);
}

void	apply_zoom(t_fractal *fractal, int x, int y, double factor)
{
	fractal->shift_x += scale_map(x, -fractal->zoom_rate, fractal->zoom_rate,
			fractal->img.width) - scale_map(x, -fractal->zoom_rate * factor,
			fractal->zoom_rate * factor, fractal->img.width);
	fractal->shift_y += scale_map(y, fractal->zoom_rate, -fractal->zoom_rate,
			fractal->img.height) - scale_map(y, fractal->zoom_rate * factor,
			-fractal->zoom_rate * factor, fractal->img.height);
	fractal->zoom_rate *= factor;
	fractal_rendering(fractal);
}

void	change_max_iterations(char sign, t_fractal *fractal)
{
	ft_printf("Changing 'max_iterations' : [%d ->", fractal->max_iterations);
	if (sign == '+')
		fractal->max_iterations += fractal->tick_iterations;
	else if (sign == '-' && fractal->max_iterations > fractal->tick_iterations)
		fractal->max_iterations -= fractal->tick_iterations;
	else
	{
		ft_printf(" %d]\n", fractal->max_iterations);
		return ;
	}
	ft_printf(" %d]\n", fractal->max_iterations);
	fractal_rendering(fractal);
}

void	reset_view(t_fractal *fractal)
{
	fractal->shift_x = fractal->init_shift_x;
	fractal->shift_y = fractal->init_shift_y;
	fractal->zoom_rate = fractal->init_zoom_rate;
	ft_putstr_fd("Reset view...\n", 1);
	fractal_rendering(fractal);
}
