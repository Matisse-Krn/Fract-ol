/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 01:42:40 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/07 12:43:48 by mkerrien         ###   ########.fr       */
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
	* ✅Implementer Mandelbrot
	* ✅Implementer Julia
	* Implementer une autre fractale (bonus)
	* ✅ Ajouter les coordonnees du curseur de la souris sur la fenetre
	* Ajouter une string contenant les coordonnees initiales (parametres) pour Julia
	* Faire en sorte de pouvoir changer la palette de couleurs
	* Ajouter une text-box en bas avec les raccourcis pour interagir avec le programme
	* Retravailler Makefile 
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
		data_init(&fractal);
		if (!ft_strcmp(argv[1], "julia"))
		{
			fractal.c.real = ft_atod(argv[2]);
			fractal.c.imag = ft_atod(argv[3]);
		}
		initialize_window(&fractal);
		initialize_image(&fractal);
//		initialize_text_image(&fractal);
		initialize_events(&fractal);
		fractal_rendering(&fractal);
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
