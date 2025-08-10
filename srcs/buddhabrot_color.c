#include "fractol.h"

/**
 * @brief  Clamp a floating-point value between 0.0 and 1.0.
 *
 * Ensures that the given value stays within the normalized range [0, 1].
 * If the value is below 0.0, it returns 0.0. If it is above 1.0, it
 * returns 1.0. Otherwise, the original value is returned unchanged.
 *
 * @param  value  The input floating-point value to clamp.
 * @return The clamped value between 0.0 and 1.0.
 *
 * @note   Useful for normalizing data or avoiding overflow in functions
 *         that require a strictly bounded range.
 * @pre    None.
 * @post   Returned value is guaranteed to be within [0, 1].
 */
static double	clamp_between_0_and_1(double value)
{
	if (value < 0.0)
		return (0.0);
	if (value > 1.0)
		return (1.0);
	return (value);
}

/**
 * @brief  Compute a soft threshold based on the maximum iteration count.
 *
 * Calculates a threshold value that scales proportionally with the
 * iteration maximum, ensuring smoother transitions in normalization
 * processes. A base offset is added to prevent excessively low
 * threshold values.
 *
 * @param  iteration_max  The maximum number of iterations for the
 *                        fractal rendering.
 * @return The computed soft threshold value.
 *
 * @note   The minimum threshold returned is always 8.0.
 * @pre    `iteration_max` should be greater than or equal to 0.
 * @post   The returned threshold is used for iterative value
 *         normalization.
 */
static double	compute_soft_threshold(uint32_t iteration_max)
{
	double	soft_threshold;

	soft_threshold = (double)iteration_max * 0.08 + 8.0;
	if (soft_threshold < 8.0)
		soft_threshold = 8.0;
	return (soft_threshold);
}

/**
 * @brief  Apply a soft knee curve to a normalized value.
 *
 * Modifies the input value to compress its high-end range, producing
 * smoother visual transitions. This is done by applying a knee curve
 * that starts at a defined position and gradually compresses values
 * beyond it.
 *
 * @param  normalized_value  A value in the [0, 1] range to be adjusted.
 * @return The adjusted value after applying the soft knee curve.
 *
 * @note   The knee position defines where compression begins (0.92),
 *         and the knee strength (0.5) controls the compression rate.
 * @pre    The input should be a normalized value between 0 and 1.
 * @post   The output remains within the [0, 1] range.
 */
static double	apply_soft_knee(double normalized_value)
{
	double	knee_position;
	double	knee_strength;
	double	normalized_above_knee;

	knee_position = 0.92;
	knee_strength = 0.5;
	if (normalized_value > knee_position)
	{
		normalized_above_knee = (normalized_value - knee_position)
			/ (1.0 - knee_position);
		normalized_value = knee_position + (1.0 - knee_position)
			* (normalized_above_knee
				/ (1.0 + knee_strength * normalized_above_knee));
	}
	return (normalized_value);
}

/**
 * @brief  Normalize the iteration count to a [0, 1] range with smoothing.
 *
 * Converts the iteration count for a given pixel into a normalized
 * value using a soft threshold, soft knee curve, and gamma correction.
 * This produces a visually pleasing distribution of brightness values
 * for Buddhabrot rendering.
 *
 * @param  iteration_count  The number of iterations taken before escape.
 * @param  iteration_max    The maximum number of iterations possible.
 * @param  fractal          Pointer to the fractal context (`t_fractal`).
 *                          Currently unused in this function.
 * @return A normalized floating-point value between 0.0 and 1.0.
 *
 * @note   Uses `compute_soft_threshold()` to adapt to different
 *         iteration ranges, `apply_soft_knee()` for smoother highlights,
 *         and gamma correction (1.15) to adjust brightness perception.
 * @pre    `iteration_max` must be greater than 0.
 * @post   The output can be safely used for color mapping.
 */
double	bb_normalize_iteration_count(uint32_t iteration_count,
								uint32_t iteration_max, t_fractal *fractal)
{
	double	soft_threshold;
	double	exponential_factor;
	double	normalized_value;
	double	gamma_correction;

	(void)fractal;
	if (iteration_max < 1)
		return (0.0);
	soft_threshold = compute_soft_threshold(iteration_max);
	exponential_factor = 0.85;
	normalized_value = (exponential_factor * (double)iteration_count)
		/ (soft_threshold + exponential_factor * (double)iteration_count);
	normalized_value = apply_soft_knee(normalized_value);
	gamma_correction = 1.15;
	normalized_value = clamp_between_0_and_1(normalized_value);
	return (pow(normalized_value, gamma_correction));
}
