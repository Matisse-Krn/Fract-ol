/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sierpinski_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 17:20:02 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/09 21:41:17 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Initializes the Sierpiński Carpet fractal parameters.
 * Determines the maximum possible depth based on the window size.
 * 
 * @param fractal A pointer to the fractal structure.
 * 
 * Constraints:
	- If the window is too small (< 3 pixels), the program exits.
	- The fractal size is set to the smallest image dimension.
	- `max_depth` is calculated using logarithmic scaling.
	- If no depth is provided, sets a default depth of 6 (if possible).
*/
void	data_init_sierpinski(t_fractal *fractal)
{
	if (fractal->img.width < 3 || fractal->img.height < 3)
	{
		ft_printf("Window size too small : exit program.\nSee ya' !\n");
		exit(EXIT_SUCCESS);
	}
	if (fractal->img.width > fractal->img.height)
		fractal->size = fractal->img.height;
	else
		fractal->size = fractal->img.width;
	ft_printf("Sierpinski Carpet size : %d*%d\n", fractal->size, fractal->size);
	fractal->max_depth = get_max_depth(fractal);
	if (!fractal->depth && fractal->max_depth >= 3)
		fractal->depth = 6;
	else if (fractal->max_depth < 3)
		fractal->depth = fractal->max_depth;
}

/*
 * Computes the maximum depth of recursion based on the image size.
 * Uses logarithmic division by 3 to determine how many recursive 
	levels fit in the available space.
 * 
 * @param fractal A pointer to the fractal structure.
 * @return The maximum allowable recursion depth.
*/
int	get_max_depth(t_fractal *fractal)
{
	int	min_size;

	if (fractal->img.width < fractal->img.height)
		min_size = fractal->img.width;
	else
		min_size = fractal->img.height;
	return ((int)(log(min_size) / log(3)));
}

/*
 * Changes the recursion depth for the Sierpiński Carpet fractal.
 * Adjusts `fractal->depth` based on the pressed key.
 * 
 * @param keysym The key pressed (`XK_0` to `XK_6`).
 * @param fractal A pointer to the fractal structure.
 * 
 * Constraints:
	- Cannot exceed `max_depth` (limited by window size).
	- If the requested depth is already set, does nothing.
	- If valid, updates the fractal and re-renders the image.
*/
void	change_depth_sierpinski(int keysym, t_fractal *fractal)
{
	if (keysym - '0' > fractal->max_depth || keysym - '0' == fractal->depth)
	{
		if (keysym - '0' > fractal->max_depth)
			ft_printf("Can't increase depth : window size too small !\nDepth \
max : %d\n\n", fractal->max_depth);
		return ;
	}
	ft_printf("Changing depth from [%d->", fractal->depth);
	if ((keysym == XK_0 || keysym == XK_1 || keysym == XK_2 || keysym == XK_3 \
		|| keysym == XK_4 || keysym == XK_5 || keysym == XK_6))
		fractal->depth = keysym - '0';
	ft_printf("%d]\n", fractal->depth);
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	initialize_image(fractal);
	rendering_sierpinski(fractal);
}

/*
 * Changes the color mode of the Sierpiński Carpet fractal.
 * Updates the color scheme based on user input.
 * 
 * @param keysym The key pressed
	(`XK_n, XK_r, XK_g, XK_b, XK_y, XK_o, XK_p, XK_c`).
 * @param fractal A pointer to the fractal structure.
 * 
 * Process:
	- If 'N' is requested and already active, no changes are made.
	- Calls change_color_mode() to apply the new color mode.
	- Re-renders the fractal with the updated color scheme.
*/
void	change_color_sierpinski(int keysym, t_fractal *fractal)
{
	if (keysym == XK_n && fractal->color_mode == 'N')
		return ;
	if (keysym == XK_n)
		change_color_mode('N', fractal);
	else if (keysym == XK_r)
		change_color_mode('R', fractal);
	else if (keysym == XK_g)
		change_color_mode('G', fractal);
	else if (keysym == XK_b)
		change_color_mode('B', fractal);
	else if (keysym == XK_y)
		change_color_mode('Y', fractal);
	else if (keysym == XK_o)
		change_color_mode('O', fractal);
	else if (keysym == XK_p)
		change_color_mode('P', fractal);
	else if (keysym == XK_c)
		change_color_mode('C', fractal);
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	initialize_image(fractal);
	rendering_sierpinski(fractal);
}
