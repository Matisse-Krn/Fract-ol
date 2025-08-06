#include "fractol.h"

/*
 * Checks if the given color mode is already active or if it should reset 
	to the default black-and-white mode.
 * 
 * @param mode The requested color mode.
 * @param fractal A pointer to the fractal structure.
 * @return Returns 1 if no changes are needed, 0 otherwise.
*/
int	check_color_mode(char mode, t_fractal *fractal)
{
	if (mode == fractal->color_mode && mode == 'N')
		return (1);
	if (mode == fractal->color_mode || mode == 'N')
	{
		ft_putstr_fd("Initial \"color\" mode (black and white).\n", 1);
		fractal->color_min = fractal->init_color_min;
		fractal->color_max = fractal->init_color_max;
		fractal->color_mode = 'N';
		if (ft_strcmp(fractal->name, "sierpinski"))
			fractal_rendering(fractal);
		return (1);
	}
	return (0);
}

/*
 * Handles the final color mode change for Cyan.
 * If the requested color mode is not recognized, 
	no changes are applied.
 * 
 * @param mode The requested color mode.
 * @param fractal A pointer to the fractal structure.
*/
static void	change_color_mode_four(char mode, t_fractal *fractal)
{
	if (check_color_mode(mode, fractal))
		return ;
	else if (mode == 'C')
	{
		ft_putstr_fd("Cyan color mode.\n", 1);
		if (fractal->range_color_mode == 'C')
			fractal->color_min = 0xFF0000;
		else
			fractal->color_min = 0x000000;
		fractal->color_max = 0x00FFFF;
		fractal->color_mode = mode;
	}
	else
		return ;
	if (ft_strcmp(fractal->name, "sierpinski"))
		fractal_rendering(fractal);
}

/*
 * Handles additional color mode changes for Orange and Pink.
 * If the requested color mode is not handled here, 
	passes control to change_color_mode_four().
 * 
 * @param mode The requested color mode.
 * @param fractal A pointer to the fractal structure.
*/
static void	change_color_mode_three(char mode, t_fractal *fractal)
{
	if (check_color_mode(mode, fractal))
		return ;
	else if (mode == 'O')
	{
		ft_putstr_fd("Orange color mode.\n", 1);
		if (fractal->range_color_mode == 'C')
			fractal->color_min = 0x0080FF;
		else
			fractal->color_min = 0x000000;
		fractal->color_max = 0xFF8000;
		fractal->color_mode = mode;
	}
	else if (mode == 'P')
	{
		ft_putstr_fd("Pink color mode.\n", 1);
		if (fractal->range_color_mode == 'C')
			fractal->color_min = 0x00FF00;
		else
			fractal->color_min = 0x000000;
		fractal->color_max = 0xFF00FF;
		fractal->color_mode = mode;
	}
	else
	{
		change_color_mode_four(mode, fractal);
		return ;
	}
	if (ft_strcmp(fractal->name, "sierpinski"))
		fractal_rendering(fractal);
}

/*
 * Handles additional color mode changes for Red and Green.
 * If the requested color mode is not handled here, 
	passes control to change_color_mode_three().
 * 
 * @param mode The requested color mode.
 * @param fractal A pointer to the fractal structure.
*/
static void	change_color_mode_two(char mode, t_fractal *fractal)
{
	if (check_color_mode(mode, fractal))
		return ;
	else if (mode == 'R')
	{
		ft_putstr_fd("Red color mode.\n", 1);
		if (fractal->range_color_mode == 'C')
			fractal->color_min = 0x00FFFF;
		else
			fractal->color_min = 0x000000;
		fractal->color_max = 0xFF0000;
		fractal->color_mode = mode;
	}
	else if (mode == 'G')
	{
		ft_putstr_fd("Green color mode.\n", 1);
		if (fractal->range_color_mode == 'C')
			fractal->color_min = 0x8F8888;
		else
			fractal->color_min = 0x000000;
		fractal->color_max = 0x00FF00;
		fractal->color_mode = mode;
	}
	else
	{
		change_color_mode_three(mode, fractal);
		return ;
	}
	if (ft_strcmp(fractal->name, "sierpinski"))
		fractal_rendering(fractal);
}

/*
 * Changes the fractal's color mode based on user input.
 * Calls check_color_mode() to determine if changes are necessary.
 * If the requested color mode is not handled here, passes control 
	to change_color_mode_two().
 * 
 * @param mode The requested color mode.
 * @param fractal A pointer to the fractal structure.
*/
void	change_color_mode(char mode, t_fractal *fractal)
{
	if (check_color_mode(mode, fractal))
		return ;
	else if (mode == 'B')
	{
		ft_putstr_fd("Blue mode.\n", 1);
		if (fractal->range_color_mode == 'C')
			fractal->color_min = 0xFFFF00;
		else
			fractal->color_min = 0x000000;
		fractal->color_max = 0x0000FF;
		fractal->color_mode = mode;
	}
	else if (mode == 'Y')
	{
		ft_putstr_fd("Yellow color mode.\n", 1);
		if (fractal->range_color_mode == 'C')
			fractal->color_min = 0x000099;
		else
			fractal->color_min = 0x000000;
		fractal->color_max = 0x999900;
		fractal->color_mode = mode;
	}
	else
	{
		change_color_mode_two(mode, fractal);
		return ;
	}
	if (ft_strcmp(fractal->name, "sierpinski"))
		fractal_rendering(fractal);
}
