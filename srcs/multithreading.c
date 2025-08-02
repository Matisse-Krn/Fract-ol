#include "fractol.h"

int	get_multi_thread(void)
{
	int		ret;
	char	buf[2];

	ret = FALSE;
	write(1, "\nActivate multi-threading ? Yes/No :  ", 38);
	while (read(0, buf, 1) > 0)
	{
		if (!ft_strncmp(buf, "y", 1) || !ft_strncmp(buf, "Y", 1))
			ret = TRUE;
		else if (!ft_strncmp(buf, "n", 1) || !ft_strncmp(buf, "N", 1))
			break ;
		else
		{
			write(1, "Retry :\n\ny/Y/yes/YES  or  n/N/no/No\n", 36);
			write(1, "\nActivate multi-threading ? Yes/No : ", 38);
			continue ;
		}
		break ;
	}
	write(1, "\n", 1);
	return (ret);
}

static void	pixel_partial_loop(char type, t_fractal *fractal, int y_start, int y_end)
{
	t_pixel	pixel;

	pixel.y = y_start - 1;
	if (type == 'M')
	{
		while (++(pixel.y) < y_end)
		{
			pixel.x = -1;
			while (++(pixel.x) < fractal->img.width)
				handle_pixel_mandelbrot(&pixel, fractal);
		}
	}
	else if (type == 'J')
	{
		while (++(pixel.y) < y_end)
		{
			pixel.x = -1;
			while (++(pixel.x) < fractal->img.width)
				handle_pixel_julia(&pixel, fractal);
		}
	}
}

static void	*thread_routine(void *arg)
{
	t_thread_args	*args;

	args = (t_thread_args *)arg;
	pixel_partial_loop(args->type, args->fractal, args->y_start, args->y_end);
	return (NULL);
}

int	init_threads(t_fractal *fractal)
{
	pthread_t		*threads;
	t_thread_args	*args;
	long			n_threads;
	int				i;

	n_threads = sysconf(_SC_NPROCESSORS_ONLN);
	if (n_threads > 16)
		n_threads = 16;

	threads = ft_calloc(n_threads, sizeof(pthread_t));
	if (!threads)
		return (FALSE);
	args = ft_calloc(n_threads, sizeof(t_thread_args));
	if (!threads)
		return (FALSE);
	


	i = -1;
	while (++i < n_threads)
	{
		args[i].fractal = fractal;
		if (!ft_strcmp(fractal->name, "mandelbrot"))
			args[i].type = 'M';
		else if (!ft_strcmp(fractal->name, "julia"))
			args[i].type = 'J';
		args[i].y_start = i * (fractal->img.height / n_threads);
		if (i == n_threads - 1)
			args[i].y_end = fractal->img.height; /*   ( h )   */
		else
			args[i].y_end = (i + 1) * (fractal->img.height / n_threads);
		if (pthread_create(&threads[i], NULL, thread_routine, &args[i]))
		{
			while (--i >= 0)
				pthread_join(threads[i], NULL);
			return (FALSE);
		}
	}
	

	i = -1;
	while (++i < n_threads)
		pthread_join(threads[i], NULL);
	return (TRUE);
}
