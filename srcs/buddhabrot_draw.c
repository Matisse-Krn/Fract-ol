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

static int	bb_color_from_count(uint32_t count, t_fractal *f,
								int steps, double min_norm)
{
	double	norm;
	int		idx;
	double	t;

	if (count == 0)
		return (0x000000);
	if (steps < 2 || f->bb_max_count < 1)
		return (0x000000);
	norm = bb_normalize_iteration_count(count, f->bb_max_count, f);
	if (norm < min_norm)
		norm = min_norm;
	if (norm > 1.0)
		norm = 1.0;
	idx = (int)(norm * (double)(steps - 1) + 0.5);
	if (idx < 0)
		idx = 0;
	else if (idx > steps - 1)
		idx = steps - 1;
	t = (double)idx / (double)(steps - 1);
	return (bb_palette_ramp5(t));
}


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
	if (snap_lock(&f->img))
	{
		i = 0;
		while (i < total)
		{
			color = bb_color_from_count(f->bb_hist[i], f, steps, min_norm);
			my_mlx_pixel_put(&f->img, i % f->img.width, i / f->img.width, color);
			i++;
		}
		snap_unlock(&f->img);
	}
}

