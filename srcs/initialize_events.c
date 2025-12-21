#include "fractol.h"

static void	initialize_events_julia_mandelbrot(t_fractal *fractal)
{
	mlx_hook(fractal->win_ptr,
		DestroyNotify,
		StructureNotifyMask,
		handle_exit, fractal);
	mlx_hook(fractal->win_ptr,
		KeyPress,
		KeyPressMask,
		handle_key_julia_mandelbrot, fractal);
	mlx_hook(fractal->win_ptr,
		MotionNotify,
		PointerMotionMask,
		handle_mouse_move, fractal);
	mlx_hook(fractal->win_ptr,
		ButtonPress,
		ButtonPressMask,
		handle_mouse_julia_mandelbrot, fractal);
}

static void	initialize_events_buddhabrot(t_fractal *fractal)
{
	mlx_hook(fractal->win_ptr,
		DestroyNotify,
		StructureNotifyMask,
		handle_exit, fractal);
	mlx_hook(fractal->win_ptr,
		KeyPress,
		KeyPressMask,
		handle_key_buddhabrot, fractal);
	mlx_hook(fractal->win_ptr,
		MotionNotify,
		PointerMotionMask,
		handle_mouse_move, fractal);
}

void	initialize_events(t_fractal *fractal)
{
	if (!ft_strcmp(fractal->name, "sierpinski"))
	{
		initialize_events_sierpinski(fractal);
		return ;
	}
	if (!ft_strcmp(fractal->name, "buddhabrot"))
	{
		initialize_events_buddhabrot(fractal);
		return ;
	}
	if (!ft_strcmp(fractal->name, "sierpinski"))
		initialize_events_julia_mandelbrot(fractal);
}
