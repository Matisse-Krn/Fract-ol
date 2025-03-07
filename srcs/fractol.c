/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:38:50 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/07 12:01:02 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Puts a pixel of a given color onto the image at specified coordinates.
 * 
 * @param data A pointer to the image structure.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @param color The color value to assign to the pixel.
*/
void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->px_ptr + (y * data->line_length
			+ x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

/*
 * Handles memory allocation failures by printing an error message
	and terminating the program.
*/
void	malloc_error(void)
{
	perror("Malloc ERROR...\n");
	exit(EXIT_FAILURE);
}

/*
 * Checks if a memory allocation was successful.
 * If allocation failed, calls malloc_error() to exit the program.
 * 
 * @param s A pointer to the allocated memory.
 * @return Returns the same pointer if allocation was successful.
*/
char	*if_malloc_error(char *s)
{
	if (!s)
		malloc_error();
	return (s);
}
