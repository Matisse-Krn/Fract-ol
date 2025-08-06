#include "fractol.h"

void	switch_render_mode(t_fractal *f)
{
	if (f->render_mode == 'N')
		f->render_mode = 'L';
	else if (f->render_mode == 'L')
		f->render_mode = 'A';
	else if (f->render_mode == 'A')
		f->render_mode = 'F';
	else if (f->render_mode == 'F')
		f->render_mode = 'C';
	else
		f->render_mode = 'N';

	ft_putstr_fd("Render mode switched to : ", 1);
	if (f->render_mode == 'N')
		ft_putstr_fd("Normal (exponential)\n", 1);
	else if (f->render_mode == 'L')
		ft_putstr_fd("Logarithmic scale\n", 1);
	else if (f->render_mode == 'A')
		ft_putstr_fd("Adaptive (based on max i)\n", 1);
	else if (f->render_mode == 'F')
		ft_putstr_fd("Fixed log(i)/log(1000)\n", 1);
	else if (f->render_mode == 'C')
		ft_putstr_fd("Cyclic modulo color\n", 1);
	fractal_rendering(f);
}

char	*get_render_mode_label(char mode)
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

