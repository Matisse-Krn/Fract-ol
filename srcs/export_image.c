#include "fractol.h"
#include <sys/stat.h> // mkdir
#include <unistd.h>   // access
#include <fcntl.h>    // access macros
#include "stb_image_write.h" // à inclure une fois dans le fichier

static char	*build_filename(t_fractal *f, int suffix)
{
	char	*filename;
	char	buffer[512];
	char	name_part[256];

	if (f->range_color_mode == 'Y')
	{
		snprintf(name_part, sizeof(name_part), "fractol_%s_x=%.5f_y=%.5f"
			"_z=%.5f_iter=%d_mode=%s_psy=on_color=%c", f->name, f->shift_x,
			f->shift_y, f->zoom_rate, f->max_iterations,
			get_render_mode_label(f->render_mode), f->color_mode);
	}
	else if (f->range_color_mode == 'N')
	{
		snprintf(name_part, sizeof(name_part), "fractol_%s_x=%.5f_y=%.5f"
			"_z=%.5f_iter=%d_mode=%s_psy=off_color=%c", f->name, f->shift_x,
			f->shift_y, f->zoom_rate, f->max_iterations,
			get_render_mode_label(f->render_mode), f->color_mode);
	}
	if (suffix == 0)
		snprintf(buffer, sizeof(buffer), "exports/%s.png", name_part);
	else
		snprintf(buffer, sizeof(buffer), "exports/%s_%d.png", name_part,
			suffix);
	filename = ft_strdup(buffer);
	return (filename);
}

static char	*generate_export_filename(t_fractal *f)
{
	int		suffix;
	char	*filename;

	suffix = 0;
	if (!ft_strcmp("sierpinski", f->name))
	{
		ft_putstr_fd("DEBUG : Exporting sierpinski\n", 2);
		filename = build_sierpinski_filename(f, suffix);
	}
	else
	{
		ft_putstr_fd("DEBUG : Exporting julia or mandelbrot\n", 2);
		filename = build_filename(f, suffix);
	}
	while (access(filename, F_OK) == 0)
	{
		free(filename);
		suffix++;
		if (!ft_strcmp("sierpinski", f->name))
			filename = build_sierpinski_filename(f, suffix);
		else
			filename = build_filename(f, suffix);
	}
	return (filename);
}

static int	write_image_to_png(const char *name, t_image *img)
{
	unsigned char	*rgb;
	int				x;
	int				y;
	int				i;
	char			*px;

	rgb = ft_calloc(img->width * img->height, 3);
	if (!rgb)
		malloc_error();
	i = 0;
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			px = img->px_ptr + y * img->line_length + x * 4;
			rgb[i++] = (unsigned char)px[2];
			rgb[i++] = (unsigned char)px[1];
			rgb[i++] = (unsigned char)px[0];
		}
	}
	if (!stbi_write_png(name, img->width, img->height, 3, rgb, img->width * 3))
		return (free(rgb), ft_putstr_fd("❌ Failed to write PNG file\n", 2), 0);
	return (free(rgb), 1);
}

static void	render_only_to_image(t_fractal *fractal)
{
	if (fractal->render_mode == 'A')
		fractal->i_max = 0;
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
	t_fractal	backup;
	t_image		export;
	char		*filename;
	int			orig_iter;
	t_image		orig_img;

	mkdir("exports", 0777);
	orig_img = fractal->img;
	orig_iter = fractal->max_iterations;
	backup = duplicate_fractal(fractal);
	setup_export_image(&export, fractal);
	render_only_to_image(fractal);
	filename = generate_export_filename(fractal);
	if (!filename)
		malloc_error();
	if (write_image_to_png(filename, &export))
		ft_putstr_fd("✅ Export completed successfully !\n", 1);
	free(filename);
	restore_fractal(fractal, &backup, &orig_img);
	mlx_destroy_image(fractal->mlx_ptr, export.img_ptr);
}
