#include "fractol.h"

/**
 * @brief  Perform a single Buddhabrot rendering tick in single-thread mode.
 *
 * Executes a fixed number of random samples (`bb_samples_per_tick`)
 * to update the Buddhabrot histogram. Tracks the total number of
 * processed samples and updates the maximum histogram count found
 * during this tick if a new maximum is reached.
 *
 * @param  f  Pointer to the fractal context (`t_fractal`) containing
 *            all rendering parameters and histogram data.
 * @return None.
 *
 * @note   This function is used when multi-threading is disabled.
 *         It relies on `bb_run_samples_single()` to perform the
 *         sample generation and histogram update.
 * @pre    `f` must be properly initialized with valid Buddhabrot
 *         rendering parameters and allocated histogram buffers.
 * @post   The histogram and statistics in `f` are updated to reflect
 *         the samples generated during this tick.
 */
static void	bb_render_tick_single(t_fractal *f)
{
	int	local_max;

	local_max = bb_run_samples_single(f, f->bb_samples_per_tick);
	f->bb_samples_total += (uint64_t)f->bb_samples_per_tick;
	if ((uint32_t)local_max > f->bb_max_count)
		f->bb_max_count = (uint32_t)local_max;
}

/**
 * @brief  Render one Buddhabrot frame.
 *
 * Depending on whether multi-threading is enabled, this function
 * performs a full rendering pass using either the multi-threaded
 * or single-threaded sampling routine. Once the histogram is updated,
 * the image is drawn from the histogram and displayed in the window.
 *
 * @param  f  Pointer to the fractal context (`t_fractal`) containing
 *            all rendering state, parameters, and buffers.
 * @return None.
 *
 * @note   This is the main rendering entry point for a single frame.
 *         The function always refreshes the displayed image at the end.
 * @pre    The `f` context must have a valid MLX window and image,
 *         and initialized Buddhabrot histogram data.
 * @post   The display window shows the updated Buddhabrot image.
 */
static void	buddhabrot_render_once(t_fractal *f)
{
	if (f->mt == TRUE)
		bb_render_tick_mt(f);
	else
		bb_render_tick_single(f);
	bb_draw_from_histogram(f);
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img.img_ptr, 0, 0);
}

/**
 * @brief  Buddhabrot rendering loop callback.
 *
 * Called repeatedly by the MLX event loop to update and display the
 * Buddhabrot fractal in real-time. This function delegates rendering
 * to `buddhabrot_render_once()` and maintains the animation or live
 * computation.
 *
 * @param  param  Generic pointer passed by the MLX loop, expected to
 *                be a pointer to a valid `t_fractal` context.
 * @return Always returns 0 (required by MLX loop hook signature).
 *
 * @note   This function is registered with `mlx_loop_hook()` or
 *         equivalent. It ensures continuous progressive rendering
 *         while the program is running.
 * @pre    `param` must be a valid pointer to an initialized
 *         `t_fractal` structure with all rendering resources ready.
 * @post   The Buddhabrot image is progressively updated on screen.
 */
int	buddhabrot_loop(void *param)
{
	t_fractal	*f;

	f = (t_fractal *)param;
	buddhabrot_render_once(f);
	return (0);
}
