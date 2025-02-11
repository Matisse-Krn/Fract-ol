/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   text_box.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/06 13:39:33 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/07 13:18:32 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	draw_text_box(t_fractal *fractal)
{
	int	x;
	int	y;

	x = 0;
	while (x < 220 && x < fractal->img.width) // box width
	{
		y = 0;
		while (y < 50 && y < fractal->img.height) // box height
		{
			my_mlx_pixel_put(&fractal->img, x, y, 0x000000);
			y++;
		}
		x++;
	}
	x = 0;
	while (x < fractal->img.width) // box width
	{
		y = fractal->img.height - 35;	// box height
		while (y < fractal->img.height)
		{	
			my_mlx_pixel_put(&fractal->img, x, y, 0x000000);
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr,
		fractal->img.img_ptr, 0, 0);
}
