#include "fractol.h"

void	assign_params(char **argv, t_fractal *f)
{
	f->c.real = 0;
	f->c.imag = 0;
	ft_str_tolower(argv[2]);
	set_preset(argv[2], f);
	if (f->c.real == 0 && f->c.imag == 0)
	{
		check_valid_input_numbers(argv);
		f->c.real = ft_atod(argv[2]);
		f->c.imag = ft_atod(argv[3]);
		f->init_c_real = argv[2];
		f->init_c_imag = argv[3];
	}
}
