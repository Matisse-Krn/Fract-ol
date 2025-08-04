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
	int	has_dot;

	if (!str)
		return (FALSE);
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
		*str == '\r' || *str == '\f' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	has_dot = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
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
	mlx_get_screen_size(fractal->mlx_ptr, &fractal->img.full_width, &fractal->img.full_height);
	set_real_screen_size(fractal);
	
	data_init(fractal);
	init_mlx(fractal);
	printf("DEBUG : HHHHHHHHHHHHHHHERE\n");
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
	mlx_get_screen_size(fractal->mlx_ptr, &fractal->img.full_width, &fractal->img.full_height);
	set_real_screen_size(fractal);
	check_valid_input_numbers(argv);
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
void	init_sierpinski(char **argv, t_fractal *f)
{
	f->name = argv[1];
	f->mlx_ptr = mlx_init();
	if (!f->mlx_ptr)
		malloc_error();
	print_launch_messages('S');
	is_fullscreen(argv, f);
	mlx_get_screen_size(f->mlx_ptr, &f->img.full_width, &f->img.full_height);
	set_real_screen_size(f);
	data_init(f);
	data_init_sierpinski(f);
	ft_printf("🗔  Max depth : %d 🗔\n🕳️  Default depth : %d 🕳️\n",
		f->max_depth, f->depth);
	init_mlx(f);
	rendering_sierpinski(f);
	mlx_loop(f->mlx_ptr);
}

/*
 * Initializes the fractal structure for the Sierpinski Carpet with a
	user-defined depth.
 * Validates the provided depth value, applying default constraints if necessary.
 * 
 * @param argv The array of command-line arguments.
 * @param fractal A pointer to the fractal structure to store parsed data.
*/
void	init_sierpinski_depth(char **argv, t_fractal *f)
{
	f->name = argv[1];
	is_fullscreen(argv, f);
	data_init(f);
	f->mlx_ptr = mlx_init();
	if (!f->mlx_ptr)
		malloc_error();
	mlx_get_screen_size(f->mlx_ptr, &f->img.full_width, &f->img.full_height);
	set_real_screen_size(f);
	print_launch_messages('S');
	data_init_sierpinski(f);
	printf("Max depth = %d\n", f->max_depth);
	if (ft_strlen(argv[2]) == 1 && *argv[2] >= '0' && *argv[2] <= \
		f->max_depth + '0' && f->max_depth <= 9)
	{
		f->depth = ft_atoi(argv[2]);
		ft_printf("🗔  Max depth : %d 🗔\n🕳️  Choosen depth : %d 🕳️\n",
			f->max_depth, f->depth);
	}
	else
		invalid_depth(argv, f);
	init_mlx(f);
	rendering_sierpinski(f);
	mlx_loop(f->mlx_ptr);
}
