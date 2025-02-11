/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strings_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 10:51:06 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/07 12:42:40 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

void	print_shortcuts(t_fractal *fractal)
{	
	mlx_string_put(fractal->mlx_ptr, fractal->win_ptr,
		5, fractal->img.height - 20, 0xFFFFFF, "Scrool Up : zoom in     \
Scroll Down : zoom out     LClick : big zoom in     RClick : big zoom out");
}
