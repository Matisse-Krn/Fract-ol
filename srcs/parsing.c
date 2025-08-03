#include "fractol.h"

/*
 * Checks if the given string represents a valid numeric value.
 * Allows optional leading whitespace, a sign, and a single decimal separator.
 * 
 * @param str The string to validate.
 * @return Returns 1 if the string is a valid number, 0 otherwise.
 * @return If the string contains only a '-' or a '+' (or '-.', or '.-',...),
	it will be valid and interpreted as a 1.
*/
int	is_valid_number(const char *str)
{
	/*int	has_digits;*/
	int	has_dot;

	if (!str)
		return (FALSE);
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
		*str == '\r' || *str == '\f' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	/*has_digits = 0;*/
	has_dot = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			/*has_digits = 1;*/
			;
		else if (*str == '.' || *str == ',')
		{
			if (has_dot)
				return (FALSE);
			has_dot = 1;
		}
		else
			return (FALSE);
		str++;
	}
	return (TRUE);
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
	fractal->name = argv[1];
	fractal->mlx_ptr = mlx_init();
	if (!fractal->mlx_ptr)
		malloc_error();
	print_launch_messages('M');
	is_fullscreen(argv, fractal);
	data_init(fractal);
	init_mlx(fractal);
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
	fractal->name = argv[1];
	fractal->mlx_ptr = mlx_init();
	if (!fractal->mlx_ptr)
		malloc_error();
	print_launch_messages('J');
	is_fullscreen(argv, fractal);
	if (!is_valid_number(argv[2]))
	{
		ft_printf("\n\t\t⚠️  '%s' is not a valid input... ⚠️\n"
			"👋 Exit program 👋\n\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	else if (!is_valid_number(argv[3]))
	{
		ft_printf("\n\t\t⚠️  '%s' is not a valid input... ⚠️\n"
			"👋 Exit program 👋\n\n", argv[3]);
		exit(EXIT_FAILURE);
	}
	fractal->c.real = ft_atod(argv[2]);
	fractal->c.imag = ft_atod(argv[3]);
	fractal->init_c_real = argv[2];
	fractal->init_c_imag = argv[3];
	data_init(fractal);
	init_mlx(fractal);
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
	fractal->name = argv[1];
	fractal->mlx_ptr = mlx_init();
	if (!fractal->mlx_ptr)
		malloc_error();
	print_launch_messages('S');
	is_fullscreen(argv, fractal);
	mlx_get_screen_size(fractal->mlx_ptr, &fractal->img.full_width,
					 &fractal->img.full_height);
	if (fractal->fullscreen == TRUE)
	{
		fractal->img.height = fractal->img.full_height - (fractal->img.full_height / 21);
		fractal->img.width = fractal->img.full_width/* - (fractal->img.width / 10)*/;
	}
	else
	{
		fractal->img.height = 960;
		fractal->img.width = 960;
	}
	data_init(fractal);
	data_init_sierpinski(fractal);
	ft_printf("🗔  Max depth : %d 🗔\n🕳️  Default depth : %d 🕳️\n",
		fractal->max_depth, fractal->depth);
	init_mlx(fractal);
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
	fractal->name = argv[1];
	is_fullscreen(argv, fractal);
	data_init(fractal);
	fractal->mlx_ptr = mlx_init();
	if (!fractal->mlx_ptr)
		malloc_error();
	mlx_get_screen_size(fractal->mlx_ptr, &fractal->img.full_width,
					 &fractal->img.full_height);
	if (fractal->fullscreen == TRUE)
	{
		fractal->img.height = fractal->img.full_height - (fractal->img.full_height / 21);
		fractal->img.width = fractal->img.full_width/* - (fractal->img.width / 10)*/;
	}
	else
	{
		fractal->img.height = 960;
		fractal->img.width = 960;
	}
	print_launch_messages('S');
	data_init_sierpinski(fractal);
	printf("Max depth = %d\n", fractal->max_depth);
	if (ft_strlen(argv[2]) == 1 && *argv[2] >= '0' && *argv[2] <= \
		fractal->max_depth + '0' && fractal->max_depth <= 9)
	{
		fractal->depth = ft_atoi(argv[2]);
		ft_printf("🗔  Max depth : %d 🗔\n🕳️  Choosen depth : %d 🕳️\n",
			fractal->max_depth, fractal->depth);
	}
	else
		invalid_depth(argv, fractal);
	init_mlx(fractal);
	rendering_sierpinski(fractal);
	mlx_loop(fractal->mlx_ptr);
}
