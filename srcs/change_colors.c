#include "fractol.h"

/**
 * @brief  Check and reset the fractal's color mode to Normal if applicable.
 *
 * Determines whether the requested color mode is already active or if the
 * requested mode is 'N' (Normal black & white). If so, it resets the fractal's
 * colors to the initial values, sets the mode to 'N', and triggers rendering
 * unless the fractal is Sierpinski.
 *
 * @param  mode     The requested color mode character.
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return 1 if the mode was applied or no change was necessary, 0 otherwise.
 *
 * @note   This is a helper function used by all other color mode change
 *         functions to handle the Normal mode and redundant mode changes.
 * @pre    `fractal` must be initialized with valid color and rendering data.
 * @post   If applicable, the fractal is rendered in Normal mode.
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

/**
 * @brief  Apply the Cyan color mode or delegate to the next mode handler.
 *
 * Sets the fractal's colors to a Cyan gradient if requested, otherwise
 * delegates to `change_color_mode()` for other modes. Triggers rendering
 * unless the fractal is Sierpinski.
 *
 * @param  mode     The requested color mode character.
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   Uses `check_color_mode()` to handle Normal mode or redundant
 *         mode changes before applying Cyan.
 * @pre    `fractal` must be initialized with valid color and rendering data.
 * @post   The fractal color range is updated to Cyan if applicable.
 */
static void	change_color_mode_four(char mode, t_fractal *fractal)
{
	if (check_color_mode(mode, fractal))
		return ;
	else if (mode == 'C')
	{
		ft_putstr_fd("Cyan color mode.\n", 1);
		fractal->color_min = 0x000000;
		fractal->color_max = 0x00FFFF;
		fractal->color_mode = mode;
	}
	else
		return ;
	if (ft_strcmp(fractal->name, "sierpinski"))
		fractal_rendering(fractal);
}

/**
 * @brief  Apply the Orange or Pink color mode, or delegate further.
 *
 * Sets the fractal's colors to an Orange or Pink gradient if requested,
 * otherwise delegates to `change_color_mode_four()` for other modes.
 * Triggers rendering unless the fractal is Sierpinski.
 *
 * @param  mode     The requested color mode character.
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   Uses `check_color_mode()` to handle Normal mode or redundant
 *         mode changes before applying new colors.
 * @pre    `fractal` must be initialized with valid color and rendering data.
 * @post   The fractal color range is updated to Orange or Pink if applicable.
 */
static void	change_color_mode_three(char mode, t_fractal *fractal)
{
	if (check_color_mode(mode, fractal))
		return ;
	else if (mode == 'O')
	{
		ft_putstr_fd("Orange color mode.\n", 1);
		fractal->color_min = 0x000000;
		fractal->color_max = 0xFF8000;
		fractal->color_mode = mode;
	}
	else if (mode == 'P')
	{
		ft_putstr_fd("Pink color mode.\n", 1);
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

/**
 * @brief  Apply the Red or Green color mode, or delegate further.
 *
 * Sets the fractal's colors to a Red or Green gradient if requested,
 * otherwise delegates to `change_color_mode_three()` for other modes.
 * Triggers rendering unless the fractal is Sierpinski.
 *
 * @param  mode     The requested color mode character.
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   Uses `check_color_mode()` to handle Normal mode or redundant
 *         mode changes before applying new colors.
 * @pre    `fractal` must be initialized with valid color and rendering data.
 * @post   The fractal color range is updated to Red or Green if applicable.
 */
static void	change_color_mode_two(char mode, t_fractal *fractal)
{
	if (check_color_mode(mode, fractal))
		return ;
	else if (mode == 'R')
	{
		ft_putstr_fd("Red color mode.\n", 1);
		fractal->color_min = 0x000000;
		fractal->color_max = 0xFF0000;
		fractal->color_mode = mode;
	}
	else if (mode == 'G')
	{
		ft_putstr_fd("Green color mode.\n", 1);
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

/**
 * @brief  Apply the Blue or Yellow color mode, or delegate further.
 *
 * Sets the fractal's colors to a Blue or Yellow gradient if requested,
 * otherwise delegates to `change_color_mode_two()` for other modes.
 * Triggers rendering unless the fractal is Sierpinski.
 *
 * @param  mode     The requested color mode character.
 * @param  fractal  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   Uses `check_color_mode()` to handle Normal mode or redundant
 *         mode changes before applying new colors.
 * @pre    `fractal` must be initialized with valid color and rendering data.
 * @post   The fractal color range is updated to Blue or Yellow if applicable.
 */
void	change_color_mode(char mode, t_fractal *fractal)
{
	if (check_color_mode(mode, fractal))
		return ;
	else if (mode == 'B')
	{
		ft_putstr_fd("Blue mode.\n", 1);
		fractal->color_min = 0x000000;
		fractal->color_max = 0x0000FF;
		fractal->color_mode = mode;
	}
	else if (mode == 'Y')
	{
		ft_putstr_fd("Yellow color mode.\n", 1);
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
