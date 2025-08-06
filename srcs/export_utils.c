#include "fractol.h"

#include "fractol.h"

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
	copy.aspect_ratio = src->aspect_ratio;
	copy.escape_value = src->escape_value;
	copy.shift_x = src->shift_x;
	copy.shift_y = src->shift_y;
	copy.zoom_rate = src->zoom_rate;
	copy.init_shift_x = src->init_shift_x;
	copy.init_shift_y = src->init_shift_y;
	copy.init_zoom_rate = src->init_zoom_rate;
	copy.color_min = src->color_min;
	copy.color_max = src->color_max;
	copy.init_color_min = src->init_color_min;
	copy.init_color_max = src->init_color_max;
	copy.contrast_exponent = src->contrast_exponent;
	copy.c = src->c;
	copy.img.width = src->img.width;
	copy.img.height = src->img.height;
	copy.img.full_width = src->img.full_width;
	copy.img.full_height = src->img.full_height;
	// Ne surtout pas copier mlx_ptr / win_ptr / img_ptr / px_ptr !
	copy.mlx_ptr = NULL;
	copy.win_ptr = NULL;
	copy.img.img_ptr = NULL;
	copy.img.px_ptr = NULL;
	return (copy);
}

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
