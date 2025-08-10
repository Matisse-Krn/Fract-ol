#include "fractol.h"

/**
 * @brief  Map a numeric keypad keysym to a preset index.
 *
 * Converts specific X11 key symbols from the numeric keypad
 * (KP_0–KP_9) into corresponding preset numbers for fractal navigation.
 * Returns -1 if the key is not a recognized keypad digit.
 *
 * @param  keysym  Key symbol from the X11 event.
 * @return Preset index (0–9) if recognized, or -1 if invalid.
 *
 * @note   The mapping follows X11 keypad key codes (65429–65438).
 * @pre    None.
 * @post   No changes to program state.
 */
static int	keypad_to_preset(int keysym)
{
	if (keysym == 65436)
		return (1);
	if (keysym == 65433)
		return (2);
	if (keysym == 65435)
		return (3);
	if (keysym == 65430)
		return (4);
	if (keysym == 65437)
		return (5);
	if (keysym == 65432)
		return (6);
	if (keysym == 65429)
		return (7);
	if (keysym == 65431)
		return (8);
	if (keysym == 65434)
		return (9);
	if (keysym == 65438)
		return (0);
	return (-1);
}

/**
 * @brief  Handles specific keyboard events for fractal interactions.
 *
 * Processes advanced key bindings related to fractal presets, image exporting,
 * render mode switching, and help menu display. Supports both direct preset
 * selection and the interactive jump-to menu for Mandelbrot sets. Also triggers
 * PNG exports for supported fractal types.
 *
 * @param  keysym  The key code (from X11) representing the pressed key.
 * @param  f       Pointer to the current fractal structure containing all
 *                 rendering parameters and context.
 * @return None.
 *
 * @note   The function maintains a static flag (`preset_need`) to handle
 *         multi-step input for the jump-to menu. For Buddhabrot exports,
 *         `export_view_auto()` is used, while other fractals use `export_image()`.
 *         Only Mandelbrot supports the jump-to preset menu.
 *
 * @warning Passing an invalid `keysym` will have no effect, but
 *          exporting requires a valid and initialized `f->mlx_ptr` context.
 * @pre    The fractal rendering context (`f`) must be fully initialized
 *         before calling this function.
 * @post   Depending on the key pressed, the fractal display may be updated,
 *         a file may be exported, or console messages may be displayed.
 */
static void	handle_key_four(int keysym, t_fractal *f)
{
	int			preset;
	static int	preset_need = FALSE;

	preset = -1;
	if ((keysym == XK_J || keysym == XK_j) && !ft_strcmp(f->name, "mandelbrot"))
		preset_need = jump_menu();
	if (preset_need == TRUE && keysym >= XK_1 && keysym <= XK_9)
		preset_need = handle_jump_choice(f, keysym - XK_0);
	else
		preset = keypad_to_preset(keysym);
	if (preset > 0 && preset <= 9)
		preset_need = handle_jump_choice(f, preset);
	else if (keysym == XK_e || keysym == XK_E)
	{
		ft_putstr_fd("Exporting image to PNG...\n", 1);
		if (!ft_strcmp(f->name, "buddhabrot"))
		{
			if (!export_view_auto(f))
				ft_putstr_fd("❌ Export failed\n", 2);
			else
				ft_putstr_fd("✅ Export OK (view snapshot)\n", 1);
		}
		else
			export_image(f);
	}
	else if (keysym == XK_s || keysym == XK_S)
		switch_render_mode(f);
	else if (keysym == XK_H || keysym == XK_h)
		print_help();
}

/**
 * @brief  Handle tertiary keyboard inputs for rendering adjustments and jumps.
 *
 * Processes keys for:
 * - Switching range color mode (Space).
 * - Adjusting contrast ('-' / '=').
 * - Resetting the view (Backspace).
 * - Delegating other actions to `handle_key_four()`.
 *
 * @param  keysym    Key symbol from the X11 event.
 * @param  fractal   Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   Contrast changes affect the `contrast_exponent` parameter.
 * @pre    `fractal` must be initialized with valid rendering parameters.
 * @post   The fractal state or appearance may change and trigger re-rendering.
 */
void	handle_key_three(int keysym, t_fractal *fractal)
{
	if (keysym == XK_space)
		swap_range_color_mode(fractal);
	else if (keysym == XK_minus)
		change_contrast('-', fractal);
	else if (keysym == XK_equal)
		change_contrast('+', fractal);
	else if (keysym == XK_BackSpace)
		reset_view(fractal);
	else
		handle_key_four(keysym, fractal);
}

/**
 * @brief  Handle keyboard inputs specific to the Sierpinski fractal.
 *
 * Processes keys for:
 * - Exiting the program (Escape).
 * - Changing fractal depth (0–6).
 * - Changing fractal color mode ('n', 'r', 'g', 'b', 'y', 'o', 'p', 'c').
 * - Displaying help ('H'/'h').
 * - Exporting the current fractal view ('E'/'e').
 *
 * @param  keysym    Key symbol from the X11 event.
 * @param  fractal   Pointer to the fractal context (`t_fractal`).
 * @return 0 if the key was handled, 1 if unrecognized.
 *
 * @note   This function is only used when rendering the Sierpinski fractal.
 * @pre    `fractal` must be initialized for Sierpinski mode.
 * @post   The fractal state or appearance may be modified,
 *		   or an export may occur.
 */
int	handle_key_sierpinski(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		handle_exit(fractal);
	else if (keysym == XK_0 || keysym == XK_1 || keysym == XK_2
		|| keysym == XK_3 || keysym == XK_4 || keysym == XK_5 || keysym == XK_6)
		change_depth_sierpinski(keysym, fractal);
	else if (keysym == XK_n || keysym == XK_r || keysym == XK_g
		|| keysym == XK_b || keysym == XK_y || keysym == XK_o
		|| keysym == XK_p || keysym == XK_c)
		change_color_sierpinski(keysym, fractal);
	else if (keysym == XK_h || keysym == XK_H)
		print_help();
	else if (keysym == XK_e || keysym == XK_E)
		export_image(fractal);
	else
		return (1);
	return (0);
}
