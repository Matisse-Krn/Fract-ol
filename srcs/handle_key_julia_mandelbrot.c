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

static void	handle_key_julia_mandelbrot_four(int keysym, t_fractal *f)
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
static void	handle_key_julia_mandelbrot_three(int keysym, t_fractal *fractal)
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
		handle_key_julia_mandelbrot_four(keysym, fractal);
}

static void	handle_key_julia_mandelbrot_two(int keysym, t_fractal *fractal)
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
		handle_key_julia_mandelbrot_three(keysym, fractal);
		return ;
	}
}

int	handle_key_julia_mandelbrot(int keysym, t_fractal *fractal)
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
		handle_key_julia_mandelbrot_two(keysym, fractal);
	return (0);
}
