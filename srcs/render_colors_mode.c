#include "fractol.h"

/**
 * @brief  Cycles through and applies the next fractal render mode.
 *
 * Changes the fractal rendering mode in a fixed sequence:
 * Normal → Logarithmic → Adaptive → Fixed Log → Cyclic → Normal.
 * Each mode adjusts how iteration counts are mapped to colors.
 * The function also prints the newly selected mode and triggers
 * a full fractal re-render to reflect the change immediately.
 *
 * @param  f  Pointer to the fractal rendering context structure.
 * @return None.
 *
 * @note   This function is interactive and intended to be called in response
 *         to a keyboard shortcut (e.g., 'S' key). The change is applied
 *         instantly.
 * @warning Excessive re-rendering may impact performance for high-resolution
 *          or highly zoomed fractals.
 * @pre    `f` must be properly initialized with a valid render mode character.
 * @post   The fractal is redrawn using the newly selected render mode.
 */
void	switch_render_mode(t_fractal *f)
{
	if (f->render_mode == 'N')
		f->render_mode = 'L';
	else if (f->render_mode == 'L')
		f->render_mode = 'A';
	else if (f->render_mode == 'A')
		f->render_mode = 'F';
	else if (f->render_mode == 'F')
		f->render_mode = 'C';
	else
		f->render_mode = 'N';
	ft_putstr_fd("Render mode switched to : ", 1);
	if (f->render_mode == 'N')
		ft_putstr_fd("Normal (exponential)\n", 1);
	else if (f->render_mode == 'L')
		ft_putstr_fd("Logarithmic scale\n", 1);
	else if (f->render_mode == 'A')
		ft_putstr_fd("Adaptive (based on max i)\n", 1);
	else if (f->render_mode == 'F')
		ft_putstr_fd("Fixed log(i)/log(1000)\n", 1);
	else if (f->render_mode == 'C')
		ft_putstr_fd("Cyclic modulo color\n", 1);
	fractal_rendering(f);
}

/**
 * @brief  Retrieves the human-readable label for a render mode.
 *
 * Returns a string describing the rendering mode corresponding to
 * the provided mode character. This is mainly used for logging,
 * debugging, or generating filenames with descriptive metadata.
 *
 * @param  mode  Character code representing the render mode
 *               ('N', 'L', 'A', 'F', 'C').
 * @return Pointer to a constant string label describing the mode.
 *
 * @note   If the mode is unknown, the function returns "Unknown".
 * @warning The returned string is statically allocated and must
 *          not be freed or modified.
 * @pre    `mode` should be one of the defined render mode constants.
 * @post   No state is changed; only a descriptive string is returned.
 */
char	*get_render_mode_label(char mode)
{
	if (mode == 'N')
		return ("Normal");
	if (mode == 'L')
		return ("Logarithmic");
	if (mode == 'A')
		return ("Adaptive");
	if (mode == 'F')
		return ("Fixed_Log");
	if (mode == 'C')
		return ("Cyclic");
	return ("Unknown");
}
