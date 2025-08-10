#include "fractol.h"

/**
 * @brief  Computes the adjusted ratio for color interpolation.
 *
 * Calculates a normalized ratio based on the current rendering mode,
 * the iteration count, and fractal parameters. This ratio is later
 * used to interpolate between minimum and maximum colors for each pixel.
 *
 * @param  adjusted  Pointer to store the computed ratio.
 * @param  i         The number of iterations for the current pixel.
 * @param  f         Pointer to the fractal structure containing
 *					 render parameters.
 * @return None.
 *
 * @note   Supports multiple rendering modes: logarithmic (L), fixed log (F),
 *         cyclic modulo (C), adaptive (A), and contrast-adjusted (default).
 * @warning Division by zero is avoided by checking `f->i_max` and
 *			`f->max_iterations`.
 * @pre    `adjusted` must be a valid pointer.
 * @post   `*adjusted` contains the normalized ratio for color interpolation.
 */
static void	get_adjusted_ratio(double *adjusted, int i, t_fractal *f)
{
	double	ratio;

	if (f->render_mode == 'L')
	{
		if (i == 0)
			*adjusted = 0;
		else
			*adjusted = log((double)i + 1) / log((double)f->max_iterations);
	}
	else if (f->render_mode == 'F')
		*adjusted = log(i + 1) / log(1000);
	else if (f->render_mode == 'C')
		*adjusted = (double)((i * 15) % 256) / 255.0;
	else if (f->render_mode == 'A')
	{
		if (f->i_max > 0)
			*adjusted = (double)i / (double)f->i_max;
		else
			*adjusted = 0.0;
	}
	else
	{
		ratio = (double)i / (double)f->max_iterations;
		*adjusted = pow(ratio, f->contrast_exponent);
	}
}

/**
 * @brief  Interpolates a color between two RGB values.
 *
 * Computes a new color by linearly interpolating each RGB channel
 * between a minimum and a maximum color based on the adjusted ratio
 * from the fractal's rendering parameters.
 *
 * @param  min  The minimum RGB color (as a 24-bit integer).
 * @param  max  The maximum RGB color (as a 24-bit integer).
 * @param  i    The number of iterations for the current pixel.
 * @param  f    Pointer to the fractal structure containing render parameters.
 * @return The interpolated RGB color as a 24-bit integer.
 *
 * @note   Uses `get_adjusted_ratio()` to determine interpolation progress.
 * @pre    `min` and `max` must be valid RGB integer values.
 * @post   Returns an RGB color smoothly transitioning from `min` to `max`.
 */
int	interpolate_color(int min, int max, int i, t_fractal *f)
{
	t_rgb	color;
	double	adjusted;

	get_adjusted_ratio(&adjusted, i, f);
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

/**
 * @brief  Adjusts the fractal's contrast exponent.
 *
 * Increases or decreases the contrast exponent used for color rendering
 * depending on the `sign` parameter. Higher values increase contrast,
 * lower values reduce it.
 *
 * @param  sign     '+' to increase contrast, '-' to decrease.
 * @param  fractal  Pointer to the fractal structure.
 * @return None.
 *
 * @note   After modification, the fractal is re-rendered to apply changes.
 * @warning Changes are bounded between 0.15 and 3.0 to avoid extreme effects.
 * @pre    `fractal` must be initialized.
 * @post   `fractal->contrast_exponent` is updated and rendering refreshed.
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

/**
 * @brief  Swaps the fractal's minimum and maximum colors.
 *
 * Exchanges `color_min` and `color_max` values to invert the gradient.
 * This results in a reversed color scheme for rendering.
 *
 * @param  fractal  Pointer to the fractal structure.
 * @return None.
 *
 * @note   The fractal is immediately re-rendered after swapping colors.
 * @pre    `fractal` must have valid `color_min` and `color_max` values.
 * @post   Colors are inverted in the gradient used for rendering.
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

/**
 * @brief  Toggles between normal and psychedelic color range modes.
 *
 * Switches the `range_color_mode` between normal ('N') and psychedelic ('Y')
 * rendering. Psychedelic mode cycles through colors regardless of standard
 * color key mappings, and disables contrast/smoothing adjustments.
 *
 * @param  fractal  Pointer to the fractal structure.
 * @return None.
 *
 * @note   Displays a contextual message explaining the mode's behavior.
 * @pre    `fractal` must be initialized.
 * @post   `range_color_mode` is updated and rendering refreshed.
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
