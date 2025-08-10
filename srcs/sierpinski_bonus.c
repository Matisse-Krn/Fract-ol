#include "fractol.h"

/**
 * @brief  Initializes event handling for the Sierpinski Carpet window.
 *
 * Sets up the MLX event hooks specific to the Sierpinski Carpet fractal,
 * enabling keyboard interaction and handling window close events.
 *
 * @param  fractal  Pointer to the fractal structure containing window info.
 * @return None.
 *
 * @note   Only two hooks are set here: key press events and the destroy
 *         notification event when the window is closed.
 * @pre    `fractal->win_ptr` must point to a valid MLX window.
 * @post   Event hooks are active and will call their respective handlers.
 */
void	initialize_events_sierpinski(t_fractal *fractal)
{
	mlx_hook(fractal->win_ptr,
		KeyPress,
		KeyPressMask,
		handle_key_sierpinski, fractal);
	mlx_hook(fractal->win_ptr,
		DestroyNotify,
		StructureNotifyMask,
		handle_exit, fractal);
}

/**
 * @brief  Draws a filled square on the image.
 *
 * Renders a solid-colored square starting at coordinates (x, y) with the
 * current `fractal->size` as both width and height, using the maximum color.
 *
 * @param  x        Top-left X coordinate of the square.
 * @param  y        Top-left Y coordinate of the square.
 * @param  fractal  Pointer to the fractal context containing size and color.
 * @return None.
 *
 * @note   This is a low-level pixel fill loop and may be called recursively
 *         in the Sierpinski rendering process.
 * @pre    `fractal->size` must be >= 1, otherwise nothing is drawn.
 * @post   The specified square area is filled in the image buffer.
 */
static void	draw_square(int x, int y, t_fractal *fractal)
{
	int	i;
	int	j;

	if (fractal->size < 1)
		return ;
	i = -1;
	while (++i < fractal->size)
	{
		j = -1;
		while (++j < fractal->size)
			my_mlx_pixel_put(&fractal->img, x + i, y + j, fractal->color_max);
	}
}

/**
 * @brief  Performs one recursive step of the Sierpinski Carpet construction.
 *
 * Iterates over a 3x3 grid, drawing smaller Sierpinski sub-squares in all
 * positions except the center. Adjusts the fractal size and depth for each
 * recursive call, then restores them after processing each sub-square.
 *
 * @param  x         X coordinate of the current top-left square.
 * @param  y         Y coordinate of the current top-left square.
 * @param  new_size  Size of the smaller squares to be drawn in this step.
 * @param  fractal   Pointer to the fractal context.
 * @return None.
 *
 * @note   The function modifies `fractal->size` and `fractal->depth` but
 *         restores them to their original values after recursion.
 * @pre    `new_size` should be > 0 to produce visible output.
 * @post   The carpet is partially drawn according to the recursion depth.
 */
static void	sierpinski_recursive(int x, int y, int new_size, t_fractal *fractal)
{
	int	i;
	int	j;
	int	original_size;
	int	original_depth;

	i = -1;
	while (++i < 3)
	{
		j = -1;
		while (++j < 3)
		{
			if (!(i == 1 && j == 1))
			{
				original_size = fractal->size;
				original_depth = fractal->depth;
				fractal->size = new_size;
				fractal->depth--;
				draw_sierpinski_carpet(x + i * new_size,
					y + j * new_size,
					fractal);
				fractal->size = original_size;
				fractal->depth = original_depth;
			}
		}
	}
}

/**
 * @brief  Draws the Sierpinski Carpet from a starting position.
 *
 * Depending on the current depth, either draws a filled square (depth = 0)
 * or recursively subdivides the area into smaller squares, omitting the center.
 *
 * @param  x        Top-left X coordinate to start drawing.
 * @param  y        Top-left Y coordinate to start drawing.
 * @param  fractal  Pointer to the fractal context containing depth and size.
 * @return None.
 *
 * @note   The base case (depth = 0) stops recursion and draws a filled square.
 * @pre    `fractal->depth` must be initialized before the call.
 * @post   The carpet or its sub-section is drawn into the image buffer.
 */
void	draw_sierpinski_carpet(int x, int y, t_fractal *fractal)
{
	int	new_size;

	if (fractal->depth == 0)
	{
		draw_square(x, y, fractal);
		return ;
	}
	new_size = fractal->size / 3;
	if (new_size < 1)
		new_size = 1;
	sierpinski_recursive(x, y, new_size, fractal);
}

/**
 * @brief  Renders the complete Sierpinski Carpet fractal to the window.
 *
 * Initiates the carpet drawing process starting from the top-left corner
 * and displays the final result in the MLX window.
 *
 * @param  fractal  Pointer to the fractal context containing MLX handles.
 * @return None.
 *
 * @note   The drawing is done in-memory before being pushed to the window.
 * @pre    MLX must be initialized, and `fractal->img` must be allocated.
 * @post   The Sierpinski Carpet is visible in the application window.
 */
void	rendering_sierpinski(t_fractal *fractal)
{
	ft_printf("Rendering Sierpinski Carpet...\n\n");
	draw_sierpinski_carpet(0, 0, fractal);
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr, \
							fractal->img.img_ptr, 0, 0);
}
