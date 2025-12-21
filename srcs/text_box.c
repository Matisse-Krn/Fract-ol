#include "fractol.h"

void	draw_a_box(t_box *box, t_fractal *fractal, int color)
{
	int	init_y;

	init_y = box->from_y;
	box->from_x -= 1;
	while (++(box->from_x) < box->to_x && box->from_x < fractal->img.width)
	{
		box->from_y = init_y - 1;
		while (++(box->from_y) < box->to_y && box->from_y < fractal->img.height)
			my_mlx_pixel_put(&fractal->img, box->from_x, box->from_y, color);
	}
}

static void	draw_shortcuts_box(t_fractal *f, t_box *box, int height)
{
	int	sep;

	sep = 5;
	box->from_x = 0;
	box->from_y = f->img.height - height;
	box->to_x = f->img.width;
	box->to_y = f->img.height;
	draw_a_box(box, f, 0x000000);
	box->from_x = 0;
	box->from_y = f->img.height - height - sep;
	box->to_y = f->img.height - height;
	draw_a_box(box, f, 0xFFFFFF);
}

static void	draw_live_infos_box(t_fractal *f, t_box *box, int width, int height)
{
	int	sep;

	sep = 5;
	box->from_x = 0;
	box->from_y = 0;
	box->to_x = width;
	box->to_y = height - sep;
	draw_a_box(box, f, 0x000000);
	box->from_x = width - sep;
	box->from_y = 0;
	box->to_y = height - sep;
	draw_a_box(box, f, 0xFFFFFF);
	box->from_x = 0;
	box->from_y = height - sep;
	box->to_x = width;
	box->to_y = height;
	draw_a_box(box, f, 0xFFFFFF);
}

void	draw_text_boxes(t_fractal *fractal)
{
	t_box	box;
	int		live_w;
	int		live_h;
	int		shortcuts_h;

	live_w = 220;
	live_h = 95;
	shortcuts_h = 100;
	if (!ft_strcmp(fractal->name, "buddhabrot"))
	{
		live_w = 250;
		live_h = 40;
		shortcuts_h = 30;
	}
	else if (!ft_strcmp(fractal->name, "sierpinski"))
	{
		live_w = 220;
		live_h = 60;
		shortcuts_h = 70;
	}
	if (live_w > fractal->img.width)
		live_w = fractal->img.width;
	if (live_h > fractal->img.height)
		live_h = fractal->img.height;
	if (shortcuts_h > fractal->img.height)
		shortcuts_h = fractal->img.height;
	draw_live_infos_box(fractal, &box, live_w, live_h);
	draw_shortcuts_box(fractal, &box, shortcuts_h);
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr,
		fractal->img.img_ptr, 0, 0);
}
