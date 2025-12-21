#include "fractol.h"

static int	bb_export_make_tmp(t_fractal *f, t_image *tmp)
{
	int	w;
	int	h;

	w = f->img.width;
	h = f->img.height;
	ft_bzero(tmp, sizeof(t_image));
	tmp->width = w;
	tmp->height = h;
	tmp->img_ptr = mlx_new_image(f->mlx_ptr, w, h);
	if (!tmp->img_ptr)
		return (0);
	tmp->px_ptr = mlx_get_data_addr(tmp->img_ptr,
			&tmp->bits_per_pixel, &tmp->line_length, &tmp->endian);
	if (!tmp->px_ptr)
	{
		mlx_destroy_image(f->mlx_ptr, tmp->img_ptr);
		tmp->img_ptr = NULL;
		return (0);
	}
	return (1);
}

static void	bb_export_swap_in(t_fractal *f, t_img_snapshot *orig, t_image *tmp)
{
	img_snapshot_take(orig, &f->img);
	f->img.img_ptr = tmp->img_ptr;
	f->img.px_ptr = tmp->px_ptr;
	f->img.width = tmp->width;
	f->img.height = tmp->height;
	f->img.bits_per_pixel = tmp->bits_per_pixel;
	f->img.line_length = tmp->line_length;
	f->img.endian = tmp->endian;
}

static void	bb_export_restore(t_fractal *f, t_img_snapshot *orig, t_image *tmp)
{
	img_snapshot_apply(&f->img, orig);
	if (tmp->img_ptr)
		mlx_destroy_image(f->mlx_ptr, tmp->img_ptr);
	tmp->img_ptr = NULL;
	tmp->px_ptr = NULL;
}

static int	export_clean_buddhabrot_view(t_fractal *f, const char *filepath)
{
	t_img_snapshot	orig;
	t_image			tmp;
	int				ok;

	ok = 0;
	if (!bb_export_make_tmp(f, &tmp))
		return (0);
	bb_export_swap_in(f, &orig, &tmp);
	f->exporting = 1;
	bb_draw_from_histogram(f);
	ok = export_view_png(f, filepath);
	f->exporting = 0;
	bb_export_restore(f, &orig, &tmp);
	return (ok);
}

int	export_view_auto(t_fractal *f)
{
	char	*path;
	int		ok;

	ok = 0;
	path = NULL;
	if (!ensure_exports_dir())
		return (0);
	path = generate_view_export_filename(f);
	if (!path)
		return (0);
	ok = export_clean_buddhabrot_view(f, path);
	free(path);
	return (ok);
}
