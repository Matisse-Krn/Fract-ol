#include "fractol.h"

/**
 * @brief  Draws a filled rectangular box on the fractal image.
 *
 * Fills a rectangular region defined by the coordinates in `box`
 * with the specified color. The rectangle boundaries are clamped
 * to the image dimensions to avoid writing outside the image buffer.
 *
 * @param  box      Pointer to a t_box structure defining the rectangle bounds.
 * @param  fractal  Pointer to the fractal context containing image dimensions
 *                  and buffer information.
 * @param  color    The color (in 0xRRGGBB format) to fill the rectangle with.
 * @return None.
 *
 * @note   This function writes directly to the image pixel buffer using
 *         `my_mlx_pixel_put()`.
 * @pre    `box` coordinates must be initialized to a valid region.
 * @post   The specified rectangle area is filled with the given color.
 */
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

/**
 * @brief  Draws the background and separator for the shortcuts HUD area.
 *
 * Creates a black rectangle at the bottom of the window to serve as the
 * background for displaying keyboard and mouse shortcuts, with a white
 * horizontal separator above it.
 *
 * @param  f    Pointer to the fractal context containing image dimensions
 *              and buffer information.
 * @param  box  Pointer to a t_box structure used to define rectangle bounds.
 * @return None.
 *
 * @note   Uses `draw_a_box()` to render both the background and separator bar.
 * @pre    The `fractal->img` dimensions must be valid.
 * @post   The shortcuts HUD area is prepared for text rendering.
 */
static void	put_shortcuts_box(t_fractal *f, t_box *box)
{
	box->from_x = 0;
	box->from_y = f->img.height - 100;
	box->to_x = f->img.width;
	box->to_y = f->img.height;
	draw_a_box(box, f, 0x000000);
	box->from_x = 0;
	box->from_y = f->img.height - 100 - 5;
	box->to_y = f->img.height - 100;
	draw_a_box(box, f, 0xFFFFFF);
}

/**
 * @brief  Draws the background and separators for the live info HUD area.
 *
 * Creates a black rectangle in the top-left corner to serve as the
 * background for displaying live fractal information (zoom, position, etc.),
 * with white vertical and horizontal separators for visual clarity.
 *
 * @param  f    Pointer to the fractal context containing image dimensions
 *              and buffer information.
 * @param  box  Pointer to a t_box structure used to define rectangle bounds.
 * @return None.
 *
 * @note   Uses `draw_a_box()` multiple times to create the background
 *         and the separator lines.
 * @pre    The `fractal->img` dimensions must be valid.
 * @post   The live info HUD area is prepared for text rendering.
 */
static void	put_live_infos_box(t_fractal *f, t_box *box)
{
	box->from_x = 0;
	box->from_y = 0;
	box->to_x = 220;
	box->to_y = 90;
	draw_a_box(box, f, 0x000000);
	box->from_x = box->to_x - 5;
	box->from_y = 0;
	draw_a_box(box, f, 0xFFFFFF);
	box->from_x = 0;
	box->from_y = 90;
	box->to_y = 95;
	draw_a_box(box, f, 0xFFFFFF);
}

/**
 * @brief  Draws all HUD text background boxes for the fractal window.
 *
 * Calls helper functions to draw the live info box at the top-left
 * and the shortcuts box at the bottom of the window, then updates
 * the MLX window to display these elements.
 *
 * @param  fractal  Pointer to the fractal context containing MLX pointers
 *                  and image data.
 * @return None.
 *
 * @note   This function only draws the background rectangles; actual text
 *         is rendered separately.
 * @pre    The MLX window must be initialized and an image buffer created.
 * @post   HUD background areas are visible in the fractal window.
 */
void	draw_text_boxes(t_fractal *fractal)
{
	t_box	box;

	put_live_infos_box(fractal, &box);
	put_shortcuts_box(fractal, &box);
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr,
		fractal->img.img_ptr, 0, 0);
}
