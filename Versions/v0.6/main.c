/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 01:42:40 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/09 07:07:11 by mkerrien         ###   ########.fr       */
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
	* Handle hooks pour sierpinski
		* entrer la depth en parametre ?
		* modifier la depth
		* switch color
	* Ajouter definition de 'fractale' sur le terminal dans le cas de sierpinski (argument correction :p)
	* ✅ Afficher les coordonnees du curseur de la souris sur la fenetre
	* ✅ Afficher le mode de couleurs actuellement selectionne + psy ou non ?
	* ✅ Afficher les coordonnees initiales (parametres) pour Julia
	* ✅ Ecrire dans le terminal a CHAQUE action
	* Ajouter des 'alias' dans le programme afin de proposer des parametres
		predefinis pour Julia
	* Rediger man pour explications alias et autres (comportement attendu, limites,...)
	* ✅ Ajouter ft_printf() a la libft
	*
	* Ajout raccourcis : 
		* ✅ tab = switch min/max (colors)
		* ✅ + = +smooth
		* ✅ - = -smooth
		* ✅ BackSpace = reset zoom
	*
	* ✅ Faire en sorte de pouvoir changer la palette de couleurs
	* ✅ Passage en mode psychedelique
	* ✅ Recenter la fractale Mandelbrot
	* ✅ Ajouter une text-box avec raccourcis pour interagir avec le programme
	* Retravailler Makefile 
	* Refaire les commentaires descriptifs de chaque fonction
	* 
*/

static void	launch_processes(t_fractal *fractal, char **argv)
{
	ft_bzero(fractal, sizeof(t_fractal));
	ft_str_tolower(&argv[1]);
	fractal->name = argv[1];
	if (!ft_strcmp(argv[1], "julia"))
	{
		ft_putstr_fd("Fractal type identified !\n", 1);
		fractal->c.real = ft_atod(argv[2]);
		fractal->c.imag = ft_atod(argv[3]);
		fractal->init_c_real = argv[2];
		fractal->init_c_imag = argv[3];
	}
	data_init(fractal);
	initialize_window(fractal);
	initialize_image(fractal);
	if (ft_strcmp(argv[1], "sierpinski"))
	{	initialize_events(fractal);
		fractal_rendering(fractal);
	}
	else
	{
		// initialiser certains events (close sur X ou escape,...)
		render_sierpinski(fractal);
	}
	mlx_loop(fractal->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_fractal	fractal;

	if ((argc == 2 && (!ft_strcmp(argv[1], "mandelbrot") || !ft_strcmp(argv[1], \
			"sierpinski"))) || (argc == 4 && !ft_strcmp(argv[1], "julia")))
	{
		ft_putstr_fd("Launching the program...\n", 1);
		launch_processes(&fractal, argv);
	}
	else
	{
		ft_putstr_fd("Usage :\n\t'./fractol mandelbrot' or\n\
\t'./fractol julia <real> <imaginary>'\n", 1);				  // ajouter sierpinski !!
		return (1);
	}
	return (0);
}

int	parse_input(int argc, char **argv)
{
	if (argc == 2)
		if (!ft_strcmp(ft_str_tolower(argv[1]), "mandelbrot"))
			
}
