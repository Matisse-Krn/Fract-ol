/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:38:50 by mkerrien          #+#    #+#             */
/*   Updated: 2025/01/05 20:29:05 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "includes/fractol.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_square_borders(t_data img, int x, int y, int height, int width, int init_x, int init_y)
{
	int	side;

	side = 0;
	while (side < 4)
	{
		my_mlx_pixel_put(&img, x, y, 0x00FF0000);
		if (side == 0 && x < width + init_x - 1) // si on est sur la ligne superieure, et pas a la fin
			x++;
		else if (side == 1 && y < height + init_y - 1) // si on est sur la colonne droite, et pas a la fin
			y++;
		else if (side == 2 && x > init_x) // si on est sur la ligne inferieure, et pas a la fin
			x--;
		else if (side == 3 && y > init_y) // si on est sur la colonne gauche, et pas a la fin
			y--;
		else
			side++;
	}
}

void	draw_full_square(t_data img, int x, int y, int height, int width, int init_x, int init_y)
{
	while (y < height + init_y)
	{
		x = init_x;
		while (x < width + init_x)
			my_mlx_pixel_put(&img, x++, y, 0x00FF0000);
		y++;
	}
}

/*int	y_is_in_up_circle(int init_y, int radius, int x, int init_x)
{
	int	res;

	res = init_y + (sqrt(pow(radius, 2) - (pow(x - init_x, 2))));
	return (res);
}

int	y_is_in_down_circle(int init_y, int radius, int x, int init_x)
{
	int	res;

	res = init_y - (sqrt(pow(radius, 2) - (pow(x - init_x, 2))));
	return (res);
}
*/
void	my_draw_circle(t_data img, double x, double init_x, double init_y, int radius)
{
	double	y_up;
	double	y_down;

	my_mlx_pixel_put(&img, init_x, init_y, 0x00FF0000);
	x = init_x - radius;
	while (x <= init_x + radius)
	{
	//	printf("     x = %f\n", x);
		y_up = init_y + (sqrt(pow(radius, 2) - (pow(x - init_x, 2))));
	//	printf("  up y = %f\n", y_up);
		y_down = init_y - (sqrt(pow(radius, 2) - (pow(x - init_x, 2))));
	//	printf("down y = %f\n\n", y_down);
		my_mlx_pixel_put(&img, (int)x, (int)y_up, 0x00FF0000);
		my_mlx_pixel_put(&img, (int)x, (int)y_down, 0x00FF0000);
		x += 0.001;
	}
}

void	draw_circle_bresenham(t_data img, int init_x, int init_y, int *radius)
{
	int x = 0;
	int y = *radius;
	int decision = 3 - 2 * (*radius);

	// Dessiner les 8 octants pour un point donne
	while (x <= y)
	{
		// Dessiner les pixels symetriques
		my_mlx_pixel_put(&img, init_x + x, init_y + y, 0x00FF0000); // Octant 1
		my_mlx_pixel_put(&img, init_x - x, init_y + y, 0x00FF0000); // Octant 2
		my_mlx_pixel_put(&img, init_x + x, init_y - y, 0x00FF0000); // Octant 8
		my_mlx_pixel_put(&img, init_x - x, init_y - y, 0x00FF0000); // Octant 7
		my_mlx_pixel_put(&img, init_x + y, init_y + x, 0x00FF0000); // Octant 3
		my_mlx_pixel_put(&img, init_x - y, init_y + x, 0x00FF0000); // Octant 4
		my_mlx_pixel_put(&img, init_x + y, init_y - x, 0x00FF0000); // Octant 6
		my_mlx_pixel_put(&img, init_x - y, init_y - x, 0x00FF0000); // Octant 5

		// Mise a jour de la decision
		if (decision < 0)
			decision = decision + 4 * x + 6;
		else
		{
			decision = decision + 4 * (x - y) + 10;
			y--; // Decremente y si le point passe en diagonale
		}
		x++; // Incremente x a chaque etape
	}
}

