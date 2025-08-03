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

void	check_valid_input_numbers(char **argv)
{
	if (!is_valid_number(argv[2]))
	{
		ft_printf("\n\t\t⚠️  '%s' is not a valid first param... ⚠️\n"
			"👋 Exit program 👋\n\n", argv[2]);
		exit(EXIT_FAILURE);
	}
	else if (!is_valid_number(argv[3]))
	{
		ft_printf("\n\t\t⚠️  '%s' is not a valid second param... ⚠️\n"
			"👋 Exit program 👋\n\n", argv[3]);
		exit(EXIT_FAILURE);
	}
}
