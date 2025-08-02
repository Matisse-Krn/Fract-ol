#include "fractol.h"

/*
 * Initializes event handling for the Sierpiński Carpet fractal.
 * Sets up keyboard and window close event hooks.
 * 
 * @param fractal A pointer to the fractal structure.
 * 
 * Events:
	- `KeyPress` → Handles depth and color changes (`handle_key_sierpinski`).
	- `DestroyNotify` → Closes the window and exits (`handle_exit`).
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

/*
 * Draws a filled square at the specified coordinates.
 * The square size is determined by `fractal->size`.
 * 
 * @param x The x-coordinate of the starting point of the square.
 * @param y The y-coordinate of the starting point of the square.
 * @param fractal A pointer to the fractal structure.
 * 
 * Constraints:
	- If `size < 1`, the function does nothing.
	- Ensures the square stays within the image boundaries.
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

/*
 * Recursively generates the Sierpiński Carpet fractal.
 * Splits the current square into 9 smaller squares, removing the center one.
 * Calls draw_sierpinski_carpet() on the remaining 8 squares.
 * 
 * @param x The x-coordinate of the starting position for subdivision.
 * @param y The y-coordinate of the starting position for subdivision.
 * @param new_size The size of each new sub-square.
 * @param fractal A pointer to the fractal structure.
 * 
 * Process:
	- Calls itself recursively, decreasing `depth` at each level.
	- When depth reaches 0, stops recursion and fills the square.
	- Restores original `size` and `depth` after recursion.
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

/*
 * Initiates the recursive drawing process for the Sierpiński Carpet.
 * Calls draw_square() if the maximum recursion depth is reached.
 * Otherwise, calculates the new sub-square size and
	calls sierpinski_recursive().
 * 
 * @param x The x-coordinate of the starting position.
 * @param y The y-coordinate of the starting position.
 * @param fractal A pointer to the fractal structure.
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

/*
 * Renders the Sierpiński Carpet fractal.
 * Calls draw_sierpinski_carpet() to compute the fractal structure.
 * Updates the window with the new image.
 * 
 * @param fractal A pointer to the fractal structure.
*/
void	rendering_sierpinski(t_fractal *fractal)
{
	ft_printf("Rendering Sierpinski Carpet...\n\n");
	draw_sierpinski_carpet(0, 0, fractal);
	mlx_put_image_to_window(fractal->mlx_ptr, fractal->win_ptr, \
							fractal->img.img_ptr, 0, 0);
}
