/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/07 22:02:20 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/07 22:26:31 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

int	check_color_mode(char mode, t_fractal *fractal)
{
	if (mode == fractal->color_mode && mode == 'N') // si N demande et mode actuel = N -> RAS
		return (1);
	if (mode == fractal->color_mode || mode == 'N') // 
	{
		ft_putstr_fd("Initial color mode (black and white).\n", 1);
		fractal->color_min = fractal->init_color_min;
		fractal->color_max = fractal->init_color_max;
		fractal->color_mode = 'N';
		fractal_rendering(fractal);
		return (1);
	}
	return (0);
}

static void	change_color_mode_four(char mode, t_fractal *fractal)
{
	if (check_color_mode(mode, fractal))
		return ;
	else if (mode == 'C')
	{
		ft_putstr_fd("Cyan color mode.\n", 1);
		fractal->color_min = 0x000000;
		fractal->color_max = 0x00FFFF;
		fractal->color_mode = mode;
	}
/*	else if (mode == 'P')
	{
		ft_putstr_fd("Green color mode.\n", 1);
		fractal->color_min = 0x000000;
		fractal->color_max = 0xFF00FF;
		fractal->color_mode = mode;
	}
*/	else
	{
//		change_color_mode_four(mode, fractal);
		return ;
	}
	fractal_rendering(fractal);
}

static void	change_color_mode_three(char mode, t_fractal *fractal)
{
	if (check_color_mode(mode, fractal))
		return ;
	else if (mode == 'O')
	{
		ft_putstr_fd("Orange color mode.\n", 1);
		fractal->color_min = 0x000000;
		fractal->color_max = 0xFF8000;
		fractal->color_mode = mode;
	}
	else if (mode == 'P')
	{
		ft_putstr_fd("Pink color mode.\n", 1);
		fractal->color_min = 0x000000;
		fractal->color_max = 0xFF00FF;
		fractal->color_mode = mode;
	}
	else
	{
		change_color_mode_four(mode, fractal);
		return ;
	}
	fractal_rendering(fractal);
}

static void	change_color_mode_two(char mode, t_fractal *fractal)
{
	if (check_color_mode(mode, fractal))
		return ;
	else if (mode == 'R')
	{
		ft_putstr_fd("Red color mode.\n", 1);
		fractal->color_min = 0x000000;
		fractal->color_max = 0xFF0000;
		fractal->color_mode = mode;
	}
	else if (mode == 'G')
	{
		ft_putstr_fd("Green color mode.\n", 1);
		fractal->color_min = 0x000000;
		fractal->color_max = 0x00FF00;
		fractal->color_mode = mode;
	}
	else
	{
		change_color_mode_three(mode, fractal);
		return ;
	}
	fractal_rendering(fractal);
}

void	change_color_mode(char mode, t_fractal *fractal)
{
	if (check_color_mode(mode, fractal))
		return ;
	else if (mode == 'B')
	{
		ft_putstr_fd("Blue mode.\n", 1);
		fractal->color_min = 0x000000;
		fractal->color_max = 0x0000FF;
		fractal->color_mode = mode;
	}
	else if (mode == 'Y')
	{
		ft_putstr_fd("Yellow color mode.\n", 1);
		fractal->color_min = 0x000000;
		fractal->color_max = 0x999900;
		fractal->color_mode = mode;
	}
	else
	{
		change_color_mode_two(mode, fractal);
		return ;
	}
	fractal_rendering(fractal);
}


