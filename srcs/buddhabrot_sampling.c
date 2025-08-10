#include "fractol.h"

/**
 * @brief  Generate a pseudo-random number using the Xorshift algorithm.
 *
 * Implements a 32-bit Xorshift PRNG (Pseudo-Random Number Generator).
 * Updates the internal state and returns the next pseudo-random value.
 *
 * @param  state  Pointer to the current generator state.
 * @return The next pseudo-random number as an unsigned int.
 *
 * @note   If the state is 0, it is re-seeded with a fixed non-zero constant
 *         to avoid a degenerate sequence.
 * @pre    `state` must be a valid pointer to an unsigned int.
 * @post   The value at `state` is updated with the new generator state.
 */
unsigned int	bb_xorshift(unsigned int *state)
{
	unsigned int	x;

	x = *state;
	if (x == 0)
		x = 2463534242U;
	x ^= x << 13;
	x ^= x >> 17;
	x ^= x << 5;
	*state = x;
	return (x);
}

/**
 * @brief  Increment the global histogram at a pixel location.
 *
 * Adds one to the histogram bin corresponding to the given pixel
 * coordinates and updates the local maximum value if necessary.
 *
 * @param  f         Pointer to the fractal context (`t_fractal`)
 *                   containing the global histogram.
 * @param  p         Pointer to the pixel coordinates (`t_pixel`).
 * @param  local_max Pointer to the variable tracking the highest bin value
 *                   seen during the current sampling pass.
 * @return None.
 *
 * @note   Assumes the pixel coordinates are within the image bounds.
 * @pre    `f`, `p`, and `local_max` must be valid pointers.
 * @post   The global histogram is incremented at the target pixel,
 *         and `local_max` is updated if needed.
 */
static void	bb_accum_global_at_screen(t_fractal *f,
									const t_pixel *p, uint32_t *local_max)
{
	int			idx;
	uint32_t	val;

	idx = (p->y * f->img.width) + p->x;
	f->bb_hist[idx] += 1;
	val = f->bb_hist[idx];
	if (val > *local_max)
		*local_max = val;
}

/**
 * @brief  Accumulate an orbit directly into the global histogram.
 *
 * Iterates the Mandelbrot formula for a complex point `c` and records
 * all iterations after the minimum iteration threshold into the global
 * histogram. Updates the local maximum histogram value when necessary.
 *
 * @param  f         Pointer to the fractal context (`t_fractal`).
 * @param  c         Complex starting coordinate of the orbit.
 * @param  esc       Escape iteration index returned by `bb_escape_iter()`.
 * @param  local_max Pointer to the variable tracking the highest bin value
 *                   seen during accumulation.
 * @return None.
 *
 * @note   Uses `bb_world_to_screen()` to map complex coordinates to
 *         pixel positions before accumulating.
 * @pre    `f` and `local_max` must be valid pointers; `esc` must be >= 0.
 * @post   The global histogram is updated for all contributing orbit points.
 */
static void	bb_orbit_accumulate_global(t_fractal *f, t_complex c,
										int esc, uint32_t *local_max)
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
			bb_accum_global_at_screen(f, &screen, local_max);
		i++;
	}
}

/**
 * @brief  Trace and accumulate a single Buddhabrot sample globally.
 *
 * Computes the escape iteration for the point `(cr, ci)` and, if valid,
 * accumulates its orbit directly into the global histogram.
 *
 * @param  f         Pointer to the fractal context (`t_fractal`).
 * @param  cr        Real part of the sample point.
 * @param  ci        Imaginary part of the sample point.
 * @param  local_max Pointer to the variable tracking the highest bin value
 *                   seen during accumulation.
 * @return 1 if the point contributed to the histogram, 0 otherwise.
 *
 * @note   Points escaping before `f->bb_min_iter` are ignored.
 * @pre    `f` and `local_max` must be valid pointers.
 * @post   The global histogram may be updated, and `local_max` may change.
 */
static int	bb_trace_one(t_fractal *f,
						double cr, double ci, uint32_t *local_max)
{
	t_complex	c;
	int			esc;

	c.real = cr;
	c.imag = ci;
	esc = bb_escape_iter(f, c);
	if (esc < f->bb_min_iter)
		return (0);
	bb_orbit_accumulate_global(f, c, esc, local_max);
	return (1);
}

/**
 * @brief  Run Buddhabrot sampling in single-threaded mode.
 *
 * Generates `n` random complex points, filters out those in the main
 * cardioid or period-2 bulb, and traces valid orbits directly into
 * the global histogram. Tracks and returns the maximum bin value
 * encountered during this pass.
 *
 * @param  f  Pointer to the fractal context (`t_fractal`) containing
 *            Buddhabrot rendering parameters.
 * @param  n  Number of samples to generate and process.
 * @return The highest bin value found during this sampling pass.
 *
 * @note   Uses `bb_rand_range()` for coordinate generation and
 *         `bb_reject_cardioid_bulb()` for early rejection.
 * @pre    `f` must be initialized with valid histogram and parameters.
 * @post   The global histogram is updated, and `f->bb_seed` is advanced.
 */
int	bb_run_samples_single(t_fractal *f, int n)
{
	int				k;
	double			cr;
	double			ci;
	unsigned int	seed;
	uint32_t		max;

	k = 0;
	max = 0;
	seed = f->bb_seed;
	while (k < n)
	{
		cr = bb_rand_range(&seed, -2.2, 1.2);
		ci = bb_rand_range(&seed, -1.7, 1.7);
		if (!bb_reject_cardioid_bulb(cr, ci))
			(void)bb_trace_one(f, cr, ci, &max);
		k++;
	}
	f->bb_seed = seed;
	return ((int)max);
}
