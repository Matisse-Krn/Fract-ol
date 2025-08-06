#include "fractol.h"

/*
	* ✅Implementer Mandelbrot
	* ✅Implementer Julia
	* ✅ Implementer une autre fractale (bonus)
	* ✅ Handle hooks pour sierpinski
		* ✅ entrer la depth en parametre ?
		* ✅ modifier la depth
		* ✅ switch color
	* ✅ Parser input
	* ✅ Afficher les coordonnees du curseur de la souris sur la fenetre
	* ✅ Afficher le mode de couleurs actuellement selectionne + psy ou non ?
	* ✅ Afficher les coordonnees initiales (parametres) pour Julia
	* ✅ Ecrire dans le terminal a CHAQUE action
	* ✅ Ajouter ft_printf() a la libft
	* ✅ Ajout raccourcis : 
		* ✅ tab = switch min/max (colors)
		* ✅ + = +smooth
		* ✅ - = -smooth
		* ✅ BackSpace = reset zoom
	* ✅ Faire en sorte de pouvoir changer la palette de couleurs
	* ✅ Passage en mode psychedelique
	* ✅ Recenter la fractale Mandelbrot
	* ✅ Ajouter une text-box avec raccourcis pour interagir avec le programme
	* ✅ Refaire les commentaires descriptifs de chaque fonction
	* ✅ Verifier avec des inputs bizarres ('sierpinski 65' 'sierpinski .')
		* ✅ Sierpinski
		* ✅ Julia
		* ✅ Mandelbrot
	* ✅ Ajout d'une fonction pour recuperer la depth_max en fonction
		de la taille de la fenetre, et adapter la depth en consequence
	* ✅ Protection du changement de depth par l'utilisateur en fonction
		de fractal->max_depth
	* ✅ Sortie propre du programme quand taille de fenetre insuffisante
	* Ajouter des 'alias' dans le programme afin de proposer des parametres
		predefinis pour Julia
	* Rediger man pour explications alias et autres (comportement
		attendu, limites,...)
	* Retravailler Makefile
	* Verifier qu'il ne reste pas de 'printf()' (+ tester d'en executer un
		dans chaque fichier sans ajouter le header <stdio.h> localement)
	* Suivre et verifier la check-list (toto before push)
	* Supprimer tous les fichiers et dossiers inutiles du dosier de rendu
*/

/*
 * Parses user input to determine which fractal should be rendered.
 * Calls up the appropriate initialization function according to the
	arguments supplied.
 *
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @param fractal A pointer to the fractal structure to store parsed data.
 * @return Returns 0 on success, 1 if the input does not match any valid
	fractal type.
*/
static int	parse_input(int argc, char **argv, t_fractal *fractal)
{
	(void)argc;
	set_multi_threading(argv, fractal);
	if (!ft_strcmp(argv[1], "mandelbrot"))
		init_mandelbrot(argv, fractal);
	else if (!ft_strcmp(argv[1], "julia") && argc > 2)
		init_julia(argv, fractal);
	else if (!ft_strcmp(argv[1], "sierpinski") && is_valid_number(argv[2]))
		init_sierpinski_depth(argv, fractal);
	else if (!ft_strcmp(argv[1], "sierpinski"))
		init_sierpinski(argv, fractal);
	else
		return (1);
	return (0);
}

/*
 * Entry point of the fractal rendering program.
 * Calls the main parsing function and checks its return value.
 * Displays usage instructions if input is invalid.
 * 
 * @param argc The number of command-line arguments.
 * @param argv The array of command-line arguments.
 * @return Returns 0 on success, 1 if the input is invalid.
*/
int	main(int argc, char **argv)
{
	t_fractal	fractal;

	printf("%sDEBUG : TODO : Retirer le snprintf !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!%s\n", RED, RST);
	if (argc < 2)
		return (usage_error(), 1);
	handle_help(argv);
	ft_bzero(&fractal, sizeof(t_fractal));
	ft_str_tolower(argv[1]);
	if (parse_input(argc, argv, &fractal))
		return (usage_error(), 1);
	return (0);
}
