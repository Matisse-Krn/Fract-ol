#include "fractol.h"

/*
 * Displays a string on the fractal window at the specified coordinates.
 * Ensures that text is only rendered within the visible area.
 * 
 * @param x The x-coordinate for text placement.
 * @param y The y-coordinate for text placement.
 * @param s The string to display.
 * @param fractal A pointer to the fractal structure.
 * 
 * Constraints:
	- Ensures `x` and `y` are within image boundaries before rendering.
*/
void	put_a_string(int x, int y, char *s, t_fractal *fractal)
{
	if (fractal->img.height > y && fractal->img.width > x)
	{
		mlx_string_put(fractal->mlx_ptr, fractal->win_ptr,
			x, y, 0xFFFFFF, s);
	}
}

/*
 * Prints a list of available keyboard and mouse shortcuts at the
	bottom of the screen.
 * Displays zoom, reset, psychedelic mode, iteration adjustment, contrast,
	and color controls.
 * 
 * @param fractal A pointer to the fractal structure.
 * 
 * Layout:
	- The shortcuts are split into multiple lines for readability.
	- The function adapts text position based on image height.
*/
void	print_shortcuts(t_fractal *fractal)
{
	put_a_string(5, fractal->img.height - 64, "Scrool Up : zoom in       \
Scroll Down : zoom out       LClick : big zoom in       RClick : big zoom out\
       BackSpace : reset view\
       Space : psychedelic", fractal);
	put_a_string(5, fractal->img.height - 46, "+ (keypad) : increase definition\
       - (keypad) : reduce definition       + : smoothen       \
- : contrast", fractal);
	put_a_string(5, fractal->img.height - 28, "COLORS :", fractal);
	put_a_string(5, fractal->img.height - 10, "N : Normal       R : Red       \
G : Green       B : Blue       Y : Yellow       O : Orange       P : Pink       \
C : Cyan    ||    TAB : Reverse color mode", fractal);
}

/*
 * Manages all textual elements displayed on the fractal window.
 * Draws background boxes for text, displays shortcuts,
	and updates dynamic values.
 * 
 * @param fractal A pointer to the fractal structure.
 * 
 * Process:
	- Calls draw_text_boxes() to prepare background areas.
	- Prints shortcuts via print_shortcuts().
	- Displays cursor position stored in `fractal->last_pos`.
	- Displays the current color mode and iteration count.
*/
void	manage_text(t_fractal *fractal)
{
	draw_text_boxes(fractal);
	print_shortcuts(fractal);
	put_a_string(5, 25, fractal->last_pos, fractal);
	put_color_mode(fractal);
	put_max_iterations(fractal);
}
