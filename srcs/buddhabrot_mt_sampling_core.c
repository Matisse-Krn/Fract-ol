#include "fractol.h"

/**
 * @brief  Generate a random double within a specified range.
 *
 * Produces a random floating-point value between `lo` and `hi` using
 * a 24-bit portion of the output from `bb_xorshift()`. The result is
 * uniformly distributed within the given range.
 *
 * @param  seed  Pointer to the random number generator seed.
 * @param  lo    Lower bound of the desired range.
 * @param  hi    Upper bound of the desired range.
 * @return A random double between `lo` and `hi`.
 *
 * @note   The seed value is modified in place to produce the sequence.
 * @pre    `seed` must be a valid pointer to an unsigned integer.
 * @post   Returns a value `v` such that `lo <= v <= hi`.
 */
double	bb_rand_range(unsigned int *seed, double lo, double hi)
{
	double	u;
	double	r;

	u = (double)(bb_xorshift(seed) & 0xFFFFFF);
	r = u / 16777215.0;
	return (lo + (hi - lo) * r);
}

/**
 * @brief  Compute the escape iteration for a complex point.
 *
 * Iterates the Mandelbrot formula starting from `z = 0` until the
 * magnitude exceeds the escape threshold or the maximum iteration
 * count is reached. Returns the iteration number at which the escape
 * occurred, or -1 if the point did not escape.
 *
 * @param  f  Pointer to the fractal context (`t_fractal`) containing
 *            iteration and escape threshold parameters.
 * @param  c  Complex coordinate of the point to evaluate.
 * @return Escape iteration index, or -1 if the point never escaped.
 *
 * @note   Used in Buddhabrot rendering to determine if an orbit should
 *         be accumulated into the histogram.
 * @pre    `f` must be initialized with valid Buddhabrot parameters.
 * @post   No side effects on the fractal context.
 */
int	bb_escape_iter(const t_fractal *f, t_complex c)
{
	double	zr;
	double	zi;
	double	tmp;
	int		i;
	int		esc;

	zr = 0.0;
	zi = 0.0;
	i = 0;
	esc = -1;
	while (i < f->bb_max_iter)
	{
		tmp = (zr * zr) - (zi * zi) + c.real;
		zi = (2.0 * zr * zi) + c.imag;
		zr = tmp;
		if (((zr * zr) + (zi * zi)) > f->escape_value)
		{
			esc = i;
			break ;
		}
		i++;
	}
	return (esc);
}

/**
 * @brief  Increment histogram count for a pixel and update maximum.
 *
 * Adds one to the histogram bin corresponding to the given pixel
 * coordinates, and updates the maximum bin value if the new value
 * exceeds the current maximum.
 *
 * @param  f    Pointer to the fractal context (`t_fractal`) containing
 *              image dimensions.
 * @param  p    Pointer to the pixel coordinates (`t_pixel`).
 * @param  acc  Pointer to the accumulation structure containing the
 *              histogram and maximum value pointer.
 * @return None.
 *
 * @note   This function assumes the pixel coordinates are valid and
 *         within the image bounds.
 * @pre    `p` must be inside the image dimensions.
 * @post   Histogram bin count is incremented, and max value updated if needed.
 */
static void	bb_accum_at_screen(const t_fractal *f,
							const t_pixel *p, t_bb_accum *acc)
{
	int			idx;
	uint32_t	val;

	idx = (p->y * f->img.width) + p->x;
	acc->hist[idx] += 1;
	val = acc->hist[idx];
	if (val > *(acc->max))
		*(acc->max) = val;
}

/**
 * @brief  Accumulate an orbit's points into the histogram.
 *
 * Iterates the Mandelbrot formula for a complex coordinate `c` and,
 * for each iteration after the minimum iteration threshold, maps the
 * current complex position to screen coordinates and increments the
 * corresponding histogram bin.
 *
 * @param  f    Pointer to the fractal context (`t_fractal`).
 * @param  c    Complex starting coordinate of the orbit.
 * @param  esc  Escape iteration index, as returned by `bb_escape_iter()`.
 * @param  acc  Pointer to the accumulation structure for histogram updates.
 * @return None.
 *
 * @note   Points are only accumulated if they map inside the visible
 *         viewport via `bb_world_to_screen()`.
 * @pre    `esc` must be non-negative and `f` must be initialized.
 * @post   The histogram is updated with contributions from the orbit.
 */
void	bb_orbit_accumulate(const t_fractal *f, t_complex c,
							int esc, t_bb_accum *acc)
{
	double	zr;
	double	zi;
	double	tmp;
	int		i;
	t_pixel	screen;

	zr = 0.0;
	zi = 0.0;
	i = 0;
	while (i <= esc)
	{
		tmp = (zr * zr) - (zi * zi) + c.real;
		zi = (2.0 * zr * zi) + c.imag;
		zr = tmp;
		if (i >= f->bb_min_iter && bb_world_to_screen(f, zr, zi, &screen))
			bb_accum_at_screen(f, &screen, acc);
		i++;
	}
}
