#include "fractol.h"

/**
 * @brief  Allocate memory for Buddhabrot histograms.
 *
 * Creates the main histogram buffer (`bb_hist`) used to store sample
 * counts for each pixel. If the "nebula" mode is enabled ('Y'), also
 * allocates three separate histograms for the red, green, and blue
 * channels (`bb_hist_r`, `bb_hist_g`, `bb_hist_b`).
 *
 * @param  f  Pointer to the fractal context (`t_fractal`) containing
 *            image dimensions and rendering parameters.
 * @return 1 on successful allocation, 0 on failure.
 *
 * @note   On allocation failure, calls `malloc_error()` and frees any
 *         partially allocated memory to avoid leaks.
 * @pre    `f->img.width` and `f->img.height` must be initialized.
 * @post   The allocated histograms are ready for use in rendering.
 */
int	bb_alloc_histograms(t_fractal *f)
{
	int	count;

	count = f->img.width * f->img.height;
	f->bb_hist = ft_calloc(sizeof(uint32_t), count);
	if (!f->bb_hist)
	{
		malloc_error();
		return (0);
	}
	if (f->bb_nebula == 'Y')
	{
		f->bb_hist_r = ft_calloc(sizeof(uint32_t), count);
		if (!f->bb_hist_r)
			return (malloc_error(), free(f->bb_hist), 0);
		f->bb_hist_g = ft_calloc(sizeof(uint32_t), count);
		if (!f->bb_hist_g)
			return (malloc_error(), free(f->bb_hist), free(f->bb_hist_r), 0);
		f->bb_hist_b = ft_calloc(sizeof(uint32_t), count);
		if (!f->bb_hist_b)
			return (malloc_error(), free(f->bb_hist),
				free(f->bb_hist_r), free(f->bb_hist_g), 0);
	}
	return (1);
}

/**
 * @brief  Reset all Buddhabrot histograms to zero.
 *
 * Clears the main histogram (`bb_hist`) and, if nebula mode is enabled,
 * also clears the red, green, and blue histograms. Resets the total
 * sample count and the maximum bin value to initial states.
 *
 * @param  f  Pointer to the fractal context (`t_fractal`) containing
 *            allocated histograms and rendering parameters.
 * @return None.
 *
 * @note   This function is typically called before starting a new
 *         rendering sequence.
 * @pre    Histograms must already be allocated.
 * @post   All histogram values are set to zero, `bb_samples_total` is
 *         reset to 0, and `bb_max_count` is set to 1.
 */
void	bb_reset_histograms(t_fractal *f)
{
	int	count;

	count = f->img.width * f->img.height;
	ft_bzero(f->bb_hist, sizeof(uint32_t) * count);
	if (f->bb_nebula == 'Y')
	{
		ft_bzero(f->bb_hist_r, sizeof(uint32_t) * count);
		ft_bzero(f->bb_hist_g, sizeof(uint32_t) * count);
		ft_bzero(f->bb_hist_b, sizeof(uint32_t) * count);
	}
	f->bb_samples_total = 0;
	f->bb_max_count = 1;
}

/**
 * @brief  Free all allocated Buddhabrot histograms.
 *
 * Releases memory used by the main histogram and, if nebula mode is
 * enabled, also frees the red, green, and blue histograms.
 *
 * @param  f  Pointer to the fractal context (`t_fractal`) containing
 *            allocated histograms.
 * @return None.
 *
 * @note   Does not set the histogram pointers to NULL after freeing.
 * @pre    Histograms must have been allocated before calling this function.
 * @post   Histogram memory is released, but the pointers may be left dangling.
 */
void	bb_free_histograms(t_fractal *f)
{
	if (f->bb_hist)
		free(f->bb_hist);
	if (f->bb_nebula == 'Y')
	{
		free(f->bb_hist_r);
		free(f->bb_hist_g);
		free(f->bb_hist_b);
	}
}
