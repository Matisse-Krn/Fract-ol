/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:51:06 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/09 03:35:09 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	put_a_string(int x, int y, char *s, t_fractal *fractal)
{
	if (fractal->img.height > y && fractal->img.width > x)
	{
		mlx_string_put(fractal->mlx_ptr, fractal->win_ptr,
			x, y, 0xFFFFFF, s);
	}
}

void	print_shortcuts(t_fractal *fractal)
{
	put_a_string(5, fractal->img.height - 64, "Scrool Up : zoom in       \
Scroll Down : zoom out       LClick : big zoom in       RClick : big zoom out\
       BackSpace : reset view\
       Space : psychedelic", fractal);
	put_a_string(5, fractal->img.height - 46, "+ (keypad) : increase definition\
       - (keypad) : reduce definition       + : smoothen       \
- : contrast", fractal);
	put_a_string(5, fractal->img.height - 28, "COLORS :", fractal);
	put_a_string(5, fractal->img.height - 10, "N : Normal       R : Red       \
G : Green       B : Blue       Y : Yellow       O : Orange       P : Pink       \
C : Cyan    ||    TAB : Reverse color mode", fractal);
}

void	manage_text(t_fractal *fractal)
{
	draw_text_boxes(fractal);
	print_shortcuts(fractal);
	put_a_string(5, 25, fractal->last_pos, fractal);
	put_color_mode(fractal);
	put_max_iterations(fractal);
}
