#include "fractol.h"

/**
 * @brief  Sets Julia fractal parameters for preset ID 19 (Airplane).
 *
 * Matches the given argument against preset identifiers or aliases
 * for the Airplane Julia set, then assigns the corresponding complex
 * constant values to the fractal context.
 *
 * @param  arg  Preset identifier or alias (string).
 * @param  f    Pointer to the fractal context (`t_fractal`) to update.
 * @return None.
 *
 * @note   Prints the selected preset’s name and parameters to the terminal.
 * @pre    `arg` must not be NULL.
 * @post   Updates `c.real`, `c.imag`, and related initial parameter strings.
 */
static void	set_preset10(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "19") || !ft_strcmp(arg, "a")
		|| !ft_strcmp(arg, "airplane"))
	{
		f->c.real = -0.39054;
		f->c.imag = 0.58679;
		f->init_c_real = "-0.39054";
		f->init_c_imag = "0.58679";
		ft_printf("\t\t✈️  Julia preset : Airplane "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
}

/**
 * @brief  Sets Julia fractal parameters for presets 17–18 or forwards to next.
 *
 * Matches the given argument against preset identifiers or aliases
 * for the Cauliflower (Negative) or Siegel (Golden Mean) Julia sets,
 * and assigns the corresponding complex constant values.
 * If no match is found, passes control to `set_preset10()`.
 *
 * @param  arg  Preset identifier or alias (string).
 * @param  f    Pointer to the fractal context (`t_fractal`) to update.
 * @return None.
 *
 * @note   Prints the selected preset’s name and parameters to the terminal.
 * @pre    `arg` must not be NULL.
 * @post   Updates `c.real`, `c.imag`, and related initial parameter strings.
 */
static void	set_preset9(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "17") || !ft_strcmp(arg, "o")
		|| !ft_strcmp(arg, "cauliflower_neg"))
	{
		f->c.real = -0.8;
		f->c.imag = -0.156;
		f->init_c_real = "-0.8";
		f->init_c_imag = "-0.156";
		ft_printf("\t\t🥦 Julia preset : Cauliflower (Neg) "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else if (!ft_strcmp(arg, "18") || !ft_strcmp(arg, "g")
		|| !ft_strcmp(arg, "golden") || !ft_strcmp(arg, "golden_mean"))
	{
		f->c.real = -0.618;
		f->c.imag = 0.0;
		f->init_c_real = "-0.618";
		f->init_c_imag = "0.0";
		ft_printf("\t\t💛 Julia preset : Siegel (Golden Mean) "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else
		set_preset10(arg, f);
}

/**
 * @brief  Sets Julia fractal parameters for presets 15–16 or forwards to next.
 *
 * Matches the given argument against preset identifiers or aliases
 * for the Filaments Region or Antennae Julia sets, then assigns
 * the corresponding complex constant values.
 * If no match is found, passes control to `set_preset9()`.
 *
 * @param  arg  Preset identifier or alias (string).
 * @param  f    Pointer to the fractal context (`t_fractal`) to update.
 * @return None.
 *
 * @note   Prints the selected preset’s name and parameters to the terminal.
 * @pre    `arg` must not be NULL.
 * @post   Updates `c.real`, `c.imag`, and related initial parameter strings.
 */
static void	set_preset8(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "15") || !ft_strcmp(arg, "y")
		|| !ft_strcmp(arg, "filaments2"))
	{
		f->c.real = -1.34882125854492;
		f->c.imag = -0.454237874348958;
		f->init_c_real = "-1.34882125854492";
		f->init_c_imag = "-0.454237874348958";
		ft_printf("\t\t🧬 Julia preset : Filaments Region "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else if (!ft_strcmp(arg, "16") || !ft_strcmp(arg, "h")
		|| !ft_strcmp(arg, "antennae"))
	{
		f->c.real = -1.768778833;
		f->c.imag = -0.001738996;
		f->init_c_real = "-1.768778833";
		f->init_c_imag = "-0.001738996";
		ft_printf("\t\t👾 Julia preset : Antennae "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else
		set_preset9(arg, f);
}

/**
 * @brief  Sets Julia fractal parameters for presets 13–14 or forwards to next.
 *
 * Matches the given argument against preset identifiers or aliases
 * for the Siegel Disk or Cactus Julia sets, then assigns
 * the corresponding complex constant values.
 * If no match is found, passes control to `set_preset8()`.
 *
 * @param  arg  Preset identifier or alias (string).
 * @param  f    Pointer to the fractal context (`t_fractal`) to update.
 * @return None.
 *
 * @note   Prints the selected preset’s name and parameters to the terminal.
 * @pre    `arg` must not be NULL.
 * @post   Updates `c.real`, `c.imag`, and related initial parameter strings.
 */
static void	set_preset7(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "13") || !ft_strcmp(arg, "a")
		|| !ft_strcmp(arg, "airplane"))
	{
		f->c.real = -0.39054;
		f->c.imag = 0.58679;
		f->init_c_real = "-0.39054";
		f->init_c_imag = "0.58679";
		ft_printf("\t\t🟡 Julia preset : Siegel Disk "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else if (!ft_strcmp(arg, "14") || !ft_strcmp(arg, "k")
		|| !ft_strcmp(arg, "cactus"))
	{
		f->c.real = -0.835;
		f->c.imag = -0.2321;
		f->init_c_real = "-0.835";
		f->init_c_imag = "-0.2321";
		ft_printf("\t\t🌵 Julia preset : Cactus "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else
		set_preset8(arg, f);
}

/**
 * @brief  Sets Julia fractal parameters for presets 11–12 or forwards to next.
 *
 * Matches the given argument against preset identifiers or aliases
 * for the Spiral Valley or Diagonal Symmetry/Quadratic Julia sets,
 * then assigns the corresponding complex constant values.
 * If no match is found, passes control to `set_preset7()`.
 *
 * @param  arg  Preset identifier or alias (string).
 * @param  f    Pointer to the fractal context (`t_fractal`) to update.
 * @return None.
 *
 * @note   Prints the selected preset’s name and parameters to the terminal.
 * @pre    `arg` must not be NULL.
 * @post   Updates `c.real`, `c.imag`, and related initial parameter strings.
 */
void	set_preset6(char *arg, t_fractal *f)
{
	if (!ft_strcmp(arg, "11") || !ft_strcmp(arg, "v")
		|| !ft_strcmp(arg, "spiral_valley"))
	{
		f->c.real = 0.355534;
		f->c.imag = -0.337292;
		f->init_c_real = "0.355534";
		f->init_c_imag = "-0.337292";
		ft_printf("\t\t🌊 Julia preset : Spiral Valley "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else if (!ft_strcmp(arg, "12") || !ft_strcmp(arg, "q")
		|| !ft_strcmp(arg, "diagonal") || !ft_strcmp(arg, "quadratic"))
	{
		f->c.real = 0.355;
		f->c.imag = 0.355;
		f->init_c_real = "0.355";
		f->init_c_imag = "0.355";
		ft_printf("\t\t🟪 Julia preset : Diagonal Symmetry/Quadratic "
			"[%s, %s]\n", f->init_c_real, f->init_c_imag);
	}
	else
		set_preset7(arg, f);
}
