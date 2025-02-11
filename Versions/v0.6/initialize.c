/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 03:54:18 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/09 06:25:38 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fractol.h"

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
	* Initialize some necessary variables
		* img.height :		image's and window's height 
		* img.width :		image's and window's width 
		* escape_value :	value above which a point on the “graph” will 
							be considered as tending towards infinity.
		* max_iterations :	iterations number applied on each pixel
							(higher value will give better "definition",
		but will slow down execution)
		* tick_iterations :	value added or subtract to 'max_iterations'
							when pressing '+' or '-' keys
		* shift_x :			offset to "move" on the 'x' axis (horizontally)
		* shift_y :			offset to "move" on the 'y' axis (vertically)
		* zoom_rate :		zoom rate. Initially =2 to fit the
							Mandelbrot size needs
*/
void	data_init(t_fractal *fractal)
{
	ft_putstr_fd("Initialize all necessary data...\n", 1);
	fractal->img.height = 960;
	fractal->img.width = 960;
	fractal->escape_value = pow(2, 2);
	fractal->max_iterations = 1000;
	fractal->tick_iterations = 10;
	fractal->color = 0x000000;
	fractal->init_color_min = 0x000000;
	fractal->init_color_max = 0xFFFFFF;
	fractal->color_min = fractal->init_color_min;
	fractal->color_max = fractal->init_color_max;
	fractal->color_mode = 'N';
	fractal->contrast_exponent = 0.5;
	fractal->psy = 'N';
	fractal->depth = 4;
	if (fractal->img.width > fractal->img.height)
		fractal->size = fractal->img.height;
	else
		fractal->size = fractal->img.width;
	ft_printf("Size = %d\n", fractal->size);
	position_init(fractal);
	return ;
}

/*
	* Monitor and capture few events and trigger related functions
		* First :	monitor the keyboard pressed key
		* Second :	monitor the mouse pressed (or scrolled) button
		* Third :	monitor the click on the 'x' window exit symbol
*/
void	initialize_events(t_fractal *fractal)
{
	mlx_hook(fractal->win_ptr,
		KeyPress,
		KeyPressMask,
		handle_key, fractal);
	mlx_hook(fractal->win_ptr,
		ButtonPress,
		ButtonPressMask,
		handle_mouse, fractal);
	mlx_hook(fractal->win_ptr,
		DestroyNotify,
		StructureNotifyMask,
		handle_exit, fractal);
	mlx_hook(fractal->win_ptr,
		MotionNotify,
		PointerMotionMask,
		handle_mouse_move, fractal);
}

/*
	* Initialize 'mlx_ptr' with 'mlx_init()'
	  and 'win_ptr' with 'mlx_new_window()'
		* Create and open new window, with previously created
		  variables (in 'data_init')
		* Protect the process of potential malloc error
		  and exit the programm properly if it so 
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
	* Initialize 'img.img_ptr' with 'mlx_new_image()'
		* Create an image for later editing
		  and assign the reference pointer to this image in 'img.img_ptr'
		* Assign the memory adress of the given image in 'px_ptr' 
		  and some other informations :
			* bits per pixel (in 'img.bits_per_pixel')
			* line length (in 'img.line_length')
			* endien (?) (in 'img.endian')
		* Protect the process of potential malloc error
		  and exit the programm properly if it so 
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
