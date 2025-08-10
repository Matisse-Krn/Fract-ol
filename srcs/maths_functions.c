#include "fractol.h"

/**
 * @brief  Maps a value from one range to another.
 *
 * Converts the value `nb` from its original range [0, origin_max]
 * into a proportional value within the new range [new_min, new_max].
 *
 * @param  nb          The original value to be mapped.
 * @param  new_min     The lower bound of the target range.
 * @param  new_max     The upper bound of the target range.
 * @param  origin_max  The upper bound of the original range
 *					   (origin_min is assumed 0).
 * @return The mapped value in the target range.
 *
 * @note   This function assumes the original minimum value is always 0.
 * @warning Division by zero will occur if `origin_max` equals 0.
 * @pre    `origin_max` must be non-zero.
 * @post   Returns a proportional value within [new_min, new_max].
 */
double	scale_map(double nb, double new_min, double new_max, double origin_max)
{
	double	origin_min;

	origin_min = 0;
	return ((new_max - new_min) * (nb - origin_min) / \
	(origin_max - origin_min) + new_min);
}

/**
 * @brief  Adds two complex numbers.
 *
 * Computes the sum of two complex numbers `z` and `c`
 * and returns the resulting complex number.
 *
 * @param  z  First complex number.
 * @param  c  Second complex number.
 * @return The resulting complex number (z + c).
 *
 * @note   Both input values are passed by value, not by reference.
 * @pre    None.
 * @post   Returns the complex sum.
 */
t_complex	sum_complex(t_complex z, t_complex c)
{
	t_complex	res;

	res.real = z.real + c.real;
	res.imag = z.imag + c.imag;
	return (res);
}

/**
 * @brief  Squares a complex number.
 *
 * Computes the square of the complex number `z`
 * using the formula:  
 *    real = (a² - b²)  
 *    imag = 2ab
 *
 * @param  z  The complex number to be squared.
 * @return The resulting complex number (z²).
 *
 * @note   This operation is common in Mandelbrot and Julia set calculations.
 * @pre    None.
 * @post   Returns the squared complex number.
 */
t_complex	square_complex(t_complex z)
{
	t_complex	res;

	res.real = (z.real * z.real) - (z.imag * z.imag);
	res.imag = 2 * z.real * z.imag;
	return (res);
}

/**
 * @brief  Initializes a complex number for Julia set rendering.
 *
 * Converts the pixel coordinates into the corresponding complex
 * number in the Julia set's coordinate space, applying zoom,
 * aspect ratio correction, and positional shifts.
 *
 * @param  pixel     Pointer to the pixel structure (contains x and y).
 * @param  fractal   Pointer to the fractal structure containing
 *					 zoom, shift, and size.
 * @return The initialized complex number representing the pixel's position.
 *
 * @note   Uses `scale_map()` to transform pixel coordinates into
 *         the fractal's mathematical space.
 * @warning Requires a properly initialized `fractal` structure.
 * @pre    `pixel` and `fractal` must be valid pointers.
 * @post   Returns a complex number ready for Julia iteration.
 */
t_complex	julia_init_complex(t_pixel *pixel, t_fractal *fractal)
{
	t_complex	z;
	double		x_range;

	x_range = (1.6 / fractal->zoom_rate) * fractal->aspect_ratio;
	z.real = scale_map(pixel->x, -x_range, x_range, fractal->img.width)
		+ fractal->shift_x;
	z.imag = scale_map(pixel->y, 1.6 / fractal->zoom_rate,
			-1.6 / fractal->zoom_rate, fractal->img.height)
		+ fractal->shift_y;
	return (z);
}
