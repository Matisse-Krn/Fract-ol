#include "fractol.h"

/**
 * @brief  Processes a portion of the image by rendering pixels in
 *		   a specific range.
 *
 * Iterates over a rectangular section of the fractal image between the
 * specified `y_start` and `y_end` rows, processing each pixel according
 * to the fractal type.
 * For Mandelbrot ('M') and Julia ('J'), calls the appropriate pixel
 * handler function.
 *
 * @param  type     Character indicating the fractal type
 *					('M' for Mandelbrot, 'J' for Julia).
 * @param  f        Pointer to the fractal structure containing
 *					rendering parameters.
 * @param  y_start  Starting row index (inclusive) for processing.
 * @param  y_end    Ending row index (exclusive) for processing.
 * @return None.
 *
 * @note   This function does not handle any synchronization; it assumes that the
 *         processed pixel range does not overlap with other threads.
 * @warning Passing an unsupported `type` will result in no rendering.
 * @pre    `f` must be properly initialized and valid.
 * @post   The specified image segment is rendered into `f->img`.
 */
static void	pixel_part_loop(char type, t_fractal *f, int y_start, int y_end)
{
	t_pixel	pixel;

	pixel.y = y_start - 1;
	if (type == 'M')
	{
		while (++(pixel.y) < y_end)
		{
			pixel.x = -1;
			while (++(pixel.x) < f->img.width)
				handle_pixel_mandelbrot(&pixel, f);
		}
	}
	else if (type == 'J')
	{
		while (++(pixel.y) < y_end)
		{
			pixel.x = -1;
			while (++(pixel.x) < f->img.width)
				handle_pixel_julia(&pixel, f);
		}
	}
}

/**
 * @brief  Thread entry point for fractal rendering.
 *
 * Executes the rendering of a specific image section, as defined by
 * the arguments passed in a `t_thread_args` structure.
 *
 * @param  arg  Pointer to a `t_thread_args` structure containing
 *				rendering parameters.
 * @return Always returns NULL.
 *
 * @note   Designed to be used with `pthread_create()`.
 * @warning The pointer passed in `arg` must be valid and remain accessible
 *          for the duration of the thread's execution.
 * @pre    `arg` must point to a valid `t_thread_args` object.
 * @post   The designated section of the fractal image is rendered.
 */
static void	*thread_routine(void *arg)
{
	t_thread_args	*args;

	args = (t_thread_args *)arg;
	pixel_part_loop(args->type, args->fractal, args->y_start, args->y_end);
	return (NULL);
}

/**
 * @brief  Initializes and starts rendering threads.
 *
 * Divides the fractal image vertically into segments, assigns each segment
 * to a thread, and starts all threads for concurrent rendering. Each thread
 * processes a non-overlapping region of the image.
 *
 * @param  n_threads  Number of threads to create.
 * @param  threads    Array of pthread_t to hold created thread IDs.
 * @param  args       Array of `t_thread_args` structures to hold
 *					  thread parameters.
 * @param  fractal    Pointer to the fractal structure containing rendering data.
 * @return TRUE on success, FALSE on failure (thread creation failure will
 *         join and clean up all previously created threads).
 *
 * @note   Last thread handles any remainder rows caused by uneven division.
 * @warning Requires `threads` and `args` arrays of size `n_threads`
 *			to be allocated.
 * @pre    `n_threads` must be > 0 and `fractal` must be initialized.
 * @post   All threads are running and processing assigned sections.
 */
static int	loop_init_threads(long n_threads, pthread_t *threads,
							t_thread_args *args, t_fractal *fractal)
{
	int	i;

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
			args[i].y_end = fractal->img.height;
		else
			args[i].y_end = (i + 1) * (fractal->img.height / n_threads);
		if (pthread_create(&threads[i], NULL, thread_routine, &args[i]))
		{
			while (--i >= 0)
				pthread_join(threads[i], NULL);
			return (FALSE);
		}
	}
	return (TRUE);
}

/**
 * @brief  Creates and manages rendering threads for the fractal.
 *
 * Determines a choosen number of threads based on the system's CPU core count
 * (cores × 4), allocates necessary resources, initializes thread parameters, and
 * launches all rendering threads. Waits for all threads to complete before
 * freeing resources.
 *
 * @param  fractal  Pointer to the fractal structure containing
 *					rendering parameters.
 * @return TRUE if all threads were successfully created and joined,
 *		   FALSE otherwise.
 *
 * @note   Uses `sysconf(_SC_NPROCESSORS_ONLN)` to detect CPU cores and
 *		   scales the number of threads accordingly.
 * @warning Memory allocation failures or thread creation errors will
 *			cause an early exit.
 * @pre    `fractal` must be fully initialized with valid rendering parameters.
 * @post   All threads have finished rendering; allocated memory is freed.
 */
int	init_threads(t_fractal *fractal)
{
	pthread_t		*threads;
	t_thread_args	*args;
	long			n_threads;
	int				i;

	n_threads = sysconf(_SC_NPROCESSORS_ONLN) * 4;
	threads = ft_calloc(n_threads, sizeof(pthread_t));
	if (!threads)
		return (FALSE);
	args = ft_calloc(n_threads, sizeof(t_thread_args));
	if (!args)
		return (free(threads), FALSE);
	if (loop_init_threads(n_threads, threads, args, fractal) == FALSE)
		return (free(threads), free(args), FALSE);
	i = -1;
	while (++i < n_threads)
		pthread_join(threads[i], NULL);
	free(threads);
	free(args);
	return (TRUE);
}
