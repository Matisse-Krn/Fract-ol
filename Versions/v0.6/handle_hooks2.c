/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 23:16:50 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/09 03:32:58 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

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
