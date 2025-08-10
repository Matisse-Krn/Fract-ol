#include "fractol.h"

/**
 * @brief  Perform linear interpolation between two color channel values.
 *
 * Computes the interpolated value between `start_value` and `end_value`
 * based on the given ratio. A ratio of 0.0 returns `start_value`,
 * 1.0 returns `end_value`, and values in between produce a weighted
 * average.
 *
 * @param  start_value  The starting channel value (0–255).
 * @param  end_value    The ending channel value (0–255).
 * @param  ratio        Interpolation factor between 0.0 and 1.0.
 * @return The interpolated channel value as an integer (0–255).
 *
 * @note   Used for red, green, or blue channels independently.
 * @pre    `ratio` should be clamped between 0.0 and 1.0 for expected results.
 * @post   Returned value is a valid 8-bit color channel intensity.
 */
static int	interpolate_channel_linear(int start_value,
									int end_value, double ratio)
{
	double	interpolated;

	interpolated = (1.0 - ratio)
		* (double)start_value + ratio * (double)end_value;
	return ((int)interpolated);
}

/**
 * @brief  Perform linear RGB interpolation between two colors.
 *
 * Separates the red, green, and blue channels of both colors,
 * interpolates each channel individually, and recombines them
 * into a single 24-bit RGB integer.
 *
 * @param  color_start  Starting RGB color (0xRRGGBB format).
 * @param  color_end    Ending RGB color (0xRRGGBB format).
 * @param  ratio        Interpolation factor between 0.0 and 1.0.
 * @return Interpolated RGB color as a 24-bit integer.
 *
 * @note   Uses `interpolate_channel_linear()` for each channel.
 * @pre    `ratio` should be clamped between 0.0 and 1.0 for expected results.
 * @post   Returned color is a valid RGB value.
 */
static int	interpolate_rgb_linear(int color_start, int color_end, double ratio)
{
	int	red;
	int	green;
	int	blue;

	red = interpolate_channel_linear((color_start >> 16) & 255,
			(color_end >> 16) & 255, ratio);
	green = interpolate_channel_linear((color_start >> 8) & 255,
			(color_end >> 8) & 255, ratio);
	blue = interpolate_channel_linear(color_start & 255,
			color_end & 255, ratio);
	return ((red << 16) | (green << 8) | blue);
}

/**
 * @brief  Generate a smooth 5-color gradient for Buddhabrot rendering.
 *
 * Maps a normalized value `t` in [0.0, 1.0] to a color by interpolating
 * between predefined colors at specific positions along the gradient.
 *
 * @param  t  Normalized position along the gradient (0.0–1.0).
 * @return Interpolated RGB color as a 24-bit integer.
 *
 * @note   Colors are defined at positions 0.00, 0.30, 0.55, 0.78, and 1.00.
 *         Values below 0.0 return the first color, values above 1.0 return
 *         the last color.
 * @pre    `t` should be clamped between 0.0 and 1.0 for normal operation,
 *         though the function handles out-of-range values.
 * @post   Returned color can be used directly for pixel rendering.
 */
int	bb_palette_ramp5(double t)
{
	static const double	positions[5] = {0.00, 0.30, 0.55, 0.78, 1.00};
	static const int	colors[5] = {
		0x08143C,
		0x1E3A8A,
		0x93C5FD,
		0xFBBF24,
		0xFFF1D6
	};
	int					segment_index;
	double				segment_ratio;

	if (t <= 0.0)
		return (colors[0]);
	if (t >= 1.0)
		return (colors[4]);
	segment_index = 0;
	while (segment_index < 4 && t > positions[segment_index + 1])
		segment_index++;
	segment_ratio = (t - positions[segment_index])
		/ (positions[segment_index + 1] - positions[segment_index]);
	return (interpolate_rgb_linear(colors[segment_index],
			colors[segment_index + 1], segment_ratio));
}
