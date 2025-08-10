#include "fractol.h"

/**
 * @brief  Launch all Buddhabrot worker threads.
 *
 * Initializes thread arguments, allocates each thread's local histogram,
 * and starts the worker threads. If any allocation or thread creation
 * fails, already-initialized resources are cleaned up.
 *
 * @param  ctx  Pointer to the multi-threading context (`t_bb_mt_ctx`)
 *              containing thread and argument arrays.
 * @param  f    Pointer to the fractal context (`t_fractal`).
 * @return 1 on success, 0 on failure.
 *
 * @note   Uses `bb_mt_fill_arg_common()` to initialize arguments,
 *         `bb_alloc_local_hist()` for per-thread histograms, and
 *         `pthread_create()` to start threads.
 * @pre    `ctx` must be initialized with allocated arrays and a barrier.
 * @post   If successful, all threads are running; otherwise, all
 *         partially created threads and allocated resources are freed.
 */
static int	bb_mt_launch_threads(t_bb_mt_ctx *ctx, t_fractal *f)
{
	int	i;

	i = 0;
	while (i < ctx->n)
	{
		bb_mt_fill_arg_common(f, ctx, i);
		if (!bb_alloc_local_hist(&ctx->args[i].local_hist, ctx->count))
		{
			bb_mt_cleanup_partial(ctx, i);
			return (0);
		}
		if (pthread_create(&ctx->th[i], NULL,
				bb_thread_routine, &ctx->args[i]) != 0)
		{
			bb_mt_cleanup_partial(ctx, i + 1);
			return (0);
		}
		i++;
	}
	return (1);
}

/**
 * @brief  Wait for all Buddhabrot worker threads to complete.
 *
 * Joins each thread in the multi-threading context, blocking until
 * all threads have finished their work.
 *
 * @param  ctx  Pointer to the multi-threading context (`t_bb_mt_ctx`).
 * @return None.
 *
 * @note   Uses `pthread_join()` to wait for each thread's completion.
 * @pre    All threads in `ctx` must have been successfully created.
 * @post   All worker threads have terminated before returning.
 */
static void	bb_mt_join_threads(t_bb_mt_ctx *ctx)
{
	int	i;

	i = 0;
	while (i < ctx->n)
	{
		pthread_join(ctx->th[i], NULL);
		i++;
	}
}

/**
 * @brief  Collect the maximum histogram bin value and free local histograms.
 *
 * Iterates through all threads, updating the maximum histogram bin value
 * found in their local results, and frees each thread's local histogram
 * memory.
 *
 * @param  f    Pointer to the fractal context (`t_fractal`) containing
 *              the current maximum histogram bin value.
 * @param  ctx  Pointer to the multi-threading context (`t_bb_mt_ctx`).
 * @return The maximum histogram bin value after merging results.
 *
 * @note   This function does not merge histograms; it only tracks the
 *         maximum value and releases local memory.
 * @pre    All threads must have completed their execution.
 * @post   All per-thread histograms are freed and `max_after_merge`
 *         is ready for finalization.
 */
static uint32_t	bb_mt_collect_max_and_free(t_fractal *f, t_bb_mt_ctx *ctx)
{
	int			i;
	uint32_t	max_after_merge;

	max_after_merge = f->bb_max_count;
	i = 0;
	while (i < ctx->n)
	{
		if ((uint32_t)ctx->args[i].local_max > max_after_merge)
			max_after_merge = (uint32_t)ctx->args[i].local_max;
		bb_free_local_hist(&ctx->args[i].local_hist);
		i++;
	}
	return (max_after_merge);
}

/**
 * @brief  Perform a single Buddhabrot rendering tick using multi-threading.
 *
 * Sets up the multi-threading context, launches all worker threads,
 * waits for their completion, collects the maximum histogram bin value,
 * and finalizes the rendering tick.
 *
 * @param  f  Pointer to the fractal context (`t_fractal`) containing
 *            all Buddhabrot rendering parameters.
 * @return None.
 *
 * @note   If any step fails (context preparation or thread launch),
 *         the function exits early without performing further work.
 * @pre    `f` must be initialized with valid rendering parameters.
 * @post   The global histogram and statistics in `f` are updated to
 *         reflect the samples generated during this tick.
 */
void	bb_render_tick_mt(t_fractal *f)
{
	t_bb_mt_ctx	ctx;
	uint32_t	max_after_merge;

	if (!bb_mt_prepare_ctx(f, &ctx))
		return ;
	if (!bb_mt_launch_threads(&ctx, f))
		return ;
	bb_mt_join_threads(&ctx);
	max_after_merge = bb_mt_collect_max_and_free(f, &ctx);
	bb_mt_finalize(f, &ctx, max_after_merge);
}
