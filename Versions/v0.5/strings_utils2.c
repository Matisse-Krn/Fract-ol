/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:51:06 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/07 20:11:27 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	put_a_string(char *s, int x, int y, t_fractal *fractal)
{
//	if (fractal->img.height > y && fractal->img.width > x)
//	{
		mlx_string_put(fractal->mlx_ptr, fractal->win_ptr,
		x, y, 0xFFFFFF, s);
//	}
}

void	print_shortcuts(t_fractal *fractal)
{	
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 5, fractal->img.height - 64, 0xFFFFFF,"Scrool Up : zoom in       Scroll Down : zoom out       \
LClick : big zoom in       RClick : big zoom out       + : smoothen       \
- : contrast");
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 5, fractal->img.height - 46, 0xFFFFFF,"+ (keypad) : increase definition      - (keypad) : reduce definition");
/*	put_a_string("COLORS :", 5, 65, fractal);
	put_a_string("N : Normal", 5, 90, fractal);
	put_a_string("R : Red", 5, 108, fractal);
	put_a_string("G : Green", 5, 126, fractal);
	put_a_string("B : Blue", 5, 144, fractal);
	put_a_string("Y : Yellow", 5, 162, fractal);
	put_a_string("O : Orange", 5, 180, fractal);
	put_a_string("P : Pink", 5, 198, fractal);
	put_a_string("C : Cyan", 5, 216, fractal);
*/	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 5, fractal->img.height - 28, 0xFFFFFF, "COLORS :");
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr, 5, fractal->img.height - 10, 0xFFFFFF,"N : Normal       R : Red       G : Green       B : Blue       Y : Yellow       O : Orange       P : Pink       C : Cyan");
}

