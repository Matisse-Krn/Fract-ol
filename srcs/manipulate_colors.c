#include "fractol.h"

/*
 * Interpolates between two colors based on the iteration count.
 * Uses a power function to adjust the contrast smoothly.
 * 
 * @param min The minimum color value.
 * @param max The maximum color value.
 * @param i The current iteration count.
 * @param fractal A pointer to the fractal structure.
 * @return The interpolated color as an integer.
 * 
 * Variables:
	- color.r_min, color.g_min, color.b_min: Extracted RGB components of min.
	- color.r_max, color.g_max, color.b_max: Extracted RGB components of max.
	- ratio: Normalized iteration count between 0 and 1.
	- adjusted_ratio: Contrast-adjusted ratio for smooth transitions.
*/

/*int	interpolate_color(int min, int max, int i, t_fractal *fractal)*/
/*{*/
/*	t_rgb	color;*/
/*	double	ratio;*/
/*	double	adjusted_ratio;*/
/**/
/*	ratio = (double)i / (double)fractal->max_iterations;*/
/*	adjusted_ratio = pow(ratio, fractal->contrast_exponent);*/
/*	color.r_min = (min >> 16) & 0xFF;*/
/*	color.g_min = (min >> 8) & 0xFF;*/
/*	color.b_min = min & 0xFF;*/
/*	color.r_max = (max >> 16) & 0xFF;*/
/*	color.g_max = (max >> 8) & 0xFF;*/
/*	color.b_max = max & 0xFF;*/
/*	color.r_min += (color.r_max - color.r_min) * adjusted_ratio;*/
/*	color.g_min += (color.g_max - color.g_min) * adjusted_ratio;*/
/*	color.b_min += (color.b_max - color.b_min) * adjusted_ratio;*/
/*	return ((color.r_min << 16) | (color.g_min << 8) | color.b_min);*/
/*}*/











/*
 * Applies a color gradient using either:
 * - contrast exponent (default mode),
 * - logarithmic scale (palette_mode == 'L'),
 * - adaptive scale (palette_mode == 'A'), based on max i reached.
 */
int	interpolate_color(int min, int max, int i, t_fractal *f)
{
	t_rgb	color;
	double	ratio;
	double	adjusted;
	/*double	base;*/

	if (f->palette_mode == 'L')
	{
		if (i == 0)
			adjusted = 0;
		else
			adjusted = log((double)i + 1) / log((double)f->max_iterations);
	}
	else if (f->palette_mode == 'A' && f->i_max > 0)
		adjusted = (double)i / (double)f->i_max;
	else
	{
		ratio = (double)i / (double)f->max_iterations;
		adjusted = pow(ratio, f->contrast_exponent);
	}
	color.r_min = (min >> 16) & 0xFF;
	color.g_min = (min >> 8) & 0xFF;
	color.b_min = min & 0xFF;
	color.r_max = (max >> 16) & 0xFF;
	color.g_max = (max >> 8) & 0xFF;
	color.b_max = max & 0xFF;
	color.r_min += (color.r_max - color.r_min) * adjusted;
	color.g_min += (color.g_max - color.g_min) * adjusted;
	color.b_min += (color.b_max - color.b_min) * adjusted;
	return ((color.r_min << 16) | (color.g_min << 8) | color.b_min);
}

/*
 * Adjusts the contrast exponent, modifying the gradient effect.
 * Limits the contrast exponent between 0.1 and 3.
 * 
 * @param sign The character indicating increase ('+') or decrease ('-').
 * @param fractal A pointer to the fractal structure.
*/
void	change_contrast(char sign, t_fractal *fractal)
{
	if (!sign)
		return ;
	if (sign == '+')
	{
		if (fractal->contrast_exponent < 3)
		{
			fractal->contrast_exponent += 0.05;
			ft_putstr_fd("Contrat ratio : increase\n", 1);
			fractal_rendering(fractal);
		}
	}
	else if (sign == '-')
	{
		if (fractal->contrast_exponent >= 0.15)
		{
			fractal->contrast_exponent -= 0.05;
			ft_putstr_fd("Contrast ratio : reduce\n", 1);
			fractal_rendering(fractal);
		}
	}
}

/*
 * Swaps the current minimum and maximum colors.
 * This effectively inverts the color gradient.
 * 
 * @param fractal A pointer to the fractal structure.
*/
void	swap_colors(t_fractal *fractal)
{
	double	tmp;

	tmp = fractal->color_min;
	fractal->color_min = fractal->color_max;
	fractal->color_max = tmp;
	ft_putstr_fd("Colors swapped\n", 1);
	fractal_rendering(fractal);
}

/*
 * Toggles psychedelic mode on or off.
 * In psychedelic mode, color transitions are unpredictable,
	and contrast or smoothing adjustments are disabled.
 * Changing the maximum number of iterations ('max_iterations') will change
	the color palette.
 * 
 * @param fractal A pointer to the fractal structure.
*/
void	swap_psy_mode(t_fractal *fractal)
{
	if (fractal->psy == 'N')
	{
		fractal->psy = 'Y';
		ft_putstr_fd("Psychedelic mode ON.\n\
You can change colors by the usuals shortcuts,\nbut don't rely on \
the names (initials) of the shortcuts.\nAnd, by the way : you can't \
control contrast or smoothing here.\nSo relax... Or try changing the \
maximum number of iterations (keypad + or -).\nEnjoy the trip !\n\n", 1);
	}
	else if (fractal->psy == 'Y')
	{
		fractal->psy = 'N';
		ft_putstr_fd("Psychedelic mode OFF.\n\
You're such an ordinary person...\n\n", 1);
	}
	fractal_rendering(fractal);
}
