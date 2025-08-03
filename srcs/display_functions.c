#include "fractol.h"

void	displacement(char direction, t_fractal *fractal)
{
	double	aspect_ratio;
	double	x_range;

	aspect_ratio = (double)fractal->img.width / (double)fractal->img.height;
	x_range = fractal->zoom_rate * aspect_ratio;
	if (direction == 'L')
	{
		ft_putstr_fd("Going left\n", 1);
		fractal->shift_x -= 0.25 * x_range;
	}
	else if (direction == 'R')
	{
		ft_putstr_fd("Going right\n", 1);
		fractal->shift_x += 0.25 * x_range;
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

/*
 * Applies zooming to the fractal by modifying the zoom rate
	and adjusting the shift values to center the zoom at the mouse cursor.
 * 
 * @param fractal A pointer to the fractal structure.
 * @param x The x-coordinate of the zoom center.
 * @param y The y-coordinate of the zoom center.
 * @param factor The zoom factor (>1 for zoom out, <1 for zoom in).
*/
void	apply_zoom(t_fractal *fractal, int x, int y, double factor)
{
	double	aspect_ratio;
	double	x_range;

	aspect_ratio = (double)fractal->img.width / (double)fractal->img.height;
	x_range = fractal->zoom_rate * aspect_ratio;
	fractal->shift_x += scale_map(x, -x_range, x_range,
			fractal->img.width) - scale_map(x, -x_range * factor,
			x_range * factor, fractal->img.width);
	fractal->shift_y += scale_map(y, fractal->zoom_rate, -fractal->zoom_rate,
			fractal->img.height) - scale_map(y, fractal->zoom_rate * factor,
			-fractal->zoom_rate * factor, fractal->img.height);
	fractal->zoom_rate *= factor;
	fractal_rendering(fractal);
}

/*
 * Increases or decreases the maximum number of iterations used
	for fractal rendering. The step size is defined by tick_iterations.
 * 
 * @param sign The character indicating increase ('+') or decrease ('-').
 * @param fractal A pointer to the fractal structure.
 * 
 * Constraints:
	- Cannot decrease below tick_iterations.
*/
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

/*
 * Resets the fractal view to its initial position and zoom level.
 * Restores shift_x, shift_y, and zoom_rate to their original values.
 * 
 * @param fractal A pointer to the fractal structure.
*/
void	reset_view(t_fractal *fractal)
{
	fractal->shift_x = fractal->init_shift_x;
	fractal->shift_y = fractal->init_shift_y;
	fractal->zoom_rate = fractal->init_zoom_rate;
	ft_putstr_fd("Reset view...\n", 1);
	fractal_rendering(fractal);
}
