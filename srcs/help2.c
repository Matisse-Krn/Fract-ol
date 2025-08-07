#include "fractol.h"

static void	print_other_notes2(void)
{
	ft_putstr_fd("\t\t- Use '-mt=no' to disable threads (for "
		"debug/compatibility).\n", 2);
	ft_putstr_fd("\t\t- Use '-f' for fullscreen mode (useful for "
		"screenshots).\n", 2);
	ft_putstr_fd("\t\t- For Julia, type 'julia <preset>' for a quick "
		"start with beautiful examples.\n", 2);
	ft_putstr_fd("\t\t- In Sierpinski, you can specify depth as a third "
		"argument.\n", 2);
	ft_putstr_fd("\t\t- All displayed parameters can be copy-pasted to "
		"share or reproduce a view.\n", 2);
	ft_putstr_fd("\t\t- Command-line parsing is case-insensitive (try "
		"'rabbit', 'RABBIT', or '2').\n", 2);
	ft_putstr_fd("\t\t- Some color schemes and palettes may reveal hidden "
		"fractal structures.\n", 2);
	ft_putstr_fd("\t\t- Conversely, they can attenuate the rendering "
		"(manipulate [S], [TAB], [SPACE],...).\n", 2);
	ft_putstr_fd("\t\t- For bug reports or feedback, contact the "
		"author via github (https://github.com/Matisse-Krn).\n", 2);
	ft_putstr_fd("\t\t- Use '--help' for this manual anytime.\n\n", 2);
}

void	print_other_notes(void)
{
	ft_putstr_fd(BOLD BLUE UNDERLINE"\n\nOther notes :"RST"\n", 2);
	ft_putstr_fd("\t\t- Mouse cursor position is displayed in real "
		"time (top left).\n", 2);
	ft_putstr_fd("\t\t- Fractal parameters (zoom, position, iterations) "
		"are shown live.\n", 2);
	ft_putstr_fd("\t\t- Press 'H' in Mandelbrot/Julia for help overlay.\n", 2);
	ft_putstr_fd("\t\t- All keyboard shortcuts are displayed at the bottom "
		"of the window.\n", 2);
	ft_putstr_fd("\t\t- Psychedelic mode ('Space') toggles vivid and animated "
		"colors.\n", 2);
	ft_putstr_fd("\t\t- Color modes: normal, red, green, blue, yellow, orange, "
		"pink, cyan.\n", 2);
	ft_putstr_fd("\t\t- Preset/jump-to selection is available at launch or in "
		"real-time (see manual).\n", 2);
	ft_putstr_fd("\t\t- Export with 'E' writes a PNG (with current view in "
		"fullscreen and params in filename).\n", 2);
	ft_putstr_fd("\t\t- Multi-threading is enabled by default for best "
		"performance.\n", 2);
	print_other_notes2();
}

void	print_reminder_shortcuts(void)
{
	ft_putstr_fd(BOLD BLUE UNDERLINE"\n\nShortcuts (while running):"RST"\n", 2);
	ft_putstr_fd("\t\tArrow keys : Pan/Move\n", 2);
	ft_putstr_fd("\t\tScroll Up : Zoom in\n", 2);
	ft_putstr_fd("\t\tScroll Down : Zoom out\n", 2);
	ft_putstr_fd("\t\tLClick / RClick : Big zoom in/out\n", 2);
	ft_putstr_fd("\t\tBackspace : Reset view\n", 2);
	ft_putstr_fd("\t\tTab : Reverse color mode\n", 2);
	ft_putstr_fd("\t\tSpace : Psychedelic mode ON/OFF\n", 2);
	ft_putstr_fd("\t\t+ / - : Change contrast\n", 2);
	ft_putstr_fd("\t\tKp+ / Kp- : Change max iterations\n", 2);
	ft_putstr_fd("\t\tN : Normal Colors\n", 2);
	ft_putstr_fd("\t\tR : Red\n", 2);
	ft_putstr_fd("\t\tG : Green\n", 2);
	ft_putstr_fd("\t\tB : Blue\n", 2);
	ft_putstr_fd("\t\tY : Yellow\n", 2);
	ft_putstr_fd("\t\tO : Orange\n", 2);
	ft_putstr_fd("\t\tP : Pink\n", 2);
	ft_putstr_fd("\t\tC : Cyan\n", 2);
	ft_putstr_fd("\t\tE : Export PNG\n", 2);
}

void	print_mandelbrot_presets(void)
{
	ft_putstr_fd(BOLD BLUE UNDERLINE"\n\nMandelbrot 'jump-to' presets "
		"(during run):"RST"\n", 2);
	ft_putstr_fd("\t\tPress '"BOLD"J"RST"' in Mandelbrot to enter 'jump-to' "
		"mode and display the list in terminal.\n", 2);
	ft_putstr_fd("\t\tThen, press keys [1] to [9] to jump to "
		"classic regions:\n", 2);
	ft_putstr_fd("\t\t1 : Main Cardioid         (-0.6, 0.0)\n", 2);
	ft_putstr_fd("\t\t2 : Seahorse Valley       (-0.745, 0.115)\n", 2);
	ft_putstr_fd("\t\t3 : Elephant Valley       (0.285, 0.01)\n", 2);
	ft_putstr_fd("\t\t4 : Triple Spiral         (-0.748, 0.1)\n", 2);
	ft_putstr_fd("\t\t5 : Tendrils (Neuron)     "
		"(-0.74364388703, 0.13182590421)\n", 2);
	ft_putstr_fd("\t\t6 : Mini Mandelbrot SE    (-1.25, 0.2)\n", 2);
	ft_putstr_fd("\t\t7 : Period-3 Bulb         (-1.75, 0.0)\n", 2);
	ft_putstr_fd("\t\t8 : Basilica              (-0.1015, 0.633)\n", 2);
	ft_putstr_fd("\t\t9 : Antennae              (-0.2, 1.0)\n", 2);
}
