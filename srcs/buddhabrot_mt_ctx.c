#include "fractol.h"

/**
 * @brief  Determine the optimal number of threads to use.
 *
 * Retrieves the number of available CPU cores using `sysconf()`
 * and clamps it between 1 and 12. This ensures reasonable thread
 * usage without oversubscribing the system.
 *
 * @param  None.
 * @return The number of threads to use, as an integer.
 *
 * @note   The upper limit of 12 threads is arbitrary and may be
 *         adjusted based on performance testing.
 * @pre    None.
 * @post   Returned value is between 1 and 12.
 */
static int	bb_choose_threads(void)
{
	long	n;

	n = sysconf(_SC_NPROCESSORS_ONLN);
	if (n < 1)
		n = 1;
	if (n > 12)
		n = 12;
	return ((int)n);
	// return (1);
}

/**
 * @brief  Prepare the Buddhabrot multi-threading context.
 *
 * Initializes the `t_bb_mt_ctx` structure by setting the number of
 * threads, total pixel count, and samples per thread. Allocates
 * memory for thread handles and argument structures, and initializes
 * a synchronization barrier.
 *
 * @param  f    Pointer to the fractal context (`t_fractal`) containing
 *              image dimensions and rendering parameters.
 * @param  ctx  Pointer to the multi-threading context to initialize.
 * @return 1 on success, 0 on allocation or initialization failure.
 *
 * @note   On failure, all allocated memory is freed to avoid leaks.
 * @pre    `f` and `ctx` must be valid pointers.
 * @post   `ctx` is ready for thread creation, with allocated arrays
 *         and initialized barrier.
 */
int	bb_mt_prepare_ctx(const t_fractal *f, t_bb_mt_ctx *ctx)
{
	ctx->n = bb_choose_threads();
	ctx->count = f->img.width * f->img.height;
	ctx->spt = f->bb_samples_per_tick / ctx->n;
	ctx->th = (pthread_t *)ft_calloc(ctx->n, sizeof(pthread_t));
	if (!ctx->th)
		return (0);
	ctx->args = (t_bb_args *)ft_calloc(ctx->n, sizeof(t_bb_args));
	if (!ctx->args)
	{
		free(ctx->th);
		return (0);
	}
	if (pthread_barrier_init(&ctx->barrier, NULL, ctx->n) != 0)
	{
		free(ctx->th);
		free(ctx->args);
		return (0);
	}
	return (1);
}

/**
 * @brief  Fill common arguments for a Buddhabrot worker thread.
 *
 * Populates a `t_bb_args` structure for a given thread index with
 * pointers to the fractal context, random seed, sample count, thread
 * ID, total thread count, and synchronization barrier.
 *
 * @param  f     Pointer to the fractal context (`t_fractal`).
 * @param  ctx   Pointer to the multi-threading context.
 * @param  i     Index of the thread being configured.
 * @return None.
 *
 * @note   The random seed is offset by a prime multiplier (7919)
 *         to reduce correlation between threads.
 * @pre    `ctx->args` must be allocated and `i` must be within range.
 * @post   Thread arguments for index `i` are fully initialized.
 */
void	bb_mt_fill_arg_common(t_fractal *f, t_bb_mt_ctx *ctx, int i)
{
	ctx->args[i].f = f;
	ctx->args[i].seed = f->bb_seed + (unsigned int)(7919 * (i + 1));
	ctx->args[i].samples = ctx->spt;
	ctx->args[i].tid = i;
	ctx->args[i].nthreads = ctx->n;
	ctx->args[i].all = ctx->args;
	ctx->args[i].barrier = &ctx->barrier;
}

/**
 * @brief  Partially clean up a Buddhabrot multi-threading context.
 *
 * Frees local histograms and deallocates resources for threads up to
 * a given index. Destroys the synchronization barrier and releases
 * thread and argument arrays.
 *
 * @param  ctx   Pointer to the multi-threading context.
 * @param  upto  Number of threads to clean up (from index 0 to `upto - 1`).
 * @return None.
 *
 * @note   Used when initialization fails partway, to clean only the
 *         successfully initialized resources.
 * @pre    `ctx` must be valid and partially initialized.
 * @post   Freed resources for all threads below `upto`, and common
 *         resources released.
 */
void	bb_mt_cleanup_partial(t_bb_mt_ctx *ctx, int upto)
{
	int	j;

	j = 0;
	while (j < upto)
	{
		bb_free_local_hist(&ctx->args[j].local_hist);
		j++;
	}
	pthread_barrier_destroy(&ctx->barrier);
	free(ctx->th);
	free(ctx->args);
}

/**
 * @brief  Finalize a Buddhabrot multi-threading session.
 *
 * Updates the fractal context's maximum histogram count, random seed,
 * and total sample count based on the work completed by all threads.
 * Destroys the synchronization barrier and frees all thread-related
 * resources.
 *
 * @param  f                Pointer to the fractal context (`t_fractal`).
 * @param  ctx              Pointer to the multi-threading context.
 * @param  max_after_merge  The maximum histogram bin value after merging
 *                          all thread-local histograms.
 * @return None.
 *
 * @note   This function is typically called after all worker threads
 *         have completed and their results have been merged.
 * @pre    `ctx` must have been successfully initialized and used for
 *         a rendering pass.
 * @post   Multi-threading resources are fully released.
 */
void	bb_mt_finalize(t_fractal *f, t_bb_mt_ctx *ctx,
						uint32_t max_after_merge)
{
	f->bb_max_count = max_after_merge;
	f->bb_seed += (unsigned int)(13331 * (ctx->n + 1));
	f->bb_samples_total += (uint64_t)(ctx->spt * ctx->n);
	pthread_barrier_destroy(&ctx->barrier);
	free(ctx->th);
	free(ctx->args);
}
