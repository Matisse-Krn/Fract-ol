#include "fractol.h"

/**
 * @brief  Move the fractal view in a given direction.
 *
 * Adjusts the horizontal or vertical shift of the fractal view based
 * on the specified direction, moving by 25% of the current visible
 * range. Triggers a full re-render of the fractal after movement.
 *
 * @param  direction  Movement direction: 'L' (left), 'R' (right),
 *                    'U' (up), or 'D' (down).
 * @param  f          Pointer to the fractal context (`t_fractal`)
 *                    containing zoom, aspect ratio, and shift values.
 * @return None.
 *
 * @note   The displacement amount scales with the current zoom level
 *         and aspect ratio.
 * @pre    `f` must be initialized with valid rendering parameters.
 * @post   The view is shifted and the fractal is re-rendered.
 */
void	displacement(char direction, t_fractal *f)
{
	double	move_amount_x;
	double	move_amount_y;

	move_amount_x = (1.6 / f->zoom_rate) * f->aspect_ratio * 0.25;
	move_amount_y = (1.6 / f->zoom_rate) * 0.25;
	if (direction == 'L')
		f->shift_x -= move_amount_x;
	else if (direction == 'R')
		f->shift_x += move_amount_x;
	else if (direction == 'U')
		f->shift_y += move_amount_y;
	else if (direction == 'D')
		f->shift_y -= move_amount_y;
	fractal_rendering(f);
}

/**
 * @brief  Apply zoom to the fractal view centered on a pixel.
 *
 * Changes the zoom level of the fractal by a given factor, adjusting
 * the position so that the specified screen coordinates remain centered
 * in the view after zooming. Triggers a full re-render after updating.
 *
 * @param  f       Pointer to the fractal context (`t_fractal`) containing
 *                 zoom, aspect ratio, and shift values.
 * @param  x       X coordinate of the zoom center (in pixels).
 * @param  y       Y coordinate of the zoom center (in pixels).
 * @param  factor  Multiplicative zoom factor (> 1.0 for zoom-in,
 *                 < 1.0 for zoom-out).
 * @return None.
 *
 * @note   Uses `scale_map()` to translate screen coordinates to fractal
 *         plane coordinates for precise zoom centering.
 * @pre    `f` must be initialized with valid rendering parameters.
 * @post   The zoom level and position are updated, and the fractal
 *		   is re-rendered.
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

/**
 * @brief  Increase or decrease the maximum iteration count.
 *
 * Adjusts the `max_iterations` value by `tick_iterations`, either
 * increasing or decreasing it depending on the given sign. Triggers
 * a re-render of the fractal after updating.
 *
 * @param  sign     '+' to increase iterations, '-' to decrease.
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   The minimum allowed value for `max_iterations` is equal
 *         to `tick_iterations`.
 * @pre    `fractal` must be initialized with valid rendering parameters.
 * @post   `max_iterations` is updated and the fractal is re-rendered.
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

/**
 * @brief  Reset the fractal view to its initial parameters.
 *
 * Restores the shift and zoom level to their initial values stored
 * in the fractal context. Triggers a re-render after resetting.
 *
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   This function does not reset colors or iteration count,
 *         only position and zoom parameters.
 * @pre    `fractal` must contain valid `init_shift_x`, `init_shift_y`,
 *         and `init_zoom_rate` values.
 * @post   The view is restored to its initial position and zoom.
 */
void	reset_view(t_fractal *fractal)
{
	fractal->shift_x = fractal->init_shift_x;
	fractal->shift_y = fractal->init_shift_y;
	fractal->zoom_rate = fractal->init_zoom_rate;
	ft_putstr_fd("Reset view...\n", 1);
	fractal_rendering(fractal);
}
