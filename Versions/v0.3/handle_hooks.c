/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:38:32 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/04 15:12:28 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fractol.h"

static void	apply_zoom(t_fractal *fractal, int x, int y, double factor)
{
	fractal->shift_x += scale_map(x, -fractal->zoom_rate, fractal->zoom_rate,
			fractal->img.width) - scale_map(x, -fractal->zoom_rate * factor,
			fractal->zoom_rate * factor, fractal->img.width);
	fractal->shift_y += scale_map(y, fractal->zoom_rate, -fractal->zoom_rate,
			fractal->img.height) - scale_map(y, fractal->zoom_rate * factor,
			-fractal->zoom_rate * factor, fractal->img.height);
	fractal->zoom_rate *= factor;
}

/*
	* XK_Escape = ESC || XK_Left = left arrow || XK_Down = down arrow,...
*/
int	handle_key(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		handle_exit(fractal);
	else if (keysym == XK_Left)
		fractal->shift_x -= 0.25 * fractal->zoom_rate;
	else if (keysym == XK_Right)
		fractal->shift_x += 0.25 * fractal->zoom_rate;
	else if (keysym == XK_Up)
		fractal->shift_y += 0.25 * fractal->zoom_rate;
	else if (keysym == XK_Down)
		fractal->shift_y -= 0.25 * fractal->zoom_rate;
	else if (keysym == XK_KP_Add)
		fractal->max_iterations += fractal->tick_iterations;
	else if (keysym == XK_KP_Subtract)
	{
		if (fractal->max_iterations - fractal->tick_iterations > 0)
			fractal->max_iterations -= fractal->tick_iterations;
	}	
//	printf("%d\n", keysym);
	fractal_rendering(fractal);
	return (0);
}

/*
	* Exit properly when clicking on the 'x' window button
*/
int	handle_exit(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
	mlx_destroy_display(fractal->mlx_ptr);
	free(fractal->mlx_ptr);
	exit(EXIT_SUCCESS);
	return (0);
}

/*
	* Mouse-wheel zoom control
		* 'Button5' = Scroll down	//	Normal dezoom
		* 'Button4' = Scroll up		//	Normal zoom
		* 'Button3' = Right click	//	Big dezoom
		* 'Button1' = Left click	//	Big zoom
*/
int	handle_mouse(int button, int x, int y, t_fractal *fractal)
{
	if (button == Button5)
		apply_zoom(fractal, x, y, 1.3);
	else if (button == Button4)
		apply_zoom(fractal, x, y, 0.7);
	else if (button == Button3)
		apply_zoom(fractal, x, y, 1.8);
	else if (button == Button1)
		apply_zoom(fractal, x, y, 0.2);
	else
		return (0);
	fractal_rendering(fractal);
	return (0);
//	printf("Button = %d\n", button);
//	printf("x = %d\ny = %d\n\n", x, y);
	fractal_rendering(fractal);
	return (0);
}
