/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/09 19:17:49 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/09 22:02:41 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
 * Checks if the given string represents a valid numeric value.
 * Allows optional leading whitespace, a sign, and a single decimal separator.
 * 
 * @param str The string to validate.
 * @return Returns 0 if the string is a valid number, 1 otherwise.
 * @return If the string contains only a '-' or a '+' (or '-.', or '.-',...),
	it will be valid and interpreted as a 0.
*/
static int	is_valid_number(const char *str)
{
	int	has_digits;
	int	has_dot;

	if (!str)
		return (1);
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
		*str == '\r' || *str == '\f' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	has_digits = 0;
	has_dot = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			has_digits = 1;
		else if ((*str == '.' || *str == ',') && !has_dot)
			has_dot = 1;
		else
			return (1);
		str++;
	}
	return (0);
}

/*
 * Initializes the fractal structure for the Mandelbrot set and starts rendering.
 * Sets up the required resources and event handling for the display window.
 * 
 * @param argv The array of command-line arguments.
 * @param fractal A pointer to the fractal structure to store parsed data.
*/
void	init_mandelbrot(char **argv, t_fractal *fractal)
{
	ft_putstr_fd("Fractal type identified !\n", 1);
	ft_putstr_fd("Launching the program...\n", 1);
	ft_bzero(fractal, sizeof(t_fractal));
	fractal->name = argv[1];
	data_init(fractal);
	initialize_window(fractal);
	initialize_image(fractal);
	initialize_events(fractal);
	fractal_rendering(fractal);
	mlx_loop(fractal->mlx_ptr);
}

/*
 * Initializes the fractal structure for the Julia set and starts rendering.
 * Validates the complex number parameters provided by the user.
 * Exits the program if the inputs are invalid.
 * 
 * @param argv The array of command-line arguments.
 * @param fractal A pointer to the fractal structure to store parsed data.
*/
void	init_julia(char **argv, t_fractal *fractal)
{
	ft_putstr_fd("Fractal type identified !\n", 1);
	ft_putstr_fd("Launching the program...\n", 1);
	ft_bzero(fractal, sizeof(t_fractal));
	fractal->name = argv[1];
	if (is_valid_number(argv[2]))
	{
		ft_printf("\n'%s' is not a valid input...\nExit program\n\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	else if (is_valid_number(argv[3]))
	{
		ft_printf("\n'%s' is not a valid input...\nExit program\n\n", argv[3]);
		exit(EXIT_FAILURE);
	}
	fractal->c.real = ft_atod(argv[2]);
	fractal->c.imag = ft_atod(argv[3]);
	fractal->init_c_real = argv[2];
	fractal->init_c_imag = argv[3];
	data_init(fractal);
	initialize_window(fractal);
	initialize_image(fractal);
	initialize_events(fractal);
	fractal_rendering(fractal);
	mlx_loop(fractal->mlx_ptr);
}

/*
 * Initializes the fractal structure for the Sierpinski Carpet and
	starts rendering.
 * Uses the default depth value for the fractal if none is specified.
 * 
 * @param argv The array of command-line arguments.
 * @param fractal A pointer to the fractal structure to store parsed data.
*/
void	init_sierpinski(char **argv, t_fractal *fractal)
{
	ft_putstr_fd("Fractal type identified !\n", 1);
	ft_putstr_fd("Launching the program...\n", 1);
	ft_bzero(fractal, sizeof(t_fractal));
	fractal->name = argv[1];
	data_init(fractal);
	ft_printf("Max depth : %d\nDefault depth : %d\n",
		fractal->max_depth, fractal->depth);
	initialize_window(fractal);
	initialize_image(fractal);
	initialize_events(fractal);
	rendering_sierpinski(fractal);
	mlx_loop(fractal->mlx_ptr);
}

/*
 * Initializes the fractal structure for the Sierpinski Carpet with a
	user-defined depth.
 * Validates the provided depth value, applying default constraints if necessary.
 * 
 * @param argv The array of command-line arguments.
 * @param fractal A pointer to the fractal structure to store parsed data.
*/
void	init_sierpinski_depth(char **argv, t_fractal *fractal)
{
	ft_putstr_fd("Fractal type identified !\n", 1);
	ft_putstr_fd("Launching the program...\n", 1);
	ft_bzero(fractal, sizeof(t_fractal));
	fractal->name = argv[1];
	data_init(fractal);
	if (ft_strlen(argv[2]) == 1 && *argv[2] >= '0' && *argv[2] <= \
		fractal->max_depth + '0' && fractal->max_depth <= 9)
	{
		fractal->depth = ft_atoi(argv[2]);
		ft_printf("Max depth : %d\nChoosen depth : %d\n", fractal->max_depth, \
		fractal->depth);
	}
	else
	{
		ft_printf("%s is an invalid depth value for Sierpinski Carpet...\n\
Allowed values in a window of this size : [0-%d]\nValue applied to \
depth : %d\n", argv[2], fractal->max_depth, fractal->depth);
	}
	initialize_window(fractal);
	initialize_image(fractal);
	initialize_events(fractal);
	rendering_sierpinski(fractal);
	mlx_loop(fractal->mlx_ptr);
}
