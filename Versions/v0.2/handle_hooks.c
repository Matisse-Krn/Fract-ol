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

static void	ft_exit(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
	mlx_destroy_display(fractal->mlx_ptr);
	free(fractal->mlx_ptr);
	exit(EXIT_SUCCESS);
}

int	handle_key(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		ft_exit(fractal);
	else if (keysym == XK_Left)
		fractal->shift_x -= 0.5;
	else if (keysym == XK_Right)
		fractal->shift_x += 0.5;
	else if (keysym == XK_Up)
		fractal->shift_y += 0.5;
	else if (keysym == XK_Down)
		fractal->shift_y -= 0.5;
	fractal_rendering(fractal);
	return (0);
}

int	handle_exit(t_fractal *fractal)
{
	ft_exit(fractal);
	return (0);
}
