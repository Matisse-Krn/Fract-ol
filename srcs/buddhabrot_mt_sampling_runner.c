#include "fractol.h"

/**
 * @brief  Trace and accumulate a single Buddhabrot sample locally.
 *
 * Determines whether the given complex point escapes within the allowed
 * iteration range, and if so, accumulates its orbit into the provided
 * local histogram accumulator.
 *
 * @param  fractal_params        Pointer to the fractal context (`t_fractal`)
 *                               containing Buddhabrot rendering parameters.
 * @param  complex_point         The complex coordinate to test and trace.
 * @param  histogram_accumulator Pointer to the local histogram accumulator
 *                               (`t_bb_accum`) where contributions are stored.
 * @return 1 if the point contributed to the histogram, 0 otherwise.
 *
 * @note   Points escaping before the `bb_min_iter` threshold are ignored.
 * @pre    `fractal_params` and `histogram_accumulator` must be valid.
 * @post   Histogram accumulator is updated if the point contributes.
 */
static int	bb_trace_one_local(const t_fractal *fractal_params,
							t_complex complex_point,
							t_bb_accum *histogram_accumulator)
{
	int	escape_iterations;

	escape_iterations = bb_escape_iter(fractal_params, complex_point);
	if (escape_iterations < fractal_params->bb_min_iter)
		return (0);
	bb_orbit_accumulate(fractal_params, complex_point,
		escape_iterations, histogram_accumulator);
	return (1);
}

/**
 * @brief  Generate and process multiple Buddhabrot samples locally.
 *
 * Randomly generates `sample_count` complex coordinates within a predefined
 * region, rejects points inside the main cardioid or period-2 bulb, and
 * accumulates valid orbits into the provided local histogram accumulator.
 *
 * @param  fractal_params        Pointer to the fractal context (`t_fractal`)
 *                               containing Buddhabrot parameters.
 * @param  sample_count          Number of random samples to generate.
 * @param  random_seed           Pointer to the random number generator seed.
 * @param  histogram_accumulator Pointer to the local histogram accumulator
 *                               (`t_bb_accum`) where contributions are stored.
 * @return The number of samples that contributed to the histogram.
 *
 * @note   Uses `bb_rand_range()` to generate coordinates, 
 *         `bb_reject_cardioid_bulb()` to skip obvious interior points,
 *         and `bb_trace_one_local()` to process contributing samples.
 * @pre    All pointer arguments must be valid; `sample_count` must be > 0.
 * @post   The histogram accumulator contains contributions from
 *         successfully processed samples.
 */
int	bb_run_samples_local(t_fractal *fractal_params, int sample_count,
				unsigned int *random_seed, t_bb_accum *histogram_accumulator)
{
	int			current_sample_index;
	int			contributing_samples_count;
	double		candidate_real;
	double		candidate_imag;
	t_complex	candidate_point;

	current_sample_index = 0;
	contributing_samples_count = 0;
	while (current_sample_index < sample_count)
	{
		candidate_real = bb_rand_range(random_seed, -2.2, 1.2);
		candidate_imag = bb_rand_range(random_seed, -1.7, 1.7);
		if (!bb_reject_cardioid_bulb(candidate_real, candidate_imag))
		{
			candidate_point.real = candidate_real;
			candidate_point.imag = candidate_imag;
			contributing_samples_count += bb_trace_one_local(fractal_params,
					candidate_point, histogram_accumulator);
		}
		current_sample_index++;
	}
	return (contributing_samples_count);
}
