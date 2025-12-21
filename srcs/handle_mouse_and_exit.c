#include "fractol.h"

int	handle_exit(t_fractal *fractal)
{
	if (fractal->bb_hist || fractal->bb_hist_r
		|| fractal->bb_hist_g || fractal->bb_hist_b)
		bb_free_histograms(fractal);

	if (fractal->img.img_ptr)
	{
		img_lock_destroy(&fractal->img);
		mlx_destroy_image(fractal->mlx_ptr, fractal->img.img_ptr);
	}
	if (fractal->win_ptr)
		mlx_destroy_window(fractal->mlx_ptr, fractal->win_ptr);
	if (fractal->mlx_ptr)
	{
		mlx_destroy_display(fractal->mlx_ptr);
		free(fractal->mlx_ptr);
	}

	if (fractal->last_pos && fractal->last_pos[0] != '\0')
		free(fractal->last_pos);
	ft_printf("👋 Exiting the program. See ya' ! 👋\n");
	exit(EXIT_SUCCESS);
	return (0);
}

int	handle_mouse_julia_mandelbrot(int button, int x, int y, t_fractal *fractal)
{
	if (button == Button5)
		apply_zoom(fractal, x, y, 0.8);
	else if (button == Button4)
		apply_zoom(fractal, x, y, 1.2);
	else if (button == Button3)
		apply_zoom(fractal, x, y, 0.2);
	else if (button == Button1)
		apply_zoom(fractal, x, y, 1.8);
	return (0);
}

int	handle_mouse_move(int x, int y, t_fractal *fractal)
{
	char	*x_str;
	char	*y_str;
	char	*tmp;

	if (fractal->last_pos && fractal->last_pos[0] != '\0')
		free(fractal->last_pos);
	x_str = ft_itoa(x);
	if_malloc_error(x_str);
	y_str = ft_itoa(y);
	if_malloc_error(y_str);
	tmp = ft_strjoin("Mouse position : x = ", x_str);
	free(x_str);
	if_malloc_error(tmp);
	fractal->last_pos = ft_strjoin(tmp, "  y = ");
	free(tmp);
	if_malloc_error(fractal->last_pos);
	tmp = fractal->last_pos;
	fractal->last_pos = ft_strjoin(tmp, y_str);
	free(tmp);
	free(y_str);
	if_malloc_error(fractal->last_pos);
	manage_text(fractal);
	return (0);
}

