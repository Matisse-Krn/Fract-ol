#include "fractol.h"

int	bb_alloc_histograms(t_fractal *f)
{
	int	count;

	count = f->img.width * f->img.height;

	f->bb_hist_r = NULL;
	f->bb_hist_g = NULL;
	f->bb_hist_b = NULL;

	f->bb_hist = ft_calloc(count, sizeof(uint32_t));
	if (!f->bb_hist)
	{
		malloc_error();
		return (0);
	}
	if (f->bb_nebula == 'Y')
	{
		f->bb_hist_r = ft_calloc(count, sizeof(uint32_t));
		if (!f->bb_hist_r)
			return (malloc_error(), free(f->bb_hist), f->bb_hist = NULL, 0);
		f->bb_hist_g = ft_calloc(count, sizeof(uint32_t));
		if (!f->bb_hist_g)
			return (malloc_error(), free(f->bb_hist), f->bb_hist = NULL,
				free(f->bb_hist_r), f->bb_hist_r = NULL, 0);
		f->bb_hist_b = ft_calloc(count, sizeof(uint32_t));
		if (!f->bb_hist_b)
			return (malloc_error(), free(f->bb_hist), f->bb_hist = NULL,
				free(f->bb_hist_r), f->bb_hist_r = NULL,
				free(f->bb_hist_g), f->bb_hist_g = NULL, 0);
	}
	return (1);
}

void	bb_reset_histograms(t_fractal *f)
{
	int	count;

	count = f->img.width * f->img.height;
	if (f->bb_hist)
		ft_bzero(f->bb_hist, sizeof(uint32_t) * count);
	if (f->bb_hist_r)
		ft_bzero(f->bb_hist_r, sizeof(uint32_t) * count);
	if (f->bb_hist_g)
		ft_bzero(f->bb_hist_g, sizeof(uint32_t) * count);
	if (f->bb_hist_b)
		ft_bzero(f->bb_hist_b, sizeof(uint32_t) * count);
	f->bb_samples_total = 0;
	f->bb_max_count = 1;
}

void	bb_free_histograms(t_fractal *f)
{
	if (!f)
		return ;
	if (f->bb_hist)
		free(f->bb_hist);
	f->bb_hist = NULL;
	if (f->bb_hist_r)
		free(f->bb_hist_r);
	f->bb_hist_r = NULL;
	if (f->bb_hist_g)
		free(f->bb_hist_g);
	f->bb_hist_g = NULL;
	if (f->bb_hist_b)
		free(f->bb_hist_b);
	f->bb_hist_b = NULL;
}

