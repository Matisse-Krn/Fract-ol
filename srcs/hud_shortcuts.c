#include "fractol.h"

static void	print_shortcuts_default(t_fractal *f)
{
	put_a_string(5, f->img.height - 82, "Scroll Up : zoom in       \
Scroll Down : zoom out       LClick : big zoom in       RClick : big zoom out\
       BackSpace : reset view\
       Space : psychedelic", f);
	put_a_string(5, f->img.height - 64, "+ (keypad) : increase definition"
		"       - (keypad) : reduce definition       + : smoothen       "
		"- : contrast       S : change render mode", f);
	put_a_string(5, f->img.height - 46, "E : export to PNG       "
		"J + [1-9] : jump-to preset (Mandelbrot)       "
		"H : help menu in terminal", f);
	put_a_string(5, f->img.height - 28, "COLORS :", f);
	put_a_string(5, f->img.height - 10, "N : Normal       R : Red       \
G : Green       B : Blue       Y : Yellow       O : Orange       P : Pink       \
C : Cyan    ||    TAB : reverse color mode", f);
}

static void	print_shortcuts_buddhabrot(t_fractal *f)
{
	put_a_string(5, f->img.height - 12, "E : export PNG       H : help       Esc : exit", f);
}

static void	print_shortcuts_sierpinski(t_fractal *f)
{
	put_a_string(5, f->img.height - 52, "0-6 : depth", f);
	put_a_string(5, f->img.height - 34, "N/R/G/B/Y/O/P/C : color       E : export PNG", f);
	put_a_string(5, f->img.height - 16, "H : help       Esc : exit", f);
}

void	print_shortcuts(t_fractal *fractal)
{
	if (!ft_strcmp(fractal->name, "buddhabrot"))
		print_shortcuts_buddhabrot(fractal);
	else if (!ft_strcmp(fractal->name, "sierpinski"))
		print_shortcuts_sierpinski(fractal);
	else
		print_shortcuts_default(fractal);
}
