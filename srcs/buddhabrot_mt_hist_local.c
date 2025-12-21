#include "fractol.h"

/**
 * @brief  Allocate and initialize a local histogram.
 *
 * Allocates memory for a histogram of `count` bins, each storing a
 * 32-bit unsigned integer. If allocation succeeds, all bins are
 * initialized to zero.
 *
 * @param  hist   Address of a pointer to the histogram array. The
 *                allocated memory address will be stored here.
 * @param  count  Number of bins to allocate in the histogram.
 * @return 1 on success, 0 on allocation failure.
 *
 * @note   The caller is responsible for freeing the allocated memory
 *         using `bb_free_local_hist()`.
 * @pre    `hist` must be a valid pointer to a `uint32_t*`.
 * @post   On success, `*hist` points to a zero-initialized array of
 *         size `count`. On failure, `*hist` remains unchanged.
 */
int	bb_alloc_local_hist(uint32_t **hist, int count)
{
	*hist = (uint32_t *)ft_calloc(count, sizeof(uint32_t));
	if (!*hist)
		return (0);
	return (1);
}

/**
 * @brief  Free a previously allocated local histogram.
 *
 * Frees the memory associated with a histogram and sets its pointer
 * to NULL to prevent dangling references.
 *
 * @param  hist  Address of a pointer to the histogram array to free.
 * @return None.
 *
 * @note   Safe to call with `*hist == NULL`. Does nothing in that case.
 * @pre    `hist` must be a valid pointer to a `uint32_t*` previously
 *         allocated with `bb_alloc_local_hist()` or equivalent.
 * @post   `*hist` is set to NULL after memory is freed.
 */
void	bb_free_local_hist(uint32_t **hist)
{
	if (*hist)
		free(*hist);
	*hist = NULL;
}
