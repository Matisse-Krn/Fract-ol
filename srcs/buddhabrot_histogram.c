#include "fractol.h"

/**
 * @brief  Reset a histogram buffer to zero.
 *
 * Sets all values in the given histogram array to zero over a specified
 * number of elements. Used to initialize or clear histogram data before
 * accumulation.
 *
 * @param  hist   Pointer to the histogram array.
 * @param  count  Number of elements in the histogram to reset.
 * @return None.
 *
 * @note   This function uses `ft_bzero()` for memory clearing.
 * @pre    `hist` must be a valid pointer to an allocated array.
 * @post   All `count` entries in `hist` are set to 0.
 */
void	bb_hist_zero(uint32_t *hist, int count)
{
	ft_bzero(hist, sizeof(uint32_t) * count);
}

/**
 * @brief  Calculate the visible coordinate bounds for the current view.
 *
 * Computes the minimum and maximum real (x) and imaginary (y) coordinates
 * visible in the current Buddhabrot view, based on zoom level, aspect
 * ratio, and viewport shifts.
 *
 * @param  f       Pointer to the fractal context containing view parameters.
 * @param  bounds  Pointer to a `t_bounds` structure to store the calculated
 *                 coordinate limits.
 * @return None.
 *
 * @note   The width is scaled by the aspect ratio, and both width and height
 *         are inversely proportional to `zoom_rate`.
 * @pre    `f` and `bounds` must be valid pointers.
 * @post   `bounds` contains updated min/max values for both x and y.
 */
static void	bb_view_bounds(const t_fractal *f, t_bounds *bounds)
{
	double	view_width;
	double	view_height;

	view_width = 1.6 * f->aspect_ratio / f->zoom_rate;
	view_height = 1.6 / f->zoom_rate;
	bounds->xmin = f->shift_x - (view_width * 0.5);
	bounds->xmax = f->shift_x + (view_width * 0.5);
	bounds->ymin = f->shift_y - (view_height * 0.5);
	bounds->ymax = f->shift_y + (view_height * 0.5);
}

/**
 * @brief  Convert world-space coordinates to screen-space pixel coordinates.
 *
 * Maps a given complex-plane coordinate (real and imaginary parts) to the
 * corresponding pixel position on the image, taking into account zoom,
 * aspect ratio, and viewport shift. Returns whether the coordinate lies
 * inside the visible viewport.
 *
 * @param  f         Pointer to the fractal context (`t_fractal`).
 * @param  x_real    Real part of the coordinate in world space.
 * @param  y_imag    Imaginary part of the coordinate in world space.
 * @param  screen    Pointer to a `t_pixel` structure to store the screen
 *                   coordinates if the point is visible.
 * @return 1 if the coordinate is within the visible area, 0 otherwise.
 *
 * @note   Relies on `bb_view_bounds()` to determine the visible world-space
 *         boundaries.
 * @pre    `screen` must be a valid pointer.
 * @post   If the return value is 1, `screen` contains valid pixel coordinates.
 */
int	bb_world_to_screen(const t_fractal *f, double x_real,
					double y_imag, t_pixel *screen)
{
	t_bounds	b;

	if (!screen)
		return (0);
	bb_view_bounds(f, &b);
	if (x_real < b.xmin || x_real > b.xmax
		|| y_imag < b.ymin || y_imag > b.ymax)
		return (0);
	screen->x = (int)((x_real - b.xmin)
			* (double)f->img.width / (b.xmax - b.xmin));
	screen->y = (int)((b.ymax - y_imag)
			* (double)f->img.height / (b.ymax - b.ymin));
	if (screen->x < 0 || screen->x >= f->img.width
		|| screen->y < 0 || screen->y >= f->img.height)
		return (0);
	return (1);
}

/**
 * @brief  Quickly reject points inside the main cardioid or period-2 bulb.
 *
 * Determines whether a point in the complex plane lies within the main
 * cardioid or the large period-2 bulb of the Mandelbrot set. If so, the
 * point can be skipped without iteration, improving performance.
 *
 * @param  real_c  Real part of the point's complex coordinate.
 * @param  imag_c  Imaginary part of the point's complex coordinate.
 * @return 1 if the point is inside either the cardioid or the bulb, 0 otherwise.
 *
 * @note   This optimization is standard in Mandelbrot/Buddhabrot rendering.
 * @pre    None.
 * @post   Return value indicates whether to skip iteration for the point.
 */
int	bb_reject_cardioid_bulb(double real_c, double imag_c)
{
	double	shifted_real;
	double	shifted_imag;
	double	distance;

	shifted_real = real_c - 0.25;
	shifted_imag = imag_c;
	distance = sqrt((shifted_real * shifted_real)
			+ (shifted_imag * shifted_imag));
	if (real_c <= distance - (2.0 * distance * distance) + 0.25)
		return (1);
	shifted_real = real_c + 1.0;
	shifted_imag = imag_c;
	if ((shifted_real * shifted_real) + (shifted_imag * shifted_imag) <= 0.0625)
		return (1);
	return (0);
}

/**
 * @brief  Merge a source histogram into a destination histogram.
 *
 * Adds the values from a source histogram into a destination histogram
 * bin by bin, updating the maximum bin value encountered in the process.
 *
 * @param  destination_histogram   Pointer to the destination histogram array.
 * @param  source_histogram        Pointer to the source histogram array.
 * @param  bin_count               Number of bins to process.
 * @param  current_max_bin_value   Pointer to the variable tracking
 *								   the maximum bin value.
 * @return None.
 *
 * @note   This is typically used to combine local histograms from multiple
 *         threads into a global histogram.
 * @pre    All pointers must be valid and `bin_count` must be positive.
 * @post   The destination histogram contains accumulated values, and
 *         `current_max_bin_value` is updated if a new maximum is found.
 */
void	bb_hist_merge(uint32_t *destination_histogram,
				uint32_t *source_histogram, int bin_count,
				uint32_t *current_max_bin_value)
{
	int			bin_index;
	uint32_t	bin_value;

	if (!destination_histogram || !source_histogram
		|| !current_max_bin_value || bin_count <= 0)
		return ;
	bin_index = -1;
	while (++bin_index < bin_count)
	{
		destination_histogram[bin_index] += source_histogram[bin_index];
		bin_value = destination_histogram[bin_index];
		if (bin_value > *current_max_bin_value)
			*current_max_bin_value = bin_value;
	}
}
