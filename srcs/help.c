#include "fractol.h"

/**
 * @brief  Print the second half of Julia fractal presets.
 *
 * Displays presets 9 through 19 for Julia set rendering, including
 * their numeric index, alias, name, and corresponding complex constant.
 *
 * @param  None.
 * @return None.
 *
 * @note   Output is printed to file descriptor 2 (stderr).
 * @pre    None.
 * @post   Preset list is printed to the console.
 */
static void	print_julia_presets2(void)
{
	ft_putstr_fd("\t\t9 / c  / cauliflower   : Cauliflower         "
		"[-0.8,     0.156]\n", 2);
	ft_putstr_fd("\t\t10/ m  / heart         : Mandelbrot Heart    "
		"[-0.7269,  0.1889]\n", 2);
	ft_putstr_fd("\t\t11/ v  / spiral_valley : Spiral Valley       "
		"[0.355534,-0.337292]\n", 2);
	ft_putstr_fd("\t\t12/ q  / diagonal      : Diagonal Symmetry   "
		"[0.355,    0.355]\n", 2);
	ft_putstr_fd("\t\t13/ g  / siegel        : Siegel Disk         "
		"[-0.39054, 0.58679]\n", 2);
	ft_putstr_fd("\t\t14/ k  / cactus        : Cactus              "
		"[-0.835,   -0.2321]\n", 2);
	ft_putstr_fd("\t\t15/ y  / filaments2    : Filaments Region    "
		"[-1.3488, -0.4542]\n", 2);
	ft_putstr_fd("\t\t16/ h  / antennae      : Antennae            "
		"[-1.7687, -0.0017]\n", 2);
	ft_putstr_fd("\t\t17/ o  / cauliflower_neg: Cauliflower (Neg)  "
		"[-0.8,    -0.156]\n", 2);
	ft_putstr_fd("\t\t18/ g  / golden        : Siegel Golden Mean  "
		"[-0.618,   0.0]\n", 2);
	ft_putstr_fd("\t\t19/ a  / airplane      : Airplane            "
		"[-0.39054, 0.58679]\n", 2);
}

/**
 * @brief  Print the complete list of Julia fractal presets.
 *
 * Displays usage examples for accessing Julia presets and prints
 * presets 1 through 19, including their aliases, names, and complex
 * constants. Delegates printing of presets 9–19 to `print_julia_presets2()`.
 *
 * @param  None.
 * @return None.
 *
 * @note   Output is printed to file descriptor 2 (stderr).
 * @pre    None.
 * @post   Full preset list for Julia fractals is displayed.
 */
static void	print_julia_presets(void)
{
	ft_putstr_fd(BOLD BLUE UNDERLINE"\nJulia presets "
		"(quick access):"RST"\n", 2);
	ft_putstr_fd("\t\tExample : ./fractol julia d\n", 2);
	ft_putstr_fd("\t\t         ./fractol julia 1\n", 2);
	ft_putstr_fd("\t\t         ./fractol julia dendrite\n\n", 2);
	ft_putstr_fd("\t\t"ITALIC"Presets list "
		"(by number, alias or name):"RST"\n", 2);
	ft_putstr_fd("\t\t1 / d  / dendrite      : Dendrite            "
		"[-0.70176, -0.3842]\n", 2);
	ft_putstr_fd("\t\t2 / r  / rabbit        : Douady Rabbit       "
		"[-0.123,   0.745]\n", 2);
	ft_putstr_fd("\t\t3 / t  / tuning        : Tuning Fork         "
		"[0.285,    0.01]\n", 2);
	ft_putstr_fd("\t\t4 / s  / spiral        : Spiral              "
		"[-0.76,    0.1]\n", 2);
	ft_putstr_fd("\t\t5 / e  / eye           : Eye                 "
		"[0.37,     0.1]\n", 2);
	ft_putstr_fd("\t\t6 / b  / basilica      : Basilica            "
		"[-1.0,     0.0]\n", 2);
	ft_putstr_fd("\t\t7 / f  / biomorph      : Biomorph/Filaments  "
		"[-0.4,     0.6]\n", 2);
	ft_putstr_fd("\t\t8 / n  / snowflake     : Snowflake (Frosty)  "
		"[-0.8,     0.2]\n", 2);
	print_julia_presets2();
}

/**
 * @brief  Print usage instructions and parameter descriptions.
 *
 * Displays valid command-line usage for launching the program,
 * lists available parameters, and describes the supported fractal types.
 *
 * @param  None.
 * @return None.
 *
 * @note   Output is printed to file descriptor 2 (stderr).
 * @pre    None.
 * @post   Usage and parameter information are displayed to the console.
 */
static void	print_usage_params(void)
{
	ft_putstr_fd(BOLD RED UNDERLINE"\nUsage :"RST"\n\n", 2);
	ft_putstr_fd("\t\t./fractol mandelbrot [-f] [-mt=no]\n", 2);
	ft_putstr_fd("\t\t./fractol julia <real> <imag> [-f] [-mt=no]\n", 2);
	ft_putstr_fd("\t\t./fractol julia <preset> [-f] [-mt=no]\n", 2);
	ft_putstr_fd("\t\t./fractol sierpinski [-f] [-mt=no]\n", 2);
	ft_putstr_fd("\t\t./fractol sierpinski <depth> [-f] [-mt=no]\n\n", 2);
	ft_putstr_fd(BOLD RED UNDERLINE"Parameters :"RST"\n\n", 2);
	ft_putstr_fd("\t"BOLD"'-mt=no'"RST"        "
		": Disable multi-threading\n", 2);
	ft_putstr_fd("\t"BOLD"'-f'"RST"            "
		": Fullscreen (slower but beautiful)\n\n", 2);
	ft_putstr_fd(BOLD BLUE UNDERLINE"\nFractals available :"RST"\n", 2);
	ft_putstr_fd("\t\t🦠 Mandelbrot     : Classic escape-time set\n", 2);
	ft_putstr_fd("\t\t🔮 Julia          : Parameterized quadratic Julia "
		"sets\n", 2);
	ft_putstr_fd("\t\t🧊 Sierpinski     "
		": Sierpinski Carpet (depth param. optional)\n\n", 2);
}

/**
 * @brief  Print the complete help manual.
 *
 * Displays usage instructions, Julia and Mandelbrot presets,
 * a shortcut reminder, and additional notes for the program.
 *
 * @param  None.
 * @return None.
 *
 * @note   Combines several helper functions to present the full manual.
 * @pre    None.
 * @post   The help content is printed to the console.
 */
void	print_help(void)
{
	print_usage_params();
	print_julia_presets();
	print_mandelbrot_presets();
	print_reminder_shortcuts();
	print_other_notes();
	ft_putstr_fd("\n\n", 2);
}

/**
 * @brief  Handle the '--help' or '-h' command-line option.
 *
 * Scans the program's arguments for a help flag. If found, prints
 * the help manual and terminates the program.
 *
 * @param  argv  Array of command-line arguments.
 * @return None.
 *
 * @note   If `argv` is NULL or empty, the function returns immediately.
 * @pre    `argv` must be a valid null-terminated string array or NULL.
 * @post   If help is requested, the manual is displayed and the program exits.
 */
void	handle_help(char **argv)
{
	int	i;
	int	help;

	i = -1;
	help = FALSE;
	if (!argv || !*argv)
		return ;
	while (argv[++i])
	{
		if (!ft_strcmp(argv[i], "-h") || !ft_strcmp(argv[i], "--help"))
		{
			help = TRUE;
			break ;
		}
	}
	if (help)
	{
		print_help();
		exit(0);
	}
}
