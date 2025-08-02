#include "fractol.h"

/*
 * Handles program exit by freeing all allocated resources,
 * destroying the MiniLibX window and image, and printing an exit message.
 * 
 * @param fractal A pointer to the fractal structure managing resources.
 * @return Always returns 0.
 * 
 * Key shortcut:
	- 'Esc' (Escape key) = Exit program
*/
int	handle_exit(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
	mlx_destroy_display(fractal->mlx_ptr);
	free(fractal->mlx_ptr);
	if (fractal->last_pos && fractal->last_pos[0] != '\0')
		free(fractal->last_pos);
	ft_printf("Exiting the program. See ya' !\n");
	exit(EXIT_SUCCESS);
	return (0);
}

/*
 * Handles keyboard input events and applies corresponding actions.
 * Supports movement, zooming, and iteration adjustments.
 * Calls handle_key_two() for additional key bindings.
 * 
 * @param keysym The key code of the pressed key.
 * @param fractal A pointer to the fractal structure.
 * @return Always returns 0.
 * 
 * Keyboard shortcuts:
	- `Esc` (XK_Escape) → Exit program
	- `←` (XK_Left) → Move left
	- `→` (XK_Right) → Move right
	- `↑` (XK_Up) → Move up
	- `↓` (XK_Down) → Move down
	- `+` (XK_KP_Add) → Increase max iterations
	- `-` (XK_KP_Subtract) → Decrease max iterations
*/

int	handle_key(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		handle_exit(fractal);
	else if (keysym == XK_Left)
		displacement('L', fractal);
	else if (keysym == XK_Right)
		displacement('R', fractal);
	else if (keysym == XK_Up)
		displacement('U', fractal);
	else if (keysym == XK_Down)
		displacement('D', fractal);
	else if (keysym == XK_KP_Add)
		change_max_iterations('+', fractal);
	else if (keysym == XK_KP_Subtract)
		change_max_iterations('-', fractal);
	else
	{
		handle_key_two(keysym, fractal);
		return (0);
	}
	return (0);
}

/*
 * Handles additional keyboard inputs related to color adjustments
	and swapping colors.
 * Calls handle_key_three() for further key bindings.
 * 
 * @param keysym The key code of the pressed key.
 * @param fractal A pointer to the fractal structure.
 *
 * Keyboard shortcuts:
	- `N` (XK_n) → Set color mode to Normal
	- `R` (XK_r) → Set color mode to Red
	- `G` (XK_g) → Set color mode to Green
	- `B` (XK_b) → Set color mode to Blue
	- `Y` (XK_y) → Set color mode to Yellow
	- `O` (XK_o) → Set color mode to Orange
	- `P` (XK_p) → Set color mode to Purple
	- `C` (XK_c) → Set color mode to Cyan
	- `Tab` (XK_Tab) → Swap min/max colors
*/
void	handle_key_two(int keysym, t_fractal *fractal)
{
	if (keysym == XK_n)
		change_color_mode('N', fractal);
	else if (keysym == XK_r)
		change_color_mode('R', fractal);
	else if (keysym == XK_g)
		change_color_mode('G', fractal);
	else if (keysym == XK_b)
		change_color_mode('B', fractal);
	else if (keysym == XK_y)
		change_color_mode('Y', fractal);
	else if (keysym == XK_o)
		change_color_mode('O', fractal);
	else if (keysym == XK_p)
		change_color_mode('P', fractal);
	else if (keysym == XK_c)
		change_color_mode('C', fractal);
	else if (keysym == XK_Tab)
		swap_colors(fractal);
	else
	{
		handle_key_three(keysym, fractal);
		return ;
	}
}

/*
 * Handles mouse button events to apply zooming operations.
 * Supports different zoom levels for various mouse buttons.
 * 
 * @param button The mouse button code.
 * @param x The x-coordinate of the mouse event.
 * @param y The y-coordinate of the mouse event.
 * @param fractal A pointer to the fractal structure.
 * @return Always returns 0.
 *
 * Mouse shortcuts:
	- Scroll down (Button5) → Normal dezoom
	- Scroll up (Button4) → Normal zoom
	- Right click (Button3) → Big dezoom
	- Left click (Button1) → Big zoom
*/
int	handle_mouse(int button, int x, int y, t_fractal *fractal)
{
	if (button == Button5)
	{
		ft_putstr_fd("Zoom out\n", 1);
		apply_zoom(fractal, x, y, 1.2);
	}
	else if (button == Button4)
	{
		ft_putstr_fd("Zoom in\n", 1);
		apply_zoom(fractal, x, y, 0.8);
	}
	else if (button == Button3)
	{	
		ft_putstr_fd("Big zoom out\n", 1);
		apply_zoom(fractal, x, y, 1.8);
	}
	else if (button == Button1)
	{
		ft_putstr_fd("Big zoom in\n", 1);
		apply_zoom(fractal, x, y, 0.2);
	}
	return (0);
}

/*
 * Handles mouse movement events and updates the last known cursor position.
 * Stores the coordinates as a formatted string and updates the display.
 * 
 * @param x The x-coordinate of the mouse cursor.
 * @param y The y-coordinate of the mouse cursor.
 * @param fractal A pointer to the fractal structure.
 * @return Always returns 0.
*/
int	handle_mouse_move(int x, int y, t_fractal *fractal)
{
	char	*x_str;
	char	*y_str;
	char	*tmp;

	if (fractal->last_pos && fractal->last_pos[0] != '\0')
		free(fractal->last_pos);
	x_str = ft_itoa(x);
	if_malloc_error(x_str);
	y_str = ft_itoa(y);
	if_malloc_error(y_str);
	tmp = ft_strjoin("Mouse position : x = ", x_str);
	free(x_str);
	if_malloc_error(tmp);
	fractal->last_pos = ft_strjoin(tmp, "  y = ");
	free(tmp);
	if_malloc_error(fractal->last_pos);
	tmp = fractal->last_pos;
	fractal->last_pos = ft_strjoin(tmp, y_str);
	free(tmp);
	free(y_str);
	if_malloc_error(fractal->last_pos);
	manage_text(fractal);
	return (0);
}
