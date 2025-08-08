#include "fractol.h"

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