void	draw_full_circle_bresenham(t_data img, int init_x, int init_y, int radius)
{
	int x = 0;
	int y = radius;
	int decision = 3 - 2 * radius;
	int	xi;

	// Dessiner les 8 octants pour un point donne
	while (x <= y)
	{
		// Dessiner les pixels symetriques
		xi = init_x - x;
		while (xi <= init_x + x)
		{
			my_mlx_pixel_put(&img, xi, init_y + y, 0x00FF0000); // Octant 1 et 2
			my_mlx_pixel_put(&img, xi, init_y - y, 0x00FF0000); // Octant 7 et 8
			xi++;
		}
		xi = init_x - y;
		while (xi <= init_x + y)
		{
			my_mlx_pixel_put(&img, xi, init_y + x, 0x00FF0000); // Octant 3 et 4
			my_mlx_pixel_put(&img, xi, init_y - x, 0x00FF0000); // Octant 5 et 6
			xi++;
		}

		// Mise a jour de la decision
		if (decision < 0)
			decision = decision + 4 * x + 6;
		else
		{
			decision = decision + 4 * (x - y) + 10;
			y--; // Decremente y si le point passe en diagonale
		}
		x++; // Incremente x a chaque etape
	}
}

int	zoom(int keycode, t_vars *vars)
{
	if (!vars->radius)
		return (1);
//	printf("vars: %p, vars->mlx: %p, vars->win: %p\n", vars, vars->mlx, vars->win);
	if (keycode == 65451 && vars->radius < 2147483647)
		(vars->radius)++;
	else if (keycode == 65453 && vars->radius > 1)
		(vars->radius)--;
	else
		return (1);
	printf("Keycode = %d\n", keycode);
	printf("New radius = %d\n", vars->radius);
	return (0);
}


int	ft_exit(int keycode, t_vars *vars)
{
	(void)keycode;
	if (vars->win)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		vars->win = NULL;
	}
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		vars->mlx = NULL;
	}
	printf("Exit the program.\n");
	exit (0);
}

int	main(void)
{
	t_data	img;
	t_vars	*vars;
	int		win_width;
	int		win_height;
	int		x;
	int		y;
	int		init_x;
	int		init_y;
	int		width;
	int		height;

	win_height = 500;
	win_width = 950;

	vars = malloc(sizeof(t_vars));
	if (!vars)
		return (1);
	vars->mlx = NULL;
	vars->win = NULL;
	vars->radius = 240;
	
	vars->mlx = mlx_init();
	if (!vars->mlx)
	{
		free(vars);
		return (1);
	}

	vars->win = mlx_new_window(vars->mlx, win_width, win_height, "Test, my first window");
	if (!vars->win)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		free(vars);
		return (1);
	}
	img.img_ptr = mlx_new_image(vars->mlx, win_width, win_height);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bits_per_pixel, &img.line_length, &img.endian);

	printf("line_length: %dbytes (%dpx), bits_per_pixel: %d\n", img.line_length, (img.line_length/(img.bits_per_pixel/8)), img.bits_per_pixel);	

	printf("main = vars: %p, vars->mlx: %p, vars->win: %p\n", vars, vars->mlx, vars->win);
	mlx_hook(vars->win, 17, 1L<<2, ft_exit, vars);
	mlx_hook(vars->win, 2, 1L<<0, zoom, vars);

	height = 40;
	width = 120;
	x = 475;
	y = 250;
	init_x = x;
	init_y = y;

/*//		  QUADRILATERES EQUIANGLES PLEINS
	if (init_x + width > win_width || init_y + height > win_height)
		return (1);
	draw_full_square(img, x, y, height, width, init_x, init_y);
*/


/*//		  QUADRILATERES EQUIANGLES CONTOURS ONLY
	if (init_x + width > win_width || init_y + height > win_height)
		return (1);
	draw_square_borders(img, x, y, height, width, init_x, init_y);
*/


//			CIRCLES CONTOURS ONLY
//	if (init_x + radius > win_width || init_x - radius < 0 || init_y + radius > win_height || init_y - radius < 0)
	//	return (1);
//	my_draw_circle(img, x, init_x, init_y, radius);*/
//	draw_circle_bresenham(img, init_x, init_y, radius);

	draw_full_circle_bresenham(img, init_x, init_y, vars->radius);
	mlx_put_image_to_window(vars->mlx, vars->win, img.img_ptr, 0, 0);
//	mlx_string_put(mlx_ptr, win_ptr, 0, 10, 0x00FFFFFF, "0");
	mlx_loop(vars->mlx);
	    if (vars->mlx)
        free(vars->mlx);
	free(vars);
	return (0);
}
