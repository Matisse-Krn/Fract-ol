#include "fractol.h"

static void	put_color_mode_label(t_fractal *f)
{
	put_a_string(5, 40, "Color :", f);
	if (f->color_mode == 'N')
		put_a_string(55, 40, "Normal", f);
	else if (f->color_mode == 'R')
		put_a_string(55, 40, "Red", f);
	else if (f->color_mode == 'G')
		put_a_string(55, 40, "Green", f);
	else if (f->color_mode == 'B')
		put_a_string(55, 40, "Blue", f);
	else if (f->color_mode == 'Y')
		put_a_string(55, 40, "Yellow", f);
	else if (f->color_mode == 'O')
		put_a_string(55, 40, "Orange", f);
	else if (f->color_mode == 'P')
		put_a_string(55, 40, "Pink", f);
	else if (f->color_mode == 'C')
		put_a_string(55, 40, "Cyan", f);
	else
		put_a_string(55, 40, "Unknown", f);
}

static void	manage_text_buddhabrot(t_fractal *f)
{
	draw_text_boxes(f);
	put_a_string(5, 10, "Buddhabrot", f);
	if (f->last_pos && f->last_pos[0] != '\0')
		put_a_string(5, 25, f->last_pos, f);
	print_shortcuts(f);
}

static void	manage_text_sierpinski(t_fractal *f)
{
	char	*depth;

	draw_text_boxes(f);
	put_a_string(5, 10, "Sierpinski Carpet", f);
	put_a_string(5, 25, "Depth :", f);
	depth = ft_itoa(f->depth);
	if_malloc_error(depth);
	put_a_string(70, 25, depth, f);
	free(depth);
	put_color_mode_label(f);
	print_shortcuts(f);
}

void	manage_text(t_fractal *fractal)
{
	if (fractal->exporting == TRUE)
		return ;
	if (!ft_strcmp(fractal->name, "buddhabrot"))
	{
		manage_text_buddhabrot(fractal);
		return ;
	}
	if (!ft_strcmp(fractal->name, "sierpinski"))
	{
		manage_text_sierpinski(fractal);
		return ;
	}
	draw_text_boxes(fractal);
	put_zoom_and_position(fractal);
	print_shortcuts(fractal);
	put_a_string(5, 25, fractal->last_pos, fractal);
	put_color_mode(fractal);
	put_render_mode(fractal);
	put_max_iterations(fractal);
}
