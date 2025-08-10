#include "fractol.h"

/**
 * @brief  Displays a string on the MLX window at given coordinates.
 *
 * Renders the given string `s` at position `(x, y)` within the fractal's
 * MLX window, using a white color. The function checks that the coordinates
 * are within the current image dimensions before drawing.
 *
 * @param  x        Horizontal position in pixels.
 * @param  y        Vertical position in pixels.
 * @param  s        Null-terminated string to display.
 * @param  fractal  Pointer to the fractal context containing MLX pointers
 *                  and image dimensions.
 * @return None.
 *
 * @note   Uses `mlx_string_put()` from the MLX library for rendering text.
 * @pre    `fractal->mlx_ptr` and `fractal->win_ptr` must be valid MLX objects.
 * @post   The string is rendered in the MLX window if coordinates are valid.
 */
void	put_a_string(int x, int y, char *s, t_fractal *fractal)
{
	if (fractal->img.height > y && fractal->img.width > x)
	{
		mlx_string_put(fractal->mlx_ptr, fractal->win_ptr,
			x, y, 0xFFFFFF, s);
	}
}

/**
 * @brief  Displays a list of keyboard and mouse shortcuts on-screen.
 *
 * Draws multiple lines of text describing user interaction shortcuts,
 * including zoom controls, color modes, rendering options, and other
 * available actions. The position of each line is anchored relative to
 * the bottom of the window.
 *
 * @param  fractal  Pointer to the fractal context containing image dimensions
 *                  and MLX pointers.
 * @return None.
 *
 * @note   Shortcuts are hardcoded and positioned with fixed offsets from the
 *         bottom of the window for consistency across resolutions.
 * @pre    The MLX window must be initialized and visible.
 * @post   Shortcut descriptions are rendered in the HUD area of the window.
 */
void	print_shortcuts(t_fractal *fractal)
{
	put_a_string(5, fractal->img.height - 82, "Scrool Up : zoom in       \
Scroll Down : zoom out       LClick : big zoom in       RClick : big zoom out\
       BackSpace : reset view\
       Space : psychedelic", fractal);
	put_a_string(5, fractal->img.height - 64, "+ (keypad) : increase definition"
		"       - (keypad) : reduce definition       + : smoothen       "
		"- : contrast       S : change render mode", fractal);
	put_a_string(5, fractal->img.height - 46, "E : export to PNG       "
		"J + [1-9] : jump-to preset (Mandelbrot)       "
		"H : help menu in terminal", fractal);
	put_a_string(5, fractal->img.height - 28, "COLORS :", fractal);
	put_a_string(5, fractal->img.height - 10, "N : Normal       R : Red       \
G : Green       B : Blue       Y : Yellow       O : Orange       P : Pink       \
C : Cyan    ||    TAB : reverse color mode", fractal);
}

/**
 * @brief  Displays the current fractal position on-screen.
 *
 * Converts the current horizontal (`shift_x`) and vertical (`shift_y`)
 * offsets of the fractal view into strings, formats them with a label,
 * and displays them on the MLX window.
 *
 * @param  f  Pointer to the fractal context containing position data and MLX
 *            pointers.
 * @return None.
 *
 * @note   Values are displayed with 4 decimal places of precision.
 * @warning Terminates the program via `if_malloc_error()` if a memory
 *          allocation fails during string construction.
 * @pre    The MLX window must be initialized.
 * @post   Position coordinates are rendered in the HUD area of the window.
 */
static void	put_position(t_fractal *f)
{
	char	*x_str;
	char	*y_str;
	char	*line;

	x_str = ft_dtoa(f->shift_x, 4);
	if_malloc_error(x_str);
	y_str = ft_dtoa(f->shift_y, 4);
	if_malloc_error(y_str);
	line = ft_strjoin("Position : ", x_str);
	free(x_str);
	if_malloc_error(line);
	line = str_append(line, ", ");
	if_malloc_error(line);
	line = str_append(line, y_str);
	free(y_str);
	if_malloc_error(line);
	put_a_string(5, 85, line, f);
	free(line);
}

/**
 * @brief  Displays the current zoom factor and position on-screen.
 *
 * Converts the current zoom factor into a string (with 2 decimal places),
 * formats it with a label, and displays it on the MLX window. Then calls
 * `put_position()` to display the view's coordinates.
 *
 * @param  f  Pointer to the fractal context containing zoom and position data.
 * @return None.
 *
 * @note   The zoom factor is prefixed with "Zoom : x" for clarity.
 * @warning Terminates the program via `if_malloc_error()` if memory allocation
 *          fails when building strings.
 * @pre    The MLX window must be initialized.
 * @post   Both the zoom factor and coordinates are displayed on-screen.
 */
void	put_zoom_and_position(t_fractal *f)
{
	char	*zoom;
	char	*line;

	zoom = ft_dtoa(f->zoom_rate, 2);
	if_malloc_error(zoom);
	line = ft_strjoin("Zoom : x", zoom);
	free(zoom);
	if_malloc_error(line);
	put_a_string(5, 70, line, f);
	free(line);
	put_position(f);
}

/**
 * @brief  Manages all HUD text rendering for the fractal viewer.
 *
 * Draws the on-screen heads-up display (HUD) by rendering:
 * - A background text box.
 * - The current zoom factor and position.
 * - Available keyboard/mouse shortcuts.
 * - The last saved position (if applicable).
 * - The current color mode and psychedelic mode status.
 * - The current render mode.
 * - The maximum iteration count.
 *
 * @param  fractal  Pointer to the fractal context containing rendering state,
 *                  MLX pointers, and HUD data.
 * @return None.
 *
 * @note   This function is called after the fractal image is drawn to
 *         overlay HUD information without affecting the fractal pixels.
 * @pre    The fractal image must already be rendered and ready for display.
 * @post   All HUD elements are rendered on top of the fractal in the window.
 */
void	manage_text(t_fractal *fractal)
{
	draw_text_boxes(fractal);
	put_zoom_and_position(fractal);
	print_shortcuts(fractal);
	put_a_string(5, 25, fractal->last_pos, fractal);
	put_color_mode(fractal);
	put_render_mode(fractal);
	put_max_iterations(fractal);
}
