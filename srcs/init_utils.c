#include "fractol.h"

void	init_mlx(t_fractal *fractal)
{
	initialize_window(fractal);
	initialize_image(fractal);
	initialize_events(fractal);
}

void	invalid_depth(char **argv, t_fractal *fractal)
{
	ft_printf("%s is an invalid depth value for Sierpinski Carpet...\n\
Allowed values in a window of this size : [0-%d]\nValue applied to \
depth : %d\n", argv[2], fractal->max_depth, fractal->depth);
}

void	print_launch_messages(char type)
{
	if (type == 'M')
	{
		ft_putstr_fd("🦠 Mandelbrot fractal identified ! 🦠\n", 1);
		ft_putstr_fd("\t⚙️  Launching the program... ⚙️\n", 1);
	}
	else if (type == 'J')
	{
		ft_putstr_fd("🦠 Julia fractal identified ! 🦠\n", 1);
		ft_putstr_fd("\t⚙️  Launching the program... ⚙️ \n", 1);
	}
	else if (type == 'S')
	{
		ft_putstr_fd("🧊 Sierpinski fractal identified ! 🧊\n", 1);
		ft_putstr_fd("\t⚙️  Launching the program... ⚙️ \n", 1);
	}
}

void	is_fullscreen(char **argv, t_fractal *fractal)
{
	int	i;

	i = -1;
	while (argv[++i])
	{
		if (!ft_strncmp(argv[i], "-f", 2))
		{
			fractal->fullscreen = TRUE;
			return ;
		}
	}
	fractal->fullscreen = FALSE;
}

void  set_multi_threading(char **argv, t_fractal *fractal)
{
	int	i;

	i = -1;
	fractal->mt = TRUE;
	while (argv[++i])
	{
		if (!ft_strncmp(argv[i], "-mt=no", 6))
			fractal->mt = FALSE;
	}
}
