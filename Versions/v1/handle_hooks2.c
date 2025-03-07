/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 23:16:50 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/09 21:46:17 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
		return ;
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
