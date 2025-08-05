#include "fractol.h"

void	switch_palette_mode(t_fractal *f)
{
	if (f->palette_mode == 'N')
		f->palette_mode = 'L';
	else if (f->palette_mode == 'L')
		f->palette_mode = 'A';
	else if (f->palette_mode == 'A')
		f->palette_mode = 'F';
	else if (f->palette_mode == 'F')
		f->palette_mode = 'C';
	else
		f->palette_mode = 'N';

	ft_putstr_fd("Palette mode switched to : ", 1);
	if (f->palette_mode == 'N')
		ft_putstr_fd("Normal (exponential)\n", 1);
	else if (f->palette_mode == 'L')
		ft_putstr_fd("Logarithmic scale\n", 1);
	else if (f->palette_mode == 'A')
		ft_putstr_fd("Adaptive (based on max i)\n", 1);
	else if (f->palette_mode == 'F')
		ft_putstr_fd("Fixed log(i)/log(1000)\n", 1);
	else if (f->palette_mode == 'C')
		ft_putstr_fd("Cyclic modulo color\n", 1);
	fractal_rendering(f);
}

char	*get_palette_mode_label(char mode)
{
	if (mode == 'N')
		return ("Normal");
	if (mode == 'L')
		return ("Logarithmic");
	if (mode == 'A')
		return ("Adaptive");
	if (mode == 'F')
		return ("Fixed_Log");
	if (mode == 'C')
		return ("Cyclic");
	return ("Unknown");
}

