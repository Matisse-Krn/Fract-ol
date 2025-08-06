#include "fractol.h"

static void	set_preset5(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "9") || !ft_strcmp(arg, "c")
		|| !ft_strcmp(arg, "cauliflower"))
	{
		f->c.real = -0.8;
		f->c.imag = 0.156;
		f->init_c_real = "-0.8";
		f->init_c_imag = "0.156"; // Cauliflower
		ft_printf("\t\t🥦 Julia preset : Cauliflower "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else if (!ft_strcmp(arg, "10") || !ft_strcmp(arg, "m")
		|| !ft_strcmp(arg, "heart") || !ft_strcmp(arg, "mandelbrot_heart"))
	{
		f->c.real = -0.7269;
		f->c.imag = 0.1889;
		f->init_c_real = "-0.7269";
		f->init_c_imag = "0.1889"; // Mandelbrot Heart
		ft_printf("\t\t💖 Julia preset : Mandelbrot Heart "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else
		set_preset6(arg, f);
}

static void	set_preset4(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "7") || !ft_strcmp(arg, "f")
		|| !ft_strcmp(arg, "filaments") || !ft_strcmp(arg, "biomorph"))
	{
		f->c.real = -0.4;
		f->c.imag = 0.6;
		f->init_c_real = "-0.4";
		f->init_c_imag = "0.6"; // Biomorph / Filaments
		ft_printf("\t\t🪴 Julia preset : Biomorph/Filaments "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else if (!ft_strcmp(arg, "8") || !ft_strcmp(arg, "n")
		|| !ft_strcmp(arg, "snowflake") || !ft_strcmp(arg, "frosty"))
	{
		f->c.real = -0.8;
		f->c.imag = 0.2;
		f->init_c_real = "-0.8";
		f->init_c_imag = "0.2"; // Snowflake / Frosty
		ft_printf("\t\t❄️  Julia preset : Snowflake (Frosty) "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else
		set_preset5(arg, f);
}

static void	set_preset3(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "5") || !ft_strcmp(arg, "e")
		|| !ft_strcmp(arg, "eye"))
	{
		f->c.real = 0.37;
		f->c.imag = 0.1;
		f->init_c_real = "0.37";
		f->init_c_imag = "0.1";
		ft_printf("\t\t👁️  Julia preset : Eye "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else if (!ft_strcmp(arg, "6") || !ft_strcmp(arg, "b")
		|| !ft_strcmp(arg, "basilica"))
	{
		f->c.real = -1.0;
		f->c.imag = 0.0;
		f->init_c_real = "-1.0";
		f->init_c_imag = "0.0";
		ft_printf("\t\t⛪ Julia preset : Basilica "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else
		set_preset4(arg, f);
}

static void	set_preset2(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "3") || !ft_strcmp(arg, "t")
		|| !ft_strcmp(arg, "tuning") || !ft_strcmp(arg, "tuning_fork"))
	{
		f->c.real = 0.285;
		f->c.imag = 0.01;
		f->init_c_real = "0.285";
		f->init_c_imag = "0.01";
		ft_printf("\t\t🎼 Julia preset : Tuning Fork "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else if (!ft_strcmp(arg, "4") || !ft_strcmp(arg, "s")
		|| !ft_strcmp(arg, "spiral"))
	{
		f->c.real = -0.76;
		f->c.imag = 0.1;
		f->init_c_real = "-0.76";
		f->init_c_imag = "0.1";
		ft_printf("\t\t🌀 Julia preset : Spiral "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else
		set_preset3(arg, f);
}

void	set_preset(char *arg, t_fractal *f)
{
	if (!arg)
		return ;
	if (!ft_strcmp(arg, "1") || !ft_strcmp(arg, "d")
		|| !ft_strcmp(arg, "dendrite"))
	{
		f->c.real = -0.70176;
		f->c.imag = -0.3842;
		f->init_c_real = "-0.70176";
		f->init_c_imag = "-0.3842";
		ft_printf("\t\t🦠 Julia preset : Dendrite "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else if (!ft_strcmp(arg, "2") || !ft_strcmp(arg, "r")
		|| !ft_strcmp(arg, "rabbit"))
	{
		f->c.real = -0.123;
		f->c.imag = 0.745;
		f->init_c_real = "-0.123";
		f->init_c_imag = "0.745";
		ft_printf("\t\t🐇 Julia preset : Douady Rabbit "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else
		set_preset2(arg, f);
}
