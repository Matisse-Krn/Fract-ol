#include "fractol.h"

/**
 * @brief  Merge histogram data for a specific band across all threads.
 *
 * For each pixel index assigned to this thread (based on `tid`), sums
 * the corresponding histogram bins from all threads' local histograms
 * and adds the total to the global histogram. Tracks the highest merged
 * bin value encountered during the process.
 *
 * @param  a  Pointer to the thread's argument structure (`t_bb_args`)
 *            containing references to all threads' histograms and
 *            rendering context.
 * @return The maximum merged bin value found in this band's range.
 *
 * @note   This function distributes the merge work by having each thread
 *         process a separate "band" of pixels, determined by the thread ID.
 * @pre    All local histograms in `a->all` must be valid and filled.
 * @post   The global histogram (`f->bb_hist`) contains accumulated results
 *         from all threads for the processed band.
 */
static uint32_t	bb_merge_band(t_bb_args *a)
{
	int			idx;
	int			t;
	int			count;
	uint32_t	s;
	uint32_t	max_merge;

	count = a->f->img.width * a->f->img.height;
	idx = a->tid;
	max_merge = 0;
	while (idx < count)
	{
		s = 0;
		t = 0;
		while (t < a->nthreads)
		{
			s += a->all[t].local_hist[idx];
			t++;
		}
		a->f->bb_hist[idx] += s;
		if (a->f->bb_hist[idx] > max_merge)
			max_merge = a->f->bb_hist[idx];
		idx += a->nthreads;
	}
	return (max_merge);
}

/**
 * @brief  Buddhabrot worker thread routine.
 *
 * Executes the sampling phase for the assigned thread, storing results
 * in its local histogram, then synchronizes with other threads to merge
 * histogram data into the global histogram. Updates the local maximum
 * bin value after merging.
 *
 * @param  arg  Pointer to the thread's argument structure (`t_bb_args`).
 * @return Always returns NULL (required by pthread interface).
 *
 * @note   This routine uses two barrier synchronizations:
 *         - First barrier: wait until all threads have completed sampling.
 *         - Second barrier: wait until all threads have merged their bands.
 * @pre    `arg` must be a valid pointer to an initialized `t_bb_args`
 *         structure with allocated local histogram.
 * @post   Global histogram is updated and `local_max` reflects the
 *         highest bin value seen by this thread after merging.
 */
void	*bb_thread_routine(void *arg)
{
	t_bb_args	*a;
	uint32_t	max_local;
	t_bb_accum	acc;
	uint32_t	max_merge;

	a = (t_bb_args *)arg;
	max_local = 0;
	acc.hist = a->local_hist;
	acc.max = &max_local;
	bb_run_samples_local(a->f, a->samples, &a->seed, &acc);
	a->local_max = (int)max_local;
	pthread_barrier_wait(a->barrier);
	max_merge = bb_merge_band(a);
	if ((int)max_merge > a->local_max)
		a->local_max = (int)max_merge;
	pthread_barrier_wait(a->barrier);
	return (NULL);
}
