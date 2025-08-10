#include "fractol.h"

/**
 * @brief  Writes a pixel of a given color into the image buffer.
 *
 * Calculates the exact memory address for the pixel located at coordinates
 * (x, y) in the image buffer, based on the line length and bits per pixel.
 * Writes the specified color value at that location in memory.
 *
 * @param  data   Pointer to the image structure containing buffer info.
 * @param  x      Horizontal coordinate of the pixel to set.
 * @param  y      Vertical coordinate of the pixel to set.
 * @param  color  Color value to assign to the pixel (in 0xRRGGBB format).
 * @return None.
 *
 * @note   This function directly modifies the image buffer in memory.
 * @pre    `data->px_ptr` must point to a valid image buffer allocated by MLX.
 * @post   The specified pixel in the image buffer is updated with the new color.
 */
void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->px_ptr + (y * data->line_length
			+ x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/**
 * @brief  Sets the actual image dimensions based on fullscreen mode.
 *
 * Adjusts the image's width and height according to whether fullscreen mode
 * is enabled. In fullscreen, the height is slightly reduced (by 1/17th) to
 * avoid potential overlaps with window decorations or OS interface elements.
 * In windowed mode, a fixed square resolution is used.
 *
 * @param  f  Pointer to the fractal context containing display parameters.
 * @return None.
 *
 * @note   Fullscreen dimensions are taken from `img.full_width` and
 *         `img.full_height` previously retrieved via MLX.
 * @pre    `f->fullscreen` must be correctly set before calling this function.
 * @post   `f->img.width` and `f->img.height` are updated accordingly.
 */
void	set_real_screen_size(t_fractal *f)
{
	if (f->fullscreen == TRUE)
	{
		f->img.height = f->img.full_height - (f->img.full_height / 17);
		f->img.width = f->img.full_width;
	}
	else
	{
		f->img.height = 1370;
		f->img.width = 1370;
	}
}
