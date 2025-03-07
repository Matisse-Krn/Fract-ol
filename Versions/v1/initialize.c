/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 03:54:18 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/09 21:47:27 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Initializes the default position, zoom settings, and complex plane shift
	values.
 * Adjusts initial offsets based on the selected fractal type.
 * 
 * @param fractal A pointer to the fractal structure to configure
	position settings.
 * 
 * Variables:
 * - shift_x, shift_y: Horizontal and vertical shifts in the complex plane.
 *   The Mandelbrot set is adjusted leftward by default (-0.6).
 * - zoom_rate: Initial zoom factor applied to the fractal rendering.
 * - init_shift_x, init_shift_y: Stores the initial shift values to allow
		reset functionality.
 * - init_zoom_rate: Stores the initial zoom factor to allow reset functionality.
 * - last_pos: Stores the last recorded cursor position (initialized as an
		empty string).
 * - init_c_real, init_c_imag: Stores the initial complex parameters for
		Julia fractals.
 *   If not already set, they are initialized to empty strings.
*/
static void	position_init(t_fractal *fractal)
{
	fractal->shift_x = 0;
	if (!ft_strcmp(fractal->name, "mandelbrot"))
		fractal->shift_x = -0.6;
	fractal->shift_y = 0;
	fractal->zoom_rate = 1.6;
	fractal->init_shift_x = fractal->shift_x;
	fractal->init_shift_y = fractal->shift_y;
	fractal->init_zoom_rate = fractal->zoom_rate;
	fractal->last_pos = "";
	if (!fractal->init_c_real && !fractal->init_c_imag)
	{
		fractal->init_c_real = "";
		fractal->init_c_imag = "";
	}
}

/*
 * Initializes all necessary fields in the fractal structure.
 * Sets default values for image dimensions, iteration limits, color settings,
	contrast, and other essential parameters.
 * 
 * @param fractal A pointer to the fractal structure to initialize.
 * 
 * Variables:
 * - img.height, img.width: Dimensions of the rendering image in pixels.
 * - escape_value: Escape threshold used to determine if a point diverges.
		Typically set to 2^2 for stability in fractal calculations.
 * - max_iterations: Maximum number of iterations per pixel before considering
		it non-divergent.
 * - tick_iterations: Increment value for iteration changes when adjusting
		detail levels.
 * - color: Default color value (used in certain rendering modes).
 * - init_color_min, init_color_max: Initial color range for gradient-based
		coloring.
 * - color_min, color_max: Current active color range, modified by user
		interactions.
 * - color_mode: Character representing the current color mode
		('N' for normal, etc.).
 * - contrast_exponent: Value controlling contrast intensity in coloring
		calculations.
 * - psy: Character controlling psychedelic color mode ('N' for normal, etc.).
*/
void	data_init(t_fractal *fractal)
{
	ft_putstr_fd("Initialize all necessary data...\n", 1);
	fractal->img.height = 960;
	fractal->img.width = 960;
	fractal->escape_value = pow(2, 2);
	fractal->max_iterations = 100;
	fractal->tick_iterations = 10;
	fractal->color = 0x000000;
	fractal->init_color_min = 0x000000;
	fractal->init_color_max = 0xFFFFFF;
	fractal->color_min = fractal->init_color_min;
	fractal->color_max = fractal->init_color_max;
	fractal->color_mode = 'N';
	fractal->contrast_exponent = 0.5;
	fractal->psy = 'N';
	position_init(fractal);
	data_init_sierpinski(fractal);
}

/*
 * Sets up event hooks for handling user input such as keyboard and
	mouse actions.
 * Configures event listeners differently for the Sierpinski Carpet fractal.
 * 
 * @param fractal A pointer to the fractal structure whose events are being
		initialized.
 * 
 * Events:
 * - DestroyNotify: Handles window close event (calls handle_exit).
 * - KeyPress: Captures keyboard inputs (calls handle_key).
 * - MotionNotify: Captures mouse movement (calls handle_mouse_move).
 * - ButtonPress: Captures mouse clicks (calls handle_mouse).
*/
void	initialize_events(t_fractal *fractal)
{
	if (!ft_strcmp(fractal->name, "sierpinski"))
	{
		initialize_events_sierpinski(fractal);
		return ;
	}
	mlx_hook(fractal->win_ptr,
		DestroyNotify,
		StructureNotifyMask,
		handle_exit, fractal);
	mlx_hook(fractal->win_ptr,
		KeyPress,
		KeyPressMask,
		handle_key, fractal);
	mlx_hook(fractal->win_ptr,
		MotionNotify,
		PointerMotionMask,
		handle_mouse_move, fractal);
	mlx_hook(fractal->win_ptr,
		ButtonPress,
		ButtonPressMask,
		handle_mouse, fractal);
}

/*
 * Creates and initializes the MiniLibX window for rendering the fractal.
 * Allocates memory and ensures proper resource handling in case of allocation
	failure.
 * 
 * @param fractal A pointer to the fractal structure used to manage the display.
 * 
 * Variables:
 * - mlx_ptr: MiniLibX connection instance, initialized via mlx_init().
 * - win_ptr: MiniLibX window instance, created with mlx_new_window().
*/
void	initialize_window(t_fractal *fractal)
{
	char	*name_formatted;

	fractal->mlx_ptr = mlx_init();
	if (!fractal->mlx_ptr)
		malloc_error();
	name_formatted = get_window_name(fractal);
	if (!name_formatted)
		malloc_error();
	fractal->win_ptr = mlx_new_window(fractal->mlx_ptr, fractal->img.width,
			fractal->img.height, name_formatted);
	free(name_formatted);
	if (!fractal->win_ptr)
	{
		mlx_destroy_display(fractal->mlx_ptr);
		free(fractal->mlx_ptr);
		malloc_error();
	}
}

/*
 * Creates an image buffer for rendering the fractal within the MiniLibX window.
 * Allocates memory for image storage and retrieves the pixel data address.
 * 
 * @param fractal A pointer to the fractal structure that will store the
		image details.
 * 
 * Variables:
 * - img.img_ptr: Pointer to the MiniLibX image instance.
 * - img.px_ptr: Pointer to the raw pixel data within the image buffer.
 * - img.bits_per_pixel: Number of bits used per pixel (determines color depth).
 * - img.line_length: Number of bytes per row of pixels (accounts for padding).
 * - img.endian: Endianness of the pixel format (determines byte order).
*/
void	initialize_image(t_fractal *fractal)
{
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_ptr, fractal->img.width,
			fractal->img.height);
	if (!fractal->img.img_ptr)
	{
		mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
		mlx_destroy_display(fractal->mlx_ptr);
		free(fractal->mlx_ptr);
		malloc_error();
	}
	fractal->img.px_ptr = mlx_get_data_addr(fractal->img.img_ptr,
			&fractal->img.bits_per_pixel, &fractal->img.line_length,
			&fractal->img.endian);
	if (!fractal->img.px_ptr)
	{
		mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
		mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
		mlx_destroy_display(fractal->mlx_ptr);
		free(fractal->mlx_ptr);
		malloc_error();
	}
}
