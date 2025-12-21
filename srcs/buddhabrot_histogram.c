
#include "fractol.h"
#include <stdint.h>

void	bb_hist_zero(uint32_t *hist, int count)
{
	if (!hist || count <= 0)
		return ;
	ft_bzero(hist, sizeof(uint32_t) * (size_t)count);
}

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

void	bb_hist_merge(uint32_t *destination_histogram,
				uint32_t *source_histogram, int bin_count,
				uint32_t *current_max_bin_value)
{
	int			bin_index;
	uint32_t	dst;
	uint32_t	src;
	uint64_t	sum;

	if (!destination_histogram || !source_histogram
		|| !current_max_bin_value || bin_count <= 0)
		return ;
	bin_index = -1;
	while (++bin_index < bin_count)
	{
		dst = destination_histogram[bin_index];
		src = source_histogram[bin_index];
		sum = (uint64_t)dst + (uint64_t)src;
		if (sum > (uint64_t)UINT32_MAX)
			destination_histogram[bin_index] = UINT32_MAX;
		else
			destination_histogram[bin_index] = (uint32_t)sum;
		if (destination_histogram[bin_index] > *current_max_bin_value)
			*current_max_bin_value = destination_histogram[bin_index];
	}
}
