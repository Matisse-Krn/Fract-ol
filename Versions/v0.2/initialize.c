/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 03:54:18 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/04 15:18:10 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fractol.h"

static void	malloc_error(void)
{
	perror("Malloc ERROR...\n");
	exit(1);
}

void	data_init(t_fractal *fractal)
{
	fractal->img.height = 1010;
	fractal->img.width = 1010;
//	fractal->img.ratio = fractal->img.width / fractal->img.height;
	fractal->escape_value = pow(2, 2);
	fractal->max_iterations = 500;
	fractal->shift_x = 0;
	fractal->shift_y = 0;
	return ;
}

void	initialize_events(t_fractal *fractal)
{
	mlx_hook(fractal->win_ptr,
		KeyPress,
		KeyPressMask,
		handle_key,
		fractal);
/*
	mlx_hook(fractal->win_ptr,
		ButtonPress,
		ButtonPressMask,
		handle_mouse,		// TODO
		fractal);
*/
	mlx_hook(fractal->win_ptr,
		DestroyNotify,
		StructureNotifyMask,
		handle_exit,
		fractal);
}

void	initialize_window(t_fractal *fractal)
{
	fractal->mlx_ptr = mlx_init();
	if (!fractal->mlx_ptr)
		malloc_error();
	fractal->win_ptr = mlx_new_window(fractal->mlx_ptr, fractal->img.width,
			fractal->img.height, fractal->name);
	if (!fractal->win_ptr)
	{
		mlx_destroy_display(fractal->mlx_ptr);
		free(fractal->mlx_ptr);
		malloc_error();
	}
}

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
	if (!fractal->img.px_ptr)  // if non-necessaire ?
	{
		mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
		mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
		mlx_destroy_display(fractal->mlx_ptr);
		free(fractal->mlx_ptr);
		malloc_error();
	}
}
