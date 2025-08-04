#include "fractol.h"

void	jump_menu(void)
{
	ft_putstr_fd("\n🌌 "BOLD"Jump-to Presets (Mandelbrot only)"RST"\n\n", 1);
	ft_putstr_fd("\t[1] Main Cardioid       → x = -0.6,  y = 0.0\n", 1);
	ft_putstr_fd("\t[2] Seahorse Valley     → x = -0.745, y = 0.115\n", 1);
	ft_putstr_fd("\t[3] Elephant Valley     → x = 0.285,  y = 0.01\n", 1);
	ft_putstr_fd("\t[4] Triple Spiral        → x = -0.748, y = 0.1\n", 1);
	ft_putstr_fd("\t[5] Tendrils (Neuron)   → x = -0.74364388703, y = 0.13182590421\n", 1);
	ft_putstr_fd("\t[6] Mini Mandelbrot SE  → x = -1.25, y = 0.2\n", 1);
	ft_putstr_fd("\t[7] Period-3 Bulb       → x = -1.75, y = 0.0\n", 1);
	ft_putstr_fd("\t[8] Basilica            → x = -0.1015, y = 0.633\n", 1);
	ft_putstr_fd("\t[9] Antennae            → x = -0.2,   y = 1.0\n\n", 1);
	ft_putstr_fd("Press corresponding number key to jump.\n\n", 1);
}

static void	set_position(t_fractal *f, double sx, double sy, double zoom)
{
	f->shift_x = sx;
	f->shift_y = sy;
	f->zoom_rate = zoom;
}

void	handle_jump_choice(t_fractal *f, int choice)
{
	if (ft_strcmp(f->name, "mandelbrot"))
		return ;
	if (choice == 1)
		set_position(f, -0.6, 0.0, 1.6); // Main Cardioid
	else if (choice == 2)
		set_position(f, -0.745, 0.115, 500);
	else if (choice == 3)
		set_position(f, 0.285, 0.01, 500);
	else if (choice == 4)
		set_position(f, -0.748, 0.1, 800);
	else if (choice == 5)
		set_position(f, -0.74364388703, 0.13182590421, 10000);
	else if (choice == 6)
		set_position(f, -1.25, 0.2, 300);
	else if (choice == 7)
		set_position(f, -1.75, 0.0, 15);
	else if (choice == 8)
		set_position(f, -0.1015, 0.633, 250);
	else if (choice == 9)
		set_position(f, -0.2, 1.0, 200);
	else
		return ;
	ft_printf("✨ Jumped to preset [%d]\n", choice);
	fractal_rendering(f);
}
