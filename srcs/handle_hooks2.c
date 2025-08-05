#include "fractol.h"

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

static void	handle_key_four(int keysym, t_fractal *fractal)
{
	int			preset;
	static int	preset_need = FALSE;

	preset = -1;
	if (keysym == XK_J || keysym == XK_j)
		preset_need = jump_menu();
	if (preset_need == TRUE && keysym >= XK_1 && keysym <= XK_9)
		preset_need = handle_jump_choice(fractal, keysym - XK_0);
	else
		preset = keypad_to_preset(keysym);
	if (preset > 0 && preset <= 9)
		preset_need = handle_jump_choice(fractal, preset);
	else if (keysym == XK_e)
	{
		ft_putstr_fd("Exporting image to PNG...\n", 1);
		export_image(fractal);
	}
	else if (keysym == XK_s || keysym == XK_S)
		switch_palette_mode(fractal);

}

/*
 * Handles the last set of keyboard inputs for contrast changes,
	psychedelic mode toggling, and resetting the view.
 * 
 * @param keysym The key code of the pressed key.
 * @param fractal A pointer to the fractal structure.
 *
 * Keyboard shortcuts:
	- `Space` (XK_space) → Toggle psychedelic mode
	- `-` (XK_minus) → Decrease contrast
	- `=` (XK_equal) → Increase contrast
	- `Backspace` (XK_BackSpace) → Reset view
*/
void	handle_key_three(int keysym, t_fractal *fractal)
{
	if (keysym == XK_space)
		swap_psy_mode(fractal);
	else if (keysym == XK_minus)
		change_contrast('-', fractal);
	else if (keysym == XK_equal)
		change_contrast('+', fractal);
	else if (keysym == XK_BackSpace)
		reset_view(fractal);
	else
		handle_key_four(keysym, fractal);
}

/*
 * Handles keyboard inputs specific to the Sierpinski Carpet fractal.
 * Allows users to adjust depth and change colors.
 * 
 * @param keysym The key code of the pressed key.
 * @param fractal A pointer to the fractal structure.
 * @return Returns 0 if the key is handled, 1 otherwise.
 *
 * Sierpinski-specific keys:
	- `0-6` (XK_0 - XK_6) → Change depth
	- `N, R, G, B, Y, O, P, C` → Change colors
*/
int	handle_key_sierpinski(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		handle_exit(fractal);
	else if (keysym == XK_0 || keysym == XK_1 || keysym == XK_2 \
		|| keysym == XK_3 || keysym == XK_4 || keysym == XK_5 || keysym == XK_6)
		change_depth_sierpinski(keysym, fractal);
	if (keysym == XK_n || keysym == XK_r || keysym == XK_g || keysym == XK_b \
		|| keysym == XK_y || keysym == XK_o || keysym == XK_p || keysym == XK_c)
		change_color_sierpinski(keysym, fractal);
	else
		return (1);
	return (0);
}
