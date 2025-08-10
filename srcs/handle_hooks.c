#include "fractol.h"

/**
 * @brief  Clean up resources and exit the program.
 *
 * Frees all allocated histograms, destroys the MLX image, window,
 * and display, frees the MLX pointer, and releases the last stored
 * mouse position string if it exists. Prints a goodbye message and
 * terminates the program with `EXIT_SUCCESS`.
 *
 * @param  fractal  Pointer to the fractal context (`t_fractal`) to clean up.
 * @return Always returns 0 (unreachable since the function calls `exit()`).
 *
 * @note   This function is typically called when the user closes the
 *         program or presses the Escape key.
 * @pre    `fractal` must be initialized and contain valid MLX resources.
 * @post   The program terminates, releasing all allocated resources.
 */
int	handle_exit(t_fractal *fractal)
{
	bb_free_histograms(fractal);
	img_lock_destroy(&fractal->img);
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
	mlx_destroy_display(fractal->mlx_ptr);
	free(fractal->mlx_ptr);
	if (fractal->last_pos && fractal->last_pos[0] != '\0')
		free(fractal->last_pos);
	ft_printf("👋 Exiting the program. See ya' ! 👋\n");
	exit(EXIT_SUCCESS);
	return (0);
}

/**
 * @brief  Handle keyboard input for general fractal interactions.
 *
 * Responds to arrow keys for displacement, numeric keypad plus/minus
 * for changing iteration count, and delegates other keys to
 * `handle_key_two()` for color changes and additional features.
 *
 * @param  keysym   Key symbol from the X11 event.
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return Always returns 0.
 *
 * @note   Pressing Escape immediately triggers `handle_exit()`.
 * @pre    `fractal` must be initialized with valid rendering parameters.
 * @post   The fractal state may be updated, and the view re-rendered.
 */
int	handle_key(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		handle_exit(fractal);
	else if (keysym == XK_Left)
		displacement('L', fractal);
	else if (keysym == XK_Right)
		displacement('R', fractal);
	else if (keysym == XK_Up)
		displacement('U', fractal);
	else if (keysym == XK_Down)
		displacement('D', fractal);
	else if (keysym == XK_KP_Add)
		change_max_iterations('+', fractal);
	else if (keysym == XK_KP_Subtract)
		change_max_iterations('-', fractal);
	else
	{
		handle_key_two(keysym, fractal);
		return (0);
	}
	return (0);
}

/**
 * @brief  Handle keyboard input for color changes and secondary actions.
 *
 * Responds to specific lowercase letter keys to change the fractal's
 * color mode, or swaps colors when Tab is pressed. Delegates any
 * unrecognized keys to `handle_key_three()`.
 *
 * @param  keysym   Key symbol from the X11 event.
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   Uses `change_color_mode()` for predefined color modes.
 * @pre    `fractal` must be initialized with valid color parameters.
 * @post   The fractal colors may be updated, and the view re-rendered.
 */
void	handle_key_two(int keysym, t_fractal *fractal)
{
	if (keysym == XK_n)
		change_color_mode('N', fractal);
	else if (keysym == XK_r)
		change_color_mode('R', fractal);
	else if (keysym == XK_g)
		change_color_mode('G', fractal);
	else if (keysym == XK_b)
		change_color_mode('B', fractal);
	else if (keysym == XK_y)
		change_color_mode('Y', fractal);
	else if (keysym == XK_o)
		change_color_mode('O', fractal);
	else if (keysym == XK_p)
		change_color_mode('P', fractal);
	else if (keysym == XK_c)
		change_color_mode('C', fractal);
	else if (keysym == XK_Tab)
		swap_colors(fractal);
	else
	{
		handle_key_three(keysym, fractal);
		return ;
	}
}

/**
 * @brief  Handle mouse button actions for zoom control.
 *
 * Adjusts the fractal's zoom level when specific mouse buttons are pressed:
 * - Scroll down (Button5): zoom in moderately.
 * - Scroll up (Button4): zoom out moderately.
 * - Right click (Button3): zoom in strongly.
 * - Left click (Button1): zoom out strongly.
 *
 * @param  button   Mouse button identifier from the X11 event.
 * @param  x        X coordinate of the mouse pointer.
 * @param  y        Y coordinate of the mouse pointer.
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return Always returns 0.
 *
 * @note   Uses `apply_zoom()` to adjust zoom centered on the mouse position.
 * @pre    `fractal` must be initialized with valid rendering parameters.
 * @post   The zoom level and view position may be updated,
 *		   and the view re-rendered.
 */
int	handle_mouse(int button, int x, int y, t_fractal *fractal)
{
	if (button == Button5)
		apply_zoom(fractal, x, y, 0.8);
	else if (button == Button4)
		apply_zoom(fractal, x, y, 1.2);
	else if (button == Button3)
		apply_zoom(fractal, x, y, 0.2);
	else if (button == Button1)
		apply_zoom(fractal, x, y, 1.8);
	return (0);
}

/**
 * @brief  Handle mouse movement and update on-screen position display.
 *
 * Tracks the current mouse cursor coordinates, updates the stored
 * `last_pos` string in the fractal context, and triggers HUD update
 * to reflect the new position.
 *
 * @param  x        Current mouse X coordinate.
 * @param  y        Current mouse Y coordinate.
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return Always returns 0.
 *
 * @note   Frees and reallocates `last_pos` on each movement to
 *		   store the new position.
 * @pre    `fractal` must be initialized, and `manage_text()` must
 *		   handle HUD updates.
 * @post   The displayed mouse position in the window is updated.
 */
int	handle_mouse_move(int x, int y, t_fractal *fractal)
{
	char	*x_str;
	char	*y_str;
	char	*tmp;

	if (fractal->last_pos && fractal->last_pos[0] != '\0')
		free(fractal->last_pos);
	x_str = ft_itoa(x);
	if_malloc_error(x_str);
	y_str = ft_itoa(y);
	if_malloc_error(y_str);
	tmp = ft_strjoin("Mouse position : x = ", x_str);
	free(x_str);
	if_malloc_error(tmp);
	fractal->last_pos = ft_strjoin(tmp, "  y = ");
	free(tmp);
	if_malloc_error(fractal->last_pos);
	tmp = fractal->last_pos;
	fractal->last_pos = ft_strjoin(tmp, y_str);
	free(tmp);
	free(y_str);
	if_malloc_error(fractal->last_pos);
	manage_text(fractal);
	return (0);
}
