#include "fractol.h"

/**
 * @brief  Assigns the complex parameters for the Julia fractal.
 *
 * Initializes the complex constant `c` for the Julia set from either a preset
 * name/number or user-provided numeric values. If the provided argument matches
 * a known preset, the corresponding parameters are set. Otherwise, the input
 * is validated and converted from strings to floating-point values.
 *
 * @param  argv  Command-line arguments, where argv[2] and argv[3] may contain
 *               preset names or numeric values for the Julia set parameters.
 * @param  f     Pointer to the fractal context (`t_fractal`) to update.
 * @return None.
 *
 * @note   Calls `set_preset()` to check for matching presets before falling
 *         back to manual numeric assignment.
 * @pre    `argv` must contain at least three valid elements.
 * @post   The fields `c.real`, `c.imag`, `init_c_real`, and `init_c_imag`
 *         are updated in the fractal context.
 */
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
