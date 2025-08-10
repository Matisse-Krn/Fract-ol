#include "fractol.h"
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

/**
 * @brief  Build a descriptive export filename for a fractal image.
 *
 * Creates a filename string containing fractal parameters such as type,
 * position, zoom, iteration count, render mode, psychedelic mode state,
 * and color mode. Optionally appends a numeric suffix if provided.
 *
 * @param  f       Pointer to the fractal context (`t_fractal`).
 * @param  suffix  Numeric suffix for filename uniqueness (0 = no suffix).
 * @return A newly allocated string containing the filename.
 *
 * @note   The returned string must be freed by the caller.
 * @pre    `f` must contain valid fractal parameters.
 * @post   The filename points to the `exports/` directory and ends with `.png`.
 */
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

/**
 * @brief  Generate a unique filename for fractal image export.
 *
 * Builds a descriptive filename based on fractal parameters and ensures
 * it does not overwrite existing files by incrementing a numeric suffix
 * until an unused filename is found.
 *
 * @param  f  Pointer to the fractal context (`t_fractal`).
 * @return A newly allocated string containing the unique filename.
 *
 * @note   Calls either `build_filename()` or `build_sierpinski_filename()`
 *         depending on the fractal type. The returned string must be freed
 *         by the caller.
 * @pre    `f` must contain valid fractal parameters.
 * @post   The returned filename does not conflict with existing files.
 */
static char	*generate_export_filename(t_fractal *f)
{
	int		suffix;
	char	*filename;

	suffix = 0;
	if (!ft_strcmp("sierpinski", f->name))
		filename = build_sierpinski_filename(f, suffix);
	else
		filename = build_filename(f, suffix);
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

/**
 * @brief  Write an image buffer to a PNG file.
 *
 * Converts the given `t_image` structure from BGRA to RGB format and writes
 * it to disk as a PNG file using `stbi_write_png()`.
 *
 * @param  name  Path to the output PNG file.
 * @param  img   Pointer to the image structure containing pixel data.
 * @return 1 on success, 0 on failure.
 *
 * @note   Allocates a temporary RGB buffer, which is freed after writing.
 * @pre    `img` must be initialized with valid pixel data.
 * @post   A PNG file is written to disk if successful.
 */
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

/**
 * @brief  Render the fractal only into the image buffer, without display.
 *
 * Performs fractal rendering directly into the off-screen image buffer,
 * without updating the window. Uses either single-threaded or multi-threaded
 * rendering depending on the fractal context settings.
 *
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   For adaptive render mode ('A'), computes `i_max` before rendering.
 * @pre    `fractal` must be initialized with valid parameters.
 * @post   The `fractal->img` buffer contains the rendered fractal image.
 */
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

/**
 * @brief  Export the current fractal view as a PNG image.
 *
 * Creates a high-resolution off-screen buffer, renders the fractal into it,
 * generates a unique filename based on fractal parameters, and saves the
 * result as a PNG file in the `exports/` directory. Restores the original
 * fractal context after export.
 *
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   Prints a success message on completion. Creates the `exports/`
 *         directory if it does not exist.
 * @pre    `fractal` must be initialized with valid rendering parameters.
 * @post   A PNG file is created on disk, and the fractal context is restored.
 */
void	export_image(t_fractal *fractal)
{
	t_fractal	backup;
	t_image		export;
	char		*filename;
	t_image		orig_img;

	mkdir("exports", 0777);
	orig_img = fractal->img;
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
	img_lock_destroy(&fractal->img);
	mlx_destroy_image(fractal->mlx_ptr, export.img_ptr);
}
