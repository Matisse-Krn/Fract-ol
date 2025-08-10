#include "fractol.h"

void	present_frame(t_fractal *f)
{
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img.img_ptr, 0, 0);
	draw_text_boxes(f);
	manage_text(f);
}
