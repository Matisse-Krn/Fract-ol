/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 18:52:56 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/07 19:47:53 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

//	fractal->shift_x -= 0.25 * fractal->zoom_rate;
void	displacement(char direction, t_fractal *fractal)
{
	if (direction == 'L')
		fractal->shift_x -= 0.25 * fractal->zoom_rate;
	else if (direction == 'R')
		fractal->shift_x += 0.25 * fractal->zoom_rate;
	else if (direction == 'U')
		fractal->shift_y += 0.25 * fractal->zoom_rate;
	else if (direction == 'D')
		fractal->shift_y -= 0.25 * fractal->zoom_rate;
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
	printf("Changing 'max_iterations' from %d ", fractal->max_iterations);
	if (sign == '+')
		fractal->max_iterations += fractal->tick_iterations;
	else if (sign == '-' && fractal->max_iterations > fractal->tick_iterations)
		fractal->max_iterations -= fractal->tick_iterations;
	else
		return ;
	printf("to %d\n", fractal->max_iterations);
	fractal_rendering(fractal);
}
