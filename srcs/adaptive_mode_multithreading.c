#include "fractol.h"

/**
 * @brief  Scan a section of the image for maximum divergence iterations.
 *
 * Iterates over the pixels in the vertical range `[y_start, y_end)` and
 * calculates the number of iterations to divergence for each pixel,
 * depending on the fractal type (Mandelbrot or Julia). Tracks and
 * returns the highest iteration count found that is below the maximum
 * iteration limit.
 *
 * @param  type     Fractal type: 'M' for Mandelbrot, 'J' for Julia.
 * @param  f        Pointer to the fractal context (`t_fractal`).
 * @param  y_start  Starting row (inclusive) of the scan range.
 * @param  y_end    Ending row (exclusive) of the scan range.
 * @return The maximum iteration count found in the scanned section.
 *
 * @note   Used for adaptive coloring to determine `f->i_max`.
 * @pre    `f` must be initialized with valid rendering parameters.
 * @post   No changes are made to `f`.
 */
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

/**
 * @brief  Thread routine for scanning a section of the fractal image.
 *
 * Executes `pixel_part_scan()` for the section assigned to this thread,
 * storing the result in the thread's local maximum iteration count.
 *
 * @param  arg  Pointer to a `t_thread_args` structure containing the
 *              parameters for this thread's work.
 * @return Always returns NULL (required by pthread interface).
 *
 * @note   This function is designed to be run as a pthread worker.
 * @pre    `arg` must be a valid pointer to initialized thread arguments.
 * @post   The `local_max` field in `t_thread_args` is updated.
 */
static void	*scan_thread_routine(void *arg)
{
	t_thread_args	*args;

	args = (t_thread_args *)arg;
	args->local_max = pixel_part_scan(args->type, args->fractal,
			args->y_start, args->y_end);
	return (NULL);
}

/**
 * @brief  Initialize and start multiple threads for image scanning.
 *
 * Prepares `t_thread_args` for each thread, dividing the image into
 * horizontal sections for parallel scanning. Creates each thread to
 * execute `scan_thread_routine()`. If thread creation fails, joins
 * already-started threads and aborts.
 *
 * @param  n_threads  Number of threads to launch.
 * @param  threads    Pointer to the array of pthread_t handles.
 * @param  args       Pointer to the array of `t_thread_args`.
 * @param  f          Pointer to the fractal context (`t_fractal`).
 * @return TRUE on success, FALSE on failure.
 *
 * @note   The last thread's range may be slightly larger if height
 *         is not divisible by `n_threads`.
 * @pre    Memory for `threads` and `args` must already be allocated.
 * @post   Threads are running and scanning their respective image parts.
 */
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

/**
 * @brief  Compute the maximum divergence iterations using multi-threading.
 *
 * Allocates thread handles and argument structures, launches threads to
 * scan the image in parallel, joins them, and updates `f->i_max` with the
 * highest value found.
 *
 * @param  f  Pointer to the fractal context (`t_fractal`).
 * @return TRUE on success, FALSE on allocation or thread failure.
 *
 * @note   Uses `sysconf(_SC_NPROCESSORS_ONLN) * 4` threads for scanning.
 * @pre    `f` must be initialized with valid rendering parameters.
 * @post   `f->i_max` contains the highest iteration count found.
 */
int	find_imax_frame_mt(t_fractal *f)
{
	pthread_t		*threads;
	t_thread_args	*args;
	long			n_threads;
	int				i;

	f->i_max = 0;
	n_threads = sysconf(_SC_NPROCESSORS_ONLN) * 3;
	if (n_threads < 1)
		return (FALSE);
	if (n_threads > f->img.height)
		n_threads = f->img.height;
	if (n_threads > 32)
		n_threads = 32;
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

/**
 * @brief  Compute `i_max` value when exporting an image.
 *
 * If the render mode is not adaptive ('A'), the function exits without
 * changes. Otherwise, it computes the maximum iteration count in the
 * current frame using either single-threaded or multi-threaded scanning,
 * depending on the `mt` flag.
 *
 * @param  f  Pointer to the fractal context (`t_fractal`).
 * @return None.
 *
 * @note   In single-thread mode, calls `find_imax_frame()`; in multi-thread
 *         mode, calls `find_imax_frame_mt()`.
 * @pre    `f` must be initialized with valid rendering parameters.
 * @post   If applicable, updates `f->i_max` for adaptive rendering.
 */
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
