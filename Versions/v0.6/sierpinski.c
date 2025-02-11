/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sierpinski.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 04:55:19 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/09 06:25:24 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void draw_square(int x, int y, int color, t_fractal *fractal)
{
    int i;
	int	j;

	i = -1;
    while (++i < fractal->size)
    {
		j = -1;
        while (++j < fractal->size)
            my_mlx_pixel_put(&fractal->img, x + i, y + j, color);
    }
}

void draw_sierpinski_carpet(int x, int y, t_fractal *fractal)
{
    int new_size;
    int i;
    int j;
	int	original_size;
	int	original_depth;

    if (fractal->depth == 0)
    {
        draw_square(x, y, 0xFFFFFF, fractal);
        return ;
    }

    new_size = fractal->size / 3;
    i = -1;
    while (++i < 3)
    {
        j = -1;
        while (++j < 3)
        {
            if (i == 1 && j == 1) // On évite le centre sans `continue`
				continue ;
            original_size = fractal->size;
			original_depth = fractal->depth;
			fractal->size = new_size;
            fractal->depth--;

            draw_sierpinski_carpet(x + i * new_size, y + j * new_size, fractal);

                // Restaurer les valeurs après l'appel récursif
            fractal->size = original_size;
            fractal->depth = original_depth;
        }
    }
}

void render_sierpinski(t_fractal *fractal)
{
    // On redessine l'image sur le buffer MLX
    draw_sierpinski_carpet(0, 0, fractal);
    
    // Affichage final
    mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr, \
							fractal->img.img_ptr, 0, 0);
	ft_printf("Render done\n");
}

