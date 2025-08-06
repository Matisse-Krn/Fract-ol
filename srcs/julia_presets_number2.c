#include "fractol.h"

static void	set_preset_by_number7(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "19") || !ft_strcmp(arg, "a") || !ft_strcmp(arg, "airplane"))
	{
		f->c.real = -0.39054;
		f->c.imag = 0.58679;
		f->init_c_real = "-0.39054";
		f->init_c_imag = "0.58679"; // Airplane
		ft_printf("\t\t✈️  Julia preset : Airplane [%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
}

void	set_preset_by_number6(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "16") || !ft_strcmp(arg, "h") || !ft_strcmp(arg, "antennae"))
	{
		f->c.real = -1.768778833;
		f->c.imag = -0.001738996;
		f->init_c_real = "-1.768778833";
		f->init_c_imag = "-0.001738996"; // Filaments/antennae, hors zone classique
		ft_printf("\t\t👾 Julia preset : Antennae [%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else if (!ft_strcmp(arg, "17") || !ft_strcmp(arg, "o") || !ft_strcmp(arg, "cauliflower_neg"))
	{
		f->c.real = -0.8;
		f->c.imag = -0.156;
		f->init_c_real = "-0.8";
		f->init_c_imag = "-0.156"; // Cauliflower (négatif)
		ft_printf("\t\t🥦 Julia preset : Cauliflower (Neg) [%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else if (!ft_strcmp(arg, "18") || !ft_strcmp(arg, "g") || !ft_strcmp(arg, "golden") || !ft_strcmp(arg, "golden_mean"))
	{
		f->c.real = -0.618;
		f->c.imag = 0.0;
		f->init_c_real = "-0.618";
		f->init_c_imag = "0.0"; // Siegel disk (Golden Mean)
		ft_printf("\t\t💛 Julia preset : Siegel (Golden Mean) [%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else
		set_preset_by_number7(arg, f);

}
