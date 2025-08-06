#include "fractol.h"

/*static int	is_julia_preset(char *arg)*/
/*{*/
	 /*//	- Check if is `./fractol julia dendrite`*/
/*	if (!arg)*/
/*		return (FALSE);*/
/*	if (!ft_strcmp(arg, "dendrite"))*/
/*		return (TRUE);*/
/*	else if (!ft_strcmp(arg, "douady"))*/
/*		return (TRUE);*/
/*	else if (!ft_strcmp(arg, "tuning_fork"))*/
/*		return (TRUE);*/
/*	else if (!ft_strcmp(arg, "spiral"))*/
/*		return (TRUE);*/
/*	else if (!ft_strcmp(arg, "eye"))*/
/*		return (TRUE);*/
/*	else if (!ft_strcmp(arg, "basilica"))*/
/*		return (TRUE);*/
/*	else if (!ft_strcmp(arg, "biomorph"))*/
/*		return (TRUE);*/
/*	else if (!ft_strcmp(arg, "snowflake"))*/
/*		return (TRUE);*/
/*	else if (!ft_strcmp(arg, "cauliflower"))*/
/*		return (TRUE);*/
/*	return (FALSE);*/
/*}*/

void	assign_params(int argc, char **argv, t_fractal *f)
{
	/*
	 *	- Check if is `./fractol julia d`
	 *	- Check if is `./fractol julia dendrite`
	 *	- Check if is `./fractol julia 2` (for example)
	 *	- Check if is `./fractol julia -0.70176 -0.3842`
	*/

	/*if (argc >= 3 && ft_strlen(argv[2]) == 1 && !is_digit(*argv[2]))*/
		/*set_preset_by_letter(argv[2], f);*/
	/*else if (argc >= 3 && is_digit(*argv[2]) && (argc >= 4 && !is_digit(*argv[3])))*/
	/*else if (argc >= 3 && is_julia_preset(argv[2]))*/
		/*set_preset_by_name(argv[2], f);*/
	



	(void)argc;




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
