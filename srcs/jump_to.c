#include "fractol.h"

/**
 * @brief  Displays the Mandelbrot "jump-to" preset menu.
 *
 * Prints a numbered list of predefined coordinates (presets) for
 * exploring classic regions of the Mandelbrot set. This menu is only
 * relevant when the current fractal type is Mandelbrot.
 *
 * @return Always returns TRUE to indicate the menu was shown.
 *
 * @note   Each preset includes a descriptive name and its corresponding
 *         X/Y coordinates in the complex plane.
 * @pre    This function assumes the output stream is available.
 * @post   The preset menu is written to standard output.
 */
int	jump_menu(void)
{
	ft_putstr_fd("\n🌌 "BOLD"Jump-to Presets (Mandelbrot only)"RST"\n\n", 1);
	ft_putstr_fd("\t[1] Main Cardioid       → x = -0.6,	  	  y = 0.0\n", 1);
	ft_putstr_fd("\t[2] Seahorse Valley     → "
		"x = -0.745,		  y = 0.115\n", 1);
	ft_putstr_fd("\t[3] Elephant Valley     → "
		"x = 0.2847,		  y = -0.0118\n", 1);
	ft_putstr_fd("\t[4] Triple Spiral       → "
		"x = -0.7477,		  y = 0.1002\n", 1);
	ft_putstr_fd("\t[5] Tendrils (Neuron)   → "
		"x = -0.74364388703, y = 0.13182590421\n", 1);
	ft_putstr_fd("\t[6] Mandelbrot Fault	→ x = -0.093,		  "
		"y = 0.651\n", 1);
	ft_putstr_fd("\t[7] Period-3 Bulb       → x = -1.75,		  "
		"y = 0.0\n", 1);
	ft_putstr_fd("\t[8] Near the End        → "
		"x = -1.9075,		  y = -0.0002\n", 1);
	ft_putstr_fd("\t[9] Antennae            → "
		"x = -0.1745,		  y = 1.0206\n\n", 1);
	ft_putstr_fd("Press corresponding number key to jump.\n\n", 1);
	return (TRUE);
}

/**
 * @brief  Updates the fractal view position and zoom.
 *
 * Sets the horizontal/vertical shifts and zoom factor of the fractal
 * rendering context to the given values.
 *
 * @param  f     Pointer to the fractal context (`t_fractal`) to update.
 * @param  sx    New shift value along the X-axis.
 * @param  sy    New shift value along the Y-axis.
 * @param  zoom  New zoom factor to apply.
 *
 * @note   This function only updates the parameters — it does not
 *         trigger a re-render.
 * @pre    `f` must be a valid, initialized fractal structure.
 * @post   The fractal’s position and zoom settings are modified.
 */
static void	set_position(t_fractal *f, double sx, double sy, double zoom)
{
	f->shift_x = sx;
	f->shift_y = sy;
	f->zoom_rate = zoom;
}

/**
 * @brief  Handles selection of a Mandelbrot "jump-to" preset.
 *
 * If the current fractal is Mandelbrot, updates the view parameters
 * (shift and zoom) to match the chosen preset’s coordinates, then
 * triggers a re-render.
 *
 * @param  f       Pointer to the fractal context (`t_fractal`) to update.
 * @param  choice  Preset number selected (1–9).
 * @return FALSE if a valid jump was performed or the fractal type
 *         is not Mandelbrot; TRUE if the choice is invalid.
 *
 * @note   Prints confirmation of the jump to standard output.
 * @pre    `f` must be initialized and `choice` should be in the range 1–9.
 * @post   If valid, the fractal view is updated and re-rendered.
 */
int	handle_jump_choice(t_fractal *f, int choice)
{
	if (ft_strcmp(f->name, "mandelbrot"))
		return (FALSE);
	if (choice == 1)
		set_position(f, -0.6, 0.0, 1.6);
	else if (choice == 2)
		set_position(f, -0.745, 0.115, 500);
	else if (choice == 3)
		set_position(f, 0.2847, -0.0118, 500);
	else if (choice == 4)
		set_position(f, -0.7477, 0.1002, 1175);
	else if (choice == 5)
		set_position(f, -0.74364388703, 0.13182590421, 10000);
	else if (choice == 6)
		set_position(f, -0.093, 0.651, 215);
	else if (choice == 7)
		set_position(f, -1.75, 0.0, 15);
	else if (choice == 8)
		set_position(f, -1.9075, -0.0002, 230);
	else if (choice == 9)
		set_position(f, -0.1745, 1.0206, 180);
	else
		return (FALSE);
	ft_printf("✨ Jumped to preset [%d]\n", choice);
	fractal_rendering(f);
	return (FALSE);
}
