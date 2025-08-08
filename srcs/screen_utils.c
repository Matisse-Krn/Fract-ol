#include "fractol.h"

/*
 * Puts a pixel of a given color onto the image at specified coordinates.
 * 
 * @param data A pointer to the image structure.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color value to assign to the pixel.
*/
void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->px_ptr + (y * data->line_length
			+ x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	set_real_screen_size(t_fractal *f)
{
	if (f->fullscreen == TRUE)
	{
		f->img.height = f->img.full_height - (f->img.full_height / 17);
		f->img.width = f->img.full_width;
	}
	else
	{
		f->img.height = 1042;
		f->img.width = 1042;
	}
}
