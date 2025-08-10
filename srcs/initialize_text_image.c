#include "fractol.h"

void	initialize_text_image(t_fractal *f)
{
	f->hud.img_ptr = mlx_new_image(f->mlx_ptr, f->img.width, f->img.height);
	if (!f->hud.img_ptr)
		malloc_error();
	f->hud.px_ptr = mlx_get_data_addr(f->hud.img_ptr,
			&f->hud.bits_per_pixel, &f->hud.line_length, &f->hud.endian);
	if (!f->hud.px_ptr)
	{
		mlx_destroy_image(f->mlx_ptr, f->hud.img_ptr);
		malloc_error();
	}
}
