/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_hooks2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 23:16:50 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/08 02:06:24 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	handle_key_three(int keysym, t_fractal *fractal)
{
	printf("Handle key3 = %d\n", keysym);
	if (keysym == XK_space)
		swap_psy_mode(fractal);
//	else if (keysym == XK_equal)
//		change_contrast('+', fractal);
	else
	{
//		handle_key_three(keysym, fractal);
		return ;
	}
}
