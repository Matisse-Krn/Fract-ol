#include "fractol.h"

/**
 * @brief  Print a malloc error message and terminate the program.
 *
 * Displays a system-generated error message using `perror()` and
 * immediately exits the program with `EXIT_FAILURE`.
 *
 * @param  None.
 * @return None. This function does not return.
 *
 * @note   Intended to be called when a memory allocation fails.
 * @pre    None.
 * @post   The program is terminated.
 */
void	malloc_error(void)
{
	perror("Malloc ERROR...\n");
	exit(EXIT_FAILURE);
}

/**
 * @brief  Validate a malloc result and exit on failure.
 *
 * Checks if the given pointer is NULL. If it is, calls `malloc_error()`
 * to display an error message and terminate the program.
 *
 * @param  s  Pointer returned by a memory allocation function.
 * @return The original pointer `s` if it is not NULL.
 *
 * @note   Acts as a safety wrapper for memory allocation functions.
 * @pre    None.
 * @post   If allocation failed, the program is terminated.
 */
char	*if_malloc_error(char *s)
{
	if (!s)
		malloc_error();
	return (s);
}

/**
 * @brief  Check if a string represents a valid numeric value.
 *
 * Allows optional leading whitespace, an optional '+' or '-' sign,
 * digits, and at most one decimal separator ('.' or ',').
 *
 * @param  str  The input string to validate.
 * @return TRUE if the string is a valid number, FALSE otherwise.
 *
 * @note   An empty string or a string with only a sign is considered invalid.
 * @pre    `str` must be a valid null-terminated string or NULL.
 * @post   No changes are made to the input string.
 */
int	is_valid_number(const char *str)
{
	int	has_dot;
	int	has_digit;

	if (!str)
		return (FALSE);
	while (*str == ' ' || *str == '\t' || *str == '\n' || \
		*str == '\r' || *str == '\f' || *str == '\v')
		str++;
	if (*str == '-' || *str == '+')
		str++;
	has_dot = 0;
	has_digit = 0;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			has_digit = 1;
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
	if (has_digit == 0)
		return (FALSE);
	return (TRUE);
}

/**
 * @brief  Validate numeric input arguments for the Julia fractal.
 *
 * Ensures that both the second and third command-line arguments
 * are valid numbers. If either is invalid, displays an error message
 * with usage instructions and terminates the program.
 *
 * @param  argv  Command-line arguments array.
 * @return None.
 *
 * @note   Intended for validating `<real>` and `<imag>` parameters
 *         when launching the Julia set.
 * @pre    `argv[2]` and `argv[3]` must exist and be null-terminated strings.
 * @post   If invalid input is detected, the program is terminated.
 */
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

/**
 * @brief  Display usage instructions and exit.
 *
 * Prints a formatted help message explaining how to use the program,
 * including available fractal types, optional parameters, and their
 * descriptions.
 *
 * @param  None.
 * @return None.
 *
 * @note   Called when invalid command-line arguments are detected.
 * @pre    None.
 * @post   A usage message is printed to stderr.
 */
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
