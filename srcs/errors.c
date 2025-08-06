#include "fractol.h"

/*
 * Handles memory allocation failures by printing an error message
	and terminating the program.
*/
void	malloc_error(void)
{
	perror("Malloc ERROR...\n");
	exit(EXIT_FAILURE);
}

/*
 * Checks if a memory allocation was successful.
 * If allocation failed, calls malloc_error() to exit the program.
 * 
 * @param s A pointer to the allocated memory.
 * @return Returns the same pointer if allocation was successful.
*/
char	*if_malloc_error(char *s)
{
	if (!s)
		malloc_error();
	return (s);
}

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

void	check_valid_input_numbers(char **argv)
{
	if (!is_valid_number(argv[2]))
	{
		ft_printf("\n\t\t⚠️  '%s' is not a valid first param... ⚠️\n"
			"👋 Exit program 👋\n\n", argv[2]);
		ft_putstr_fd(BOLD UNDERLINE"\tUse '--help' or '-h' to view the "
			"manual anytime."RST"\n\n", 2);
		exit(EXIT_FAILURE);
	}
	else if (!is_valid_number(argv[3]))
	{
		ft_printf("\n\t\t⚠️  '%s' is not a valid second param... ⚠️\n"
			"👋 Exit program 👋\n\n", argv[3]);
		ft_putstr_fd(BOLD UNDERLINE"\tUse '--help' or '-h' to view "
			"the manual anytime."RST"\n\n", 2);
		exit(EXIT_FAILURE);
	}
}

void	usage_error(void)
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
	ft_putstr_fd(BOLD RED UNDERLINE"\tUse '--help' or '-h' to view "
		"the manual anytime."RST"\n\n", 2);
}
