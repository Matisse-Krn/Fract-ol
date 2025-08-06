#include "fractol.h"

static void	set_preset10(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "19") || !ft_strcmp(arg, "a")
		|| !ft_strcmp(arg, "airplane"))
	{
		f->c.real = -0.39054;
		f->c.imag = 0.58679;
		f->init_c_real = "-0.39054";
		f->init_c_imag = "0.58679"; // Airplane
		ft_printf("\t\t✈️  Julia preset : Airplane "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
}

static void	set_preset9(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "17") || !ft_strcmp(arg, "o")
		|| !ft_strcmp(arg, "cauliflower_neg"))
	{
		f->c.real = -0.8;
		f->c.imag = -0.156;
		f->init_c_real = "-0.8";
		f->init_c_imag = "-0.156"; // Cauliflower (négatif)
		ft_printf("\t\t🥦 Julia preset : Cauliflower (Neg) "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else if (!ft_strcmp(arg, "18") || !ft_strcmp(arg, "g")
		|| !ft_strcmp(arg, "golden") || !ft_strcmp(arg, "golden_mean"))
	{
		f->c.real = -0.618;
		f->c.imag = 0.0;
		f->init_c_real = "-0.618";
		f->init_c_imag = "0.0"; // Siegel disk (Golden Mean)
		ft_printf("\t\t💛 Julia preset : Siegel (Golden Mean) "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else
		set_preset10(arg, f);
}

static void	set_preset8(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "15") || !ft_strcmp(arg, "y")
		|| !ft_strcmp(arg, "filaments2"))
	{
		f->c.real = -1.34882125854492;
		f->c.imag = -0.454237874348958;
		f->init_c_real = "-1.34882125854492";
		f->init_c_imag = "-0.454237874348958"; // Filaments region
		ft_printf("\t\t🧬 Julia preset : Filaments Region "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else if (!ft_strcmp(arg, "16") || !ft_strcmp(arg, "h")
		|| !ft_strcmp(arg, "antennae"))
	{
		f->c.real = -1.768778833;
		f->c.imag = -0.001738996;
		f->init_c_real = "-1.768778833";
		f->init_c_imag = "-0.001738996"; // Filaments - hors zone classique
		ft_printf("\t\t👾 Julia preset : Antennae "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else
		set_preset9(arg, f);
}

static void	set_preset7(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "13") || !ft_strcmp(arg, "a")
		|| !ft_strcmp(arg, "airplane"))
	{
		f->c.real = -0.39054;
		f->c.imag = 0.58679;
		f->init_c_real = "-0.39054";
		f->init_c_imag = "0.58679"; // Siegel Disk
		ft_printf("\t\t🟡 Julia preset : Siegel Disk "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else if (!ft_strcmp(arg, "14") || !ft_strcmp(arg, "k")
		|| !ft_strcmp(arg, "cactus"))
	{
		f->c.real = -0.835;
		f->c.imag = -0.2321;
		f->init_c_real = "-0.835";
		f->init_c_imag = "-0.2321"; // Cactus
		ft_printf("\t\t🌵 Julia preset : Cactus "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else
		set_preset8(arg, f);
}

void	set_preset6(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "11") || !ft_strcmp(arg, "v")
		|| !ft_strcmp(arg, "spiral_valley"))
	{
		f->c.real = 0.355534;
		f->c.imag = -0.337292;
		f->init_c_real = "0.355534";
		f->init_c_imag = "-0.337292"; // Spiral Valley (variante)
		ft_printf("\t\t🌊 Julia preset : Spiral Valley "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else if (!ft_strcmp(arg, "12") || !ft_strcmp(arg, "q")
		|| !ft_strcmp(arg, "diagonal") || !ft_strcmp(arg, "quadratic"))
	{
		f->c.real = 0.355;
		f->c.imag = 0.355;
		f->init_c_real = "0.355";
		f->init_c_imag = "0.355"; // Diagonal symmetry
		ft_printf("\t\t🟪 Julia preset : Diagonal Symmetry/Quadratic "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else
		set_preset7(arg, f);
}
