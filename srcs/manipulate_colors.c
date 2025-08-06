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

static int	interpolate_rgb(t_rgb *color, int min, int max, double adjusted)
{
	color->r_min = (min >> 16) & 0xFF;
	color->g_min = (min >> 8) & 0xFF;
	color->b_min = min & 0xFF;
	color->r_max = (max >> 16) & 0xFF;
	color->g_max = (max >> 8) & 0xFF;
	color->b_max = max & 0xFF;
	color->r_min += (color->r_max - color->r_min) * adjusted;
	color->g_min += (color->g_max - color->g_min) * adjusted;
	color->b_min += (color->b_max - color->b_min) * adjusted;
	return ((color->r_min << 16) | (color->g_min << 8) | color->b_min);
}

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

int	interpolate_color(int min, int max, int i, t_fractal *f)
{
	t_rgb	color;
	double	ratio;
	double	adjusted;

	if (f->render_mode == 'L')
	{
		if (i == 0)
			adjusted = 0;
		else
			adjusted = log((double)i + 1) / log((double)f->max_iterations);
	}
	else if (f->render_mode == 'F')
		adjusted = log(i + 1) / log(1000);
	else if (f->render_mode == 'C')
		adjusted = (double)((i * 15) % 256) / 255.0;
	else if (f->render_mode == 'A' && f->i_max > 0)
		adjusted = (double)i / (double)f->i_max;
	else
	{
		ratio = (double)i / (double)f->max_iterations;
		adjusted = pow(ratio, f->contrast_exponent);
	}
	return (interpolate_rgb(&color, min, max, adjusted));
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
 * Toggles psychedelic/complementary modes on or off.
 * In psychedelic mode, color transitions are unpredictable,
	and contrast or smoothing adjustments are disabled.
 * Changing the maximum number of iterations ('max_iterations') will change
	the color palette.
 * 
 * @param fractal A pointer to the fractal structure.
*/
void	swap_range_color_mode(t_fractal *fractal)
{
	if (fractal->range_color_mode == 'N')
	{
		fractal->range_color_mode = 'Y';
		ft_putstr_fd("Psychedelic mode : ON\n\
You can change colors by the usuals shortcuts,\nbut don't rely on \
the names (initials) of the shortcuts.\nAnd, by the way : you can't \
control contrast or smoothing here.\nSo relax... Or try changing the \
maximum number of iterations (keypad + or -).\nEnjoy the trip !\n\n", 1);
	}
	else if (fractal->range_color_mode == 'Y')
	{
		fractal->range_color_mode = 'N';
		ft_putstr_fd("Normal mode : ON\n\
You're such an ordinary person...\n\n", 1);
	}
	fractal_rendering(fractal);
}
