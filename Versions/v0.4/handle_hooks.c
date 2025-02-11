/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:38:32 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/07 13:45:37 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fractol.h"

/*
	* XK_Escape = ESC || XK_Left = left arrow || XK_Down = down arrow,...
*/
int	handle_key(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		handle_exit(fractal);
	else if (keysym == XK_p)
	{
		printf("P\n");
		change_color_mode(fractal, 'P');
	}
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
		if (fractal->max_iterations > fractal->tick_iterations > 0)
			fractal->max_iterations -= fractal->tick_iterations;
	}	
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
	if (fractal->last_pos && fractal->last_pos[0] != '\0')
	free(fractal->last_pos);
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
		apply_zoom(fractal, x, y, 1.2);
	else if (button == Button4)
		apply_zoom(fractal, x, y, 0.8);
	else if (button == Button3)
		apply_zoom(fractal, x, y, 1.8);
	else if (button == Button1)
		apply_zoom(fractal, x, y, 0.2);
	else
		return (0);
	fractal_rendering(fractal);
	return (0);
}

int	handle_mouse_move(int x, int y, t_fractal *fractal)
{
	char	*x_str;
	char	*y_str;
	char	*tmp;

	if (fractal->last_pos && fractal->last_pos[0] != '\0')
		free(fractal->last_pos);
	x_str = ft_itoa(x);
	if_malloc_error(x_str);
	y_str = ft_itoa(y);
	if_malloc_error(y_str);
	tmp = ft_strjoin("Mouse position : x = ", x_str);
	free(x_str);
	if_malloc_error(tmp);
	fractal->last_pos = ft_strjoin(tmp, "  y = ");
	free(tmp);
	if_malloc_error(fractal->last_pos);
	tmp = fractal->last_pos;
	fractal->last_pos = ft_strjoin(tmp, y_str);
	free(tmp);
	free(y_str);
	if_malloc_error(fractal->last_pos);
	manage_text(fractal);
//	draw_text_box(fractal);
//	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr,
//		5, 25, 0xFFFFFF, fractal->last_pos);
	return (0);	
}
