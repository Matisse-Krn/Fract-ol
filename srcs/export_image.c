#include "fractol.h"
#include "stb_image_write.h"
#include <limits.h>

static char	*build_filename(t_fractal *f, int suffix)
{
	char	buffer[512];
	char	name_part[256];

	if (f->range_color_mode == 'Y')
	{
		snprintf(name_part, sizeof(name_part), "fractol_%s_x=%.5f_y=%.5f"
			"_z=%.5f_iter=%d_mode=%s_psy=on_color=%c", f->name, f->shift_x,
			f->shift_y, f->zoom_rate, f->max_iterations,
			get_render_mode_label(f->render_mode), f->color_mode);
	}
	else
	{
		snprintf(name_part, sizeof(name_part), "fractol_%s_x=%.5f_y=%.5f"
			"_z=%.5f_iter=%d_mode=%s_psy=off_color=%c", f->name, f->shift_x,
			f->shift_y, f->zoom_rate, f->max_iterations,
			get_render_mode_label(f->render_mode), f->color_mode);
	}
	if (suffix == 0)
		snprintf(buffer, sizeof(buffer), "exports/%s.png", name_part);
	else
		snprintf(buffer, sizeof(buffer), "exports/%s_%d.png", name_part, suffix);
	return (ft_strdup(buffer));
}

static char	*generate_export_filename(t_fractal *f)
{
	int		suffix;
	char	*filename;

	suffix = 0;
	if (!ft_strcmp("sierpinski", f->name))
		filename = build_sierpinski_filename(f, suffix);
	else
		filename = build_filename(f, suffix);
	if (!filename)
		return (NULL);
	while (access(filename, F_OK) == 0)
	{
		free(filename);
		suffix++;
		if (!ft_strcmp("sierpinski", f->name))
			filename = build_sierpinski_filename(f, suffix);
		else
			filename = build_filename(f, suffix);
		if (!filename)
			return (NULL);
	}
	return (filename);
}

static int	write_image_to_png(const char *name, t_image *img)
{
	unsigned char	*rgb;
	size_t			pixels;
	size_t			bytes;
	int				x;
	int				y;
	size_t			i;
	unsigned char	*px;

	if (!name || !img || !img->px_ptr)
		return (0);
	if (img->bits_per_pixel != 32)
		return (0);
	if (img->width <= 0 || img->height <= 0)
		return (0);
	pixels = (size_t)img->width * (size_t)img->height;
	if (img->width != 0 && pixels / (size_t)img->width != (size_t)img->height)
		return (0);
	if (pixels > SIZE_MAX / 3u)
		return (0);
	bytes = pixels * 3u;
	rgb = (unsigned char *)ft_calloc(bytes, 1);
	if (!rgb)
		malloc_error();
	i = 0;
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			px = (unsigned char *)img->px_ptr
				+ (size_t)y * (size_t)img->line_length
				+ (size_t)x * 4u;
			rgb[i++] = px[2];
			rgb[i++] = px[1];
			rgb[i++] = px[0];
		}
	}
	if (!stbi_write_png(name, img->width, img->height, 3, rgb, img->width * 3))
		return (free(rgb), ft_putstr_fd("Failed to write PNG file\n", 2), 0);
	return (free(rgb), 1);
}

static void	render_only_to_image(t_fractal *fractal)
{
	if (fractal->render_mode == 'A')
		compute_imax_for_export(fractal);
	if (fractal->mt == FALSE)
	{
		if (!ft_strcmp(fractal->name, "mandelbrot"))
			pixel_loop('M', fractal);
		else if (!ft_strcmp(fractal->name, "julia"))
			pixel_loop('J', fractal);
		else if (!ft_strcmp(fractal->name, "sierpinski"))
			draw_sierpinski_carpet(0, 0, fractal);
	}
	else
	{
		if (init_threads(fractal) == FALSE)
			return ;
	}
}

void	export_image(t_fractal *fractal)
{
	t_fractal			backup;
	t_image				export;
	char				*filename;
	t_img_snapshot		orig;

	if (!ensure_exports_dir())
	{
		ft_putstr_fd("Cannot create/open exports directory\n", 2);
		return ;
	}

	img_snapshot_take(&orig, &fractal->img);
	backup = duplicate_fractal(fractal);
	setup_export_image(&export, fractal);
	render_only_to_image(fractal);

	filename = generate_export_filename(fractal);
	if (!filename)
		malloc_error();

	(void)write_image_to_png(filename, &export);
	free(filename);
	mlx_destroy_image(fractal->mlx_ptr, export.img_ptr);
	restore_fractal(fractal, &backup, &orig);
	ft_putstr_fd("✅ Export OK (in './exports')\n", 1);
}

