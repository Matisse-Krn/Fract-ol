#include "fractol.h"

/**
 * @brief  Compute the number of color steps for Buddhabrot rendering.
 *
 * Determines the number of discrete color steps used in the color
 * mapping process. By default, it uses `max_iterations`, but if the
 * `range_color_mode` is set to 'Y', it returns a fixed value of 220
 * steps instead.
 *
 * @param  f  Pointer to the fractal context (`t_fractal`) containing
 *            rendering parameters and color mode settings.
 * @return The number of steps to use for color interpolation.
 *
 * @note   The special mode 'Y' is used to restrict the color range
 *         for a specific visual style.
 * @pre    The fractal context must be initialized with valid
 *         `max_iterations` and `range_color_mode` values.
 * @post   The returned step count is used for palette indexing.
 */
static int	bb_compute_steps(t_fractal *f)
{
	int	steps;

	steps = f->max_iterations;
	if (f->range_color_mode == 'Y')
		steps = 220;
	return (steps);
}

/**
 * @brief  Compute the RGB color for a histogram count value.
 *
 * Converts a histogram sample count into a normalized value, applies
 * minimum normalization constraints, maps it to a palette index, and
 * retrieves the corresponding RGB color. This ensures smooth and
 * consistent color mapping for Buddhabrot rendering.
 *
 * @param  count      The histogram value (number of hits for a pixel).
 * @param  f          Pointer to the fractal context (`t_fractal`)
 *                    containing rendering parameters and palette info.
 * @param  steps      The number of discrete color steps to use.
 * @param  min_norm   The minimum normalized brightness allowed.
 * @return The computed RGB color as an integer.
 *
 * @note   Uses `bb_normalize_iteration_count()` for normalization
 *         and `bb_palette_ramp5()` to obtain the actual color.
 * @pre    `steps` must be > 0, and `f->bb_max_count` must be valid.
 * @post   Returned color is ready for direct pixel plotting.
 */
static int	bb_color_from_count(uint32_t count, t_fractal *f,
							int steps, double min_norm)
{
	double	norm;
	int		idx_cyclic;
	int		i_for_palette;
	int		color;

	if (count == 0)
		return (0x000000);
	norm = bb_normalize_iteration_count(count, f->bb_max_count, f);
	if (norm < min_norm)
		norm = min_norm;
	idx_cyclic = (int)(norm * (double)(steps - 1) + 0.5);
	if (idx_cyclic < 0)
		idx_cyclic = 0;
	else if (idx_cyclic > steps - 1)
		idx_cyclic = steps - 1;
	i_for_palette = (int)((double)idx_cyclic
			* (double)f->max_iterations / (double)(steps - 1) + 0.5);
	if (i_for_palette < 1)
		i_for_palette = 1;
	else if (i_for_palette > f->max_iterations)
		i_for_palette = f->max_iterations;
	color = bb_palette_ramp5(norm);
	return (color);
}

/**
 * @brief  Render the Buddhabrot image from the histogram data.
 *
 * Iterates through all pixels in the image, converts histogram counts
 * into colors using the palette mapping, and writes the result into the
 * image buffer. This is the final step that transforms histogram data
 * into a visible fractal image.
 *
 * @param  f  Pointer to the fractal context (`t_fractal`) containing
 *            image buffer, histogram, and rendering parameters.
 * @return None.
 *
 * @note   Uses `bb_compute_steps()` to determine color resolution
 *         and `bb_color_from_count()` for per-pixel color computation.
 * @pre    The histogram (`f->bb_hist`) must be filled with valid data.
 * @post   The image buffer in `f->img` is updated with the rendered
 *         Buddhabrot fractal colors.
 */
void	bb_draw_from_histogram(t_fractal *f)
{
	int		i;
	int		steps;
	int		total;
	int		color;
	double	min_norm;

	min_norm = 0.02;
	steps = bb_compute_steps(f);
	total = f->img.width * f->img.height;
	i = 0;
	while (i < total)
	{
		color = bb_color_from_count(f->bb_hist[i], f, steps, min_norm);
		my_mlx_pixel_put(&f->img, i % f->img.width, i / f->img.width, color);
		i++;
	}
}
