#include "fractol.h"

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

static void	print_julia_presets(void)
{
	ft_putstr_fd(BOLD BLUE UNDERLINE"\nJulia presets (quick access) :"RST"\n", 2);
	ft_putstr_fd("\t\tExample : ./fractol julia d\n", 2);
	ft_putstr_fd("\t\t         ./fractol julia 1\n", 2);
	ft_putstr_fd("\t\t         ./fractol julia dendrite\n\n", 2);
	ft_putstr_fd("\t\t"ITALIC"Presets list (by number, alias or name):"RST"\n", 2);
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
	ft_putstr_fd("\t\t🔮 Julia          : Parameterized quadratic Julia sets\n", 2);
	ft_putstr_fd("\t\t🧊 Sierpinski     "
		": Sierpinski Carpet (depth param. optional)\n\n", 2);
}

void	print_help(void)
{
	print_usage_params();
	print_julia_presets();
	print_mandelbrot_presets();
	print_reminder_shortcuts();
	print_other_notes();
	write(2, "\n\n", 2);
}

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
