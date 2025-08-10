#include "fractol.h"

/**
 * @brief  Compute the divergence iteration for a Mandelbrot pixel.
 *
 * Maps the given pixel coordinates to the complex plane for the Mandelbrot
 * set and iterates the formula z = z² + c until the escape radius is reached
 * or the maximum number of iterations is hit. Returns the number of iterations
 * taken to diverge.
 *
 * @param  p  Pointer to the pixel coordinates (`t_pixel`).
 * @param  f  Pointer to the fractal context (`t_fractal`) containing zoom,
 *            shift, aspect ratio, and iteration parameters.
 * @return The number of iterations before divergence, or `max_iterations`
 *         if the point did not escape.
 *
 * @note   Used in both rendering and adaptive coloring calculations.
 * @pre    `p` must be inside the image bounds, and `f` must be initialized.
 * @post   No modifications are made to the fractal context.
 */
int	iters_to_diverge_mandelbrot(t_pixel *p, t_fractal *f)
{
	t_complex	z;
	t_complex	z2;
	t_complex	c;
	double		xr;
	int			i;

	z.real = 0;
	z.imag = 0;
	xr = (1.6 / f->zoom_rate) * f->aspect_ratio;
	c.real = scale_map(p->x, -xr, xr, f->img.width) + f->shift_x;
	c.imag = scale_map(p->y, 1.6 / f->zoom_rate,
			-1.6 / f->zoom_rate, f->img.height) + f->shift_y;
	i = -1;
	while (++i < f->max_iterations)
	{
		z2 = square_complex(z);
		z = sum_complex(z2, c);
		if ((z.real * z.real) + (z.imag * z.imag) > f->escape_value)
			return (i);
	}
	return (f->max_iterations);
}

/**
 * @brief  Compute the divergence iteration for a Julia set pixel.
 *
 * Initializes the complex coordinate from the pixel position for a Julia set,
 * then iterates the formula z = z² + c until the escape radius is reached
 * or the maximum iteration limit is reached.
 *
 * @param  p  Pointer to the pixel coordinates (`t_pixel`).
 * @param  f  Pointer to the fractal context (`t_fractal`) containing the
 *            Julia constant `c`, zoom, shift, and iteration parameters.
 * @return The number of iterations before divergence, or `max_iterations`
 *         if the point did not escape.
 *
 * @note   The complex constant `c` comes from `f->c` and remains fixed
 *         for all points in the Julia set.
 * @pre    `p` must be inside the image bounds, and `f` must be initialized.
 * @post   No modifications are made to the fractal context.
 */
int	iters_to_diverge_julia(t_pixel *p, t_fractal *f)
{
	t_complex	z;
	t_complex	z2;
	t_complex	c;
	int			i;

	z = julia_init_complex(p, f);
	c = f->c;
	i = -1;
	while (++i < f->max_iterations)
	{
		z2 = square_complex(z);
		z = sum_complex(z2, c);
		if ((z.real * z.real) + (z.imag * z.imag) > f->escape_value)
			return (i);
	}
	return (f->max_iterations);
}

/**
 * @brief  Determine the maximum divergence iteration in the current frame.
 *
 * Iterates over all pixels in the rendered image to find the highest number
 * of iterations before divergence among points that escape before reaching
 * `max_iterations`. This value is stored in `f->i_max`.
 *
 * @param  type  Fractal type: 'M' for Mandelbrot, otherwise Julia.
 * @param  f     Pointer to the fractal context (`t_fractal`) containing
 *               rendering parameters and image dimensions.
 * @return None.
 *
 * @note   Useful for adaptive or relative coloring based on per-frame
 *         iteration maxima.
 * @pre    `f` must be initialized with valid rendering parameters and
 *		   image size.
 * @post   `f->i_max` contains the highest divergence iteration found.
 */
void	find_imax_frame(char type, t_fractal *f)
{
	t_pixel	p;
	int		it;

	f->i_max = 0;
	p.y = -1;
	while (++(p.y) < f->img.height)
	{
		p.x = -1;
		while (++(p.x) < f->img.width)
		{
			if (type == 'M')
				it = iters_to_diverge_mandelbrot(&p, f);
			else
				it = iters_to_diverge_julia(&p, f);
			if (it < f->max_iterations && it > f->i_max)
				f->i_max = it;
		}
	}
}
