#include "fractol.h"

static void	vertical_displacement(double move_amount_y,
								char direction, t_fractal *f)
{
	if (direction == 'U')
	{
		ft_putstr_fd("Going up\n", 1);
		f->shift_y += move_amount_y;
	}
	else if (direction == 'D')
	{
		ft_putstr_fd("Going down\n", 1);
		f->shift_y -= move_amount_y;
	}
}

void	displacement(char direction, t_fractal *f)
{
	double	move_amount_x;
	double	move_amount_y;

	move_amount_x = (1.6 / f->zoom_rate) * f->aspect_ratio * 0.25;
	move_amount_y = (1.6 / f->zoom_rate) * 0.25;
	if (direction == 'L')
	{
		ft_putstr_fd("Going left\n", 1);
		f->shift_x -= move_amount_x;
	}
	else if (direction == 'R')
	{
		ft_putstr_fd("Going right\n", 1);
		f->shift_x += move_amount_x;
	}
	vertical_displacement(move_amount_y, direction, f);
	fractal_rendering(f);
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
void	apply_zoom(t_fractal *f, int x, int y, double factor)
{
	double	old_zoom;
	double	new_zoom;
	double	x_range_old;
	double	x_range_new;

	old_zoom = f->zoom_rate;
	new_zoom = f->zoom_rate * factor;
	x_range_old = (1.6 / old_zoom) * f->aspect_ratio;
	x_range_new = (1.6 / new_zoom) * f->aspect_ratio;
	f->shift_x += scale_map(x, -x_range_old, x_range_old, f->img.width)
		- scale_map(x, -x_range_new, x_range_new, f->img.width);
	f->shift_y += scale_map(y, 1.6 / old_zoom, -1.6 / old_zoom, f->img.height)
		- scale_map(y, 1.6 / new_zoom, -1.6 / new_zoom, f->img.height);
	f->zoom_rate = new_zoom;
	fractal_rendering(f);
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
