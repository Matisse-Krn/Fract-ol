#include "fractol.h"

void	put_a_string(int x, int y, char *s, t_fractal *fractal)
{
	if (fractal->img.height > y && fractal->img.width > x)
	{
		mlx_string_put(fractal->mlx_ptr, fractal->win_ptr,
			x, y, 0xFFFFFF, s);
	}
}

static void	put_position(t_fractal *f)
{
	char	*x_str;
	char	*y_str;
	char	*line;

	x_str = ft_dtoa(f->shift_x, 4);
	if_malloc_error(x_str);
	y_str = ft_dtoa(f->shift_y, 4);
	if_malloc_error(y_str);
	line = ft_strjoin("Position : ", x_str);
	free(x_str);
	if_malloc_error(line);
	line = str_append(line, ", ");
	if_malloc_error(line);
	line = str_append(line, y_str);
	free(y_str);
	if_malloc_error(line);
	put_a_string(5, 85, line, f);
	free(line);
}

void	put_zoom_and_position(t_fractal *f)
{
	char	*zoom;
	char	*line;

	zoom = ft_dtoa(f->zoom_rate, 2);
	if_malloc_error(zoom);
	line = ft_strjoin("Zoom : x", zoom);
	free(zoom);
	if_malloc_error(line);
	put_a_string(5, 70, line, f);
	free(line);
	put_position(f);
}
