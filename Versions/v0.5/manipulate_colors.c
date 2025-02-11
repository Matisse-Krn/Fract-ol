/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manipulate_colors.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 16:08:33 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/08 02:08:00 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int	interpolate_color(int min, int max, int i, t_fractal *fractal)
{
	t_rgb	color;
	double	ratio;
	double	adjusted_ratio;

	ratio = (double)i / (double)fractal->max_iterations;
	adjusted_ratio = pow(ratio, fractal->contrast_exponent); // valeur + haute = lissage || valeur + basse = contraste
	// Extraction des composantes RGB
	color.r_min = (min >> 16) & 0xFF;
	color.g_min = (min >> 8) & 0xFF;
	color.b_min = min & 0xFF;
	color.r_max = (max >> 16) & 0xFF;
	color.g_max = (max >> 8) & 0xFF;
	color.b_max = max & 0xFF;
	// Interpolation modifiée avec `adjusted_ratio`
	color.r_min += (color.r_max - color.r_min) * adjusted_ratio;
	color.g_min += (color.g_max - color.g_min) * adjusted_ratio;
	color.b_min += (color.b_max - color.b_min) * adjusted_ratio;
	// Reconstruction de la couleur finale
	return ((color.r_min << 16) | (color.g_min << 8) | color.b_min);
}

void	change_contrast(char sign, t_fractal *fractal)
{
	if (!sign)
		return ;
	if (sign == '+')
	{
		if (fractal->contrast_exponent < 3)
		{
			fractal->contrast_exponent += 0.05;
			printf("Contrast value = %f\n", fractal->contrast_exponent);
			fractal_rendering(fractal);
		}
	}
	else if (sign == '-')
	{
		if (fractal->contrast_exponent >= 0.15)
		{
			fractal->contrast_exponent -= 0.05;
			printf("Contrast value = %f\n", fractal->contrast_exponent);
			fractal_rendering(fractal);
		}
	}
}

void	swap_colors(t_fractal *fractal)
{
	double	tmp;

	tmp = fractal->color_min;
	fractal->color_min = fractal->color_max;
	fractal->color_max = tmp;
	fractal_rendering(fractal);
}

void	swap_psy_mode(t_fractal *fractal)
{
	if (fractal->psy == 'N')
	{
		fractal->psy = 'Y';
		ft_putstr_fd("Psychedelic mode ON.\n\
You can change colors by the usuals shortcuts,\nbut don't rely on \
the names (initials) of the shortcuts.\nAnd, by the way : you can't \
control contrast or smoothing here.\nSo relax... Or try changing the \
maximum number of iterations (keypad + or -), and enjoy the trip !\n\n", 1);
	}
	else if (fractal->psy == 'Y')
	{
		fractal->psy = 'N';
		ft_putstr_fd("Psychedelic mode OFF.\n\
You're such an ordinary person...\n\n", 1);
	}
	fractal_rendering(fractal);
}
