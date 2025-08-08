#include "fractol.h"

static int	pixel_part_scan(char type, t_fractal *f, int y_start, int y_end)
{
	t_pixel	p;
	int		it;
	int		max;

	max = 0;
	p.y = y_start - 1;
	while (++(p.y) < y_end)
	{
		p.x = -1;
		while (++(p.x) < f->img.width)
		{
			if (type == 'M')
				it = iters_to_diverge_mandelbrot(&p, f);
			else
				it = iters_to_diverge_julia(&p, f);
			if (it < f->max_iterations && it > max)
				max = it;
		}
	}
	return (max);
}

static void	*scan_thread_routine(void *arg)
{
	t_thread_args	*args;

	args = (t_thread_args *)arg;
	args->local_max = pixel_part_scan(args->type, args->fractal,
			args->y_start, args->y_end);
	return (NULL);
}

static int	loop_init_threads_scan(long n_threads, pthread_t *threads,
						t_thread_args *args, t_fractal *f)
{
	int	i;

	i = -1;
	while (++i < n_threads)
	{
		args[i].fractal = f;
		if (!ft_strcmp(f->name, "mandelbrot"))
			args[i].type = 'M';
		else if (!ft_strcmp(f->name, "julia"))
			args[i].type = 'J';
		args[i].y_start = i * (f->img.height / n_threads);
		if (i == n_threads - 1)
			args[i].y_end = f->img.height;
		else
			args[i].y_end = (i + 1) * (f->img.height / n_threads);
		args[i].local_max = 0;
		if (pthread_create(&threads[i], NULL, scan_thread_routine, &args[i]))
		{
			while (--i >= 0)
				pthread_join(threads[i], NULL);
			return (FALSE);
		}
	}
	return (TRUE);
}

int	find_imax_frame_mt(t_fractal *f)
{
	pthread_t		*threads;
	t_thread_args	*args;
	long			n_threads;
	int				i;

	f->i_max = 0;
	n_threads = sysconf(_SC_NPROCESSORS_ONLN) * 4;
	threads = (pthread_t *)ft_calloc(n_threads, sizeof(pthread_t));
	if (!threads)
		return (FALSE);
	args = (t_thread_args *)ft_calloc(n_threads, sizeof(t_thread_args));
	if (!args)
		return (free(threads), FALSE);
	if (loop_init_threads_scan(n_threads, threads, args, f) == FALSE)
		return (free(threads), free(args), FALSE);
	i = -1;
	while (++i < n_threads)
		pthread_join(threads[i], NULL);
	i = -1;
	while (++i < n_threads)
	{
		if (args[i].local_max > f->i_max)
			f->i_max = args[i].local_max;
	}
	return (free(threads), free(args), TRUE);
}

void	compute_imax_for_export(t_fractal *f)
{
	if (f->render_mode != 'A')
		return ;
	f->i_max = 0;
	if (f->mt == FALSE)
	{
		if (!ft_strcmp(f->name, "mandelbrot"))
			find_imax_frame('M', f);
		else if (!ft_strcmp(f->name, "julia"))
			find_imax_frame('J', f);
	}
	else
	{
		if (find_imax_frame_mt(f) == FALSE)
			return ;
	}
}
