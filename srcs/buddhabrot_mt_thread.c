#include "fractol.h"

void	*bb_thread_routine(void *arg)
{
	t_bb_args	*a;
	uint32_t	max_local;
	t_bb_accum	acc;

	a = (t_bb_args *)arg;
	max_local = 0;
	acc.hist = a->local_hist;
	acc.max = &max_local;
	bb_run_samples_local(a->f, a->samples, &a->seed, &acc);
	a->local_max = (int)max_local;
	return (NULL);
}

