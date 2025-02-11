/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:38:32 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/09 03:37:31 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/fractol.h"

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
	ft_printf("Exiting the program. See ya !\n");
	exit(EXIT_SUCCESS);
	return (0);
}

/*
	* XK_Escape = ESC || XK_Left = left arrow || XK_Down = down arrow,...
*/
int	handle_key(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		handle_exit(fractal);
	else if (keysym == XK_Left)
		displacement('L', fractal);
	else if (keysym == XK_Right)
		displacement('R', fractal);
	else if (keysym == XK_Up)
		displacement('U', fractal);
	else if (keysym == XK_Down)
		displacement('D', fractal);
	else if (keysym == XK_KP_Add)
		change_max_iterations('+', fractal);
	else if (keysym == XK_KP_Subtract)
		change_max_iterations('-', fractal);
	else
	{
		handle_key_two(keysym, fractal);
		return (0);
	}
	return (0);
}

/*
	* Events who don't need an automatic rendering each time.
	* I.e, if the contrast is already the minimum value accepted,
	* we don't need to rendering the image a new time.
*/
void	handle_key_two(int keysym, t_fractal *fractal)
{
	if (keysym == XK_n)
		change_color_mode('N', fractal);
	else if (keysym == XK_r)
		change_color_mode('R', fractal);
	else if (keysym == XK_g)
		change_color_mode('G', fractal);
	else if (keysym == XK_b)
		change_color_mode('B', fractal);
	else if (keysym == XK_y)
		change_color_mode('Y', fractal);
	else if (keysym == XK_o)
		change_color_mode('O', fractal);
	else if (keysym == XK_p)
		change_color_mode('P', fractal);
	else if (keysym == XK_c)
		change_color_mode('C', fractal);
	else if (keysym == XK_Tab)
		swap_colors(fractal);
	else
	{
		handle_key_three(keysym, fractal);
		return ;
	}
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
	{
		ft_putstr_fd("Zoom out\n", 1);
		apply_zoom(fractal, x, y, 1.2);
	}
	else if (button == Button4)
	{
		ft_putstr_fd("Zoom in\n", 1);
		apply_zoom(fractal, x, y, 0.8);
	}
	else if (button == Button3)
	{	
		ft_putstr_fd("Big zoom out\n", 1);
		apply_zoom(fractal, x, y, 1.8);
	}
	else if (button == Button1)
	{
		ft_putstr_fd("Big zoom in\n", 1);
		apply_zoom(fractal, x, y, 0.2);
	}
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
	return (0);
}
