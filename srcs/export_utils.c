#include "fractol.h"

/**
 * @brief  Initialize an export image buffer for fractal rendering.
 *
 * Sets up an image buffer (`t_image`) for high-resolution export based on
 * the fractal's full resolution. For Sierpinski fractals, uses the current
 * window dimensions instead. Allocates the image via MLX, retrieves its
 * pixel data address, and updates the fractal's image and aspect ratio.
 *
 * @param  export    Pointer to the image structure to initialize.
 * @param  fractal   Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   On allocation failure, calls `malloc_error()` and terminates.
 * @pre    `fractal->mlx_ptr` must be valid and initialized.
 * @post   `export` and `fractal->img` are initialized for rendering.
 */
void	setup_export_image(t_image *export, t_fractal *fractal)
{
	export->width = fractal->img.full_width;
	export->height = fractal->img.full_height;
	if (!ft_strcmp("sierpinski", fractal->name))
	{
		export->width = fractal->img.width;
		export->height = fractal->img.height;
	}
	export->img_ptr = mlx_new_image(fractal->mlx_ptr,
			export->width, export->height);
	if (!export->img_ptr)
		malloc_error();
	export->px_ptr = mlx_get_data_addr(export->img_ptr,
			&export->bits_per_pixel,
			&export->line_length,
			&export->endian);
	if (!export->px_ptr)
		malloc_error();
	fractal->img = *export;
	fractal->aspect_ratio = (double)fractal->img.width
		/ (double)fractal->img.height;
}

/**
 * @brief  Copy selected fractal parameters into another structure (part 2).
 *
 * Helper function for `duplicate_fractal()` that copies rendering, color,
 * geometry, and image size parameters from a source fractal to a copy.
 *
 * @param  src   Pointer to the source fractal context.
 * @param  copy  Pointer to the destination fractal structure to fill.
 * @return None.
 *
 * @note   Does not copy MLX pointers or image pixel data.
 * @pre    `src` and `copy` must be valid pointers.
 * @post   The `copy` structure contains cloned rendering parameters.
 */
static void	duplicate_fractal2(t_fractal *src, t_fractal *copy)
{
	copy->aspect_ratio = src->aspect_ratio;
	copy->escape_value = src->escape_value;
	copy->shift_x = src->shift_x;
	copy->shift_y = src->shift_y;
	copy->zoom_rate = src->zoom_rate;
	copy->init_shift_x = src->init_shift_x;
	copy->init_shift_y = src->init_shift_y;
	copy->init_zoom_rate = src->init_zoom_rate;
	copy->color_min = src->color_min;
	copy->color_max = src->color_max;
	copy->init_color_min = src->init_color_min;
	copy->init_color_max = src->init_color_max;
	copy->contrast_exponent = src->contrast_exponent;
	copy->c = src->c;
	copy->img.width = src->img.width;
	copy->img.height = src->img.height;
	copy->img.full_width = src->img.full_width;
	copy->img.full_height = src->img.full_height;
	copy->mlx_ptr = NULL;
	copy->win_ptr = NULL;
	copy->img.img_ptr = NULL;
	copy->img.px_ptr = NULL;
}

/**
 * @brief  Create a duplicate of a fractal context.
 *
 * Produces a shallow copy of most fractal parameters so that rendering
 * state can be restored later. Image and MLX pointers are not duplicated.
 *
 * @param  src  Pointer to the source fractal context.
 * @return A `t_fractal` structure containing the copied data.
 *
 * @note   Uses `duplicate_fractal2()` to copy geometry and image size data.
 * @pre    `src` must be initialized with valid fractal parameters.
 * @post   The returned copy can be used to restore the fractal state.
 */
t_fractal	duplicate_fractal(t_fractal *src)
{
	t_fractal	copy;

	ft_bzero(&copy, sizeof(t_fractal));
	copy.name = src->name;
	copy.init_c_real = src->init_c_real;
	copy.init_c_imag = src->init_c_imag;
	copy.last_pos = src->last_pos;
	copy.color_mode = src->color_mode;
	copy.range_color_mode = src->range_color_mode;
	copy.render_mode = src->render_mode;
	copy.max_iterations = src->max_iterations;
	copy.i_max = src->i_max;
	copy.tick_iterations = src->tick_iterations;
	copy.color = src->color;
	copy.depth = src->depth;
	copy.max_depth = src->max_depth;
	copy.size = src->size;
	copy.fullscreen = src->fullscreen;
	copy.mt = src->mt;
	duplicate_fractal2(src, &copy);
	return (copy);
}

/**
 * @brief  Restore fractal state from a backup after export.
 *
 * Replaces the fractal's rendering parameters and image buffer with those
 * stored in a backup and the original image reference.
 *
 * @param  f         Pointer to the fractal context to restore.
 * @param  backup    Pointer to the backup fractal containing saved parameters.
 * @param  orig_img  Pointer to the original image structure to restore.
 * @return None.
 *
 * @note   Typically used after an export to restore the fractal's
 *		   on-screen state.
 * @pre    `backup` and `orig_img` must be initialized with valid data.
 * @post   `f` matches the rendering state prior to export.
 */
void	restore_fractal(t_fractal *f, t_fractal *backup, t_image *orig_img)
{
	f->max_iterations = backup->max_iterations;
	f->i_max = backup->i_max;
	f->color = backup->color;
	f->color_min = backup->color_min;
	f->color_max = backup->color_max;
	f->render_mode = backup->render_mode;
	f->range_color_mode = backup->range_color_mode;
	f->aspect_ratio = (double)orig_img->width / (double)orig_img->height;
	f->img = *orig_img;
}

/**
 * @brief  Build a descriptive export filename for a Sierpinski fractal.
 *
 * Creates a filename string containing the fractal's type, resolution,
 * depth, and color mode. Optionally appends a numeric suffix for uniqueness.
 *
 * @param  f       Pointer to the fractal context (`t_fractal`).
 * @param  suffix  Numeric suffix for filename uniqueness (0 = no suffix).
 * @return A newly allocated string containing the filename.
 *
 * @note   The returned string must be freed by the caller.
 * @pre    `f` must contain valid fractal parameters.
 * @post   The filename points to the `exports/` directory and ends with `.png`.
 */
char	*build_sierpinski_filename(t_fractal *f, int suffix)
{
	char	*filename;
	char	buffer[512];
	char	name_part[256];

	snprintf(name_part, sizeof(name_part), "fractol_%s_%dx%d_depth=%d_color=%c",
		f->name, f->img.width, f->img.height, f->depth, f->color_mode);
	if (suffix == 0)
		snprintf(buffer, sizeof(buffer), "exports/%s.png", name_part);
	else
		snprintf(buffer, sizeof(buffer), "exports/%s_%d.png", name_part,
			suffix);
	filename = ft_strdup(buffer);
	return (filename);
}
