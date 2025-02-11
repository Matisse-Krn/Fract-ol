/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 01:42:40 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/04 15:11:55 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

/*
 *
 * Implementer Mandelbrot et Julia
 * Possibilite de zoomer "a l'infini" (mapping des touches '+' et '-')
 * Appuyer sur la croix de fenetre X stoppe le programme, sans leak
 * Appuyer sur ESC (echap) stoppe le programme, sans leak
 * Gerer les arguments 'mandelbrot' ou 'julia <real> <imaginary>'
 */


/*
	* Creer fonction `ft_atod()` pour convertir une char *str vers un double.
	* Implementer Julia
	* Implementer une autre fractale (bonus)
	* Limiter 'max_iterations' ?
	* 
	* 
	* Refaire les commentaires descriptifs de chaque fonction
	* 
*/

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if ((argc == 2 && !ft_strcmp(argv[1], "mandelbrot")) || (argc == 4
			&& !ft_strcmp(argv[1], "julia")))
	{
		fractal.name = argv[1];
		// 1) initialiser les variables de la mlx
		data_init(&fractal);
		if (!ft_strcmp(argv[1], "julia"))
		{
			fractal->c.real = 
		}
		initialize_window(&fractal);
		initialize_image(&fractal);
		initialize_events(&fractal);
		// 2) faire le rendu
		fractal_rendering(&fractal);
		// 3) mlx_loop
		mlx_loop(fractal.mlx_ptr);
	}
	else
	{
		ft_putstr_fd("Usage :\n\t'./fractol mandelbrot' or\n\
\t'./fractol julia <real> <imaginary>'\n", 1);
		return (1);
	}
	return (0);
}
