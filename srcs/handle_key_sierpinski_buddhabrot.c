#include "fractol.h"

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

int	handle_key_buddhabrot(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		handle_exit(fractal);
	else if (keysym == XK_e || keysym == XK_E)
	{
		ft_putstr_fd("Exporting image to PNG...\n", 1);
		if (!export_view_auto(fractal))
			ft_putstr_fd("❌ Export failed\n", 2);
		else
			ft_putstr_fd("✅ Export OK (in './exports')\n", 1);
	}
	else if (keysym == XK_H || keysym == XK_h)
		print_help();
	else
		return (FALSE);
	return (TRUE);
}
