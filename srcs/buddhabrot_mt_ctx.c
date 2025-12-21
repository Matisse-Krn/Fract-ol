#include "fractol.h"

static int	bb_choose_threads(void)
{
	long	n;

	n = sysconf(_SC_NPROCESSORS_ONLN);
	if (n < 1)
		n = 1;
	if (n > 12)
		n = 12;
	return ((int)n);
}

static int	bb_cap_threads_by_memory(int n, int count)
{
	size_t	bytes_per_hist;
	size_t	budget;
	int		max_threads;

	bytes_per_hist = (size_t)count * sizeof(uint32_t);
	budget = 256u * 1024u * 1024u;
	if (bytes_per_hist == 0)
		return (1);
	max_threads = (int)(budget / bytes_per_hist);
	if (max_threads < 1)
		max_threads = 1;
	if (n > max_threads)
		n = max_threads;
	if (n < 1)
		n = 1;
	return (n);
}

int	bb_mt_prepare_ctx(const t_fractal *f, t_bb_mt_ctx *ctx)
{
	ctx->n = bb_choose_threads();
	ctx->count = f->img.width * f->img.height;

	ctx->n = bb_cap_threads_by_memory(ctx->n, ctx->count);

	if (ctx->n > f->bb_samples_per_tick)
		ctx->n = f->bb_samples_per_tick;
	if (ctx->n < 1)
		ctx->n = 1;

	ctx->spt = f->bb_samples_per_tick / ctx->n;
	if (ctx->spt < 1)
		ctx->spt = 1;

	ctx->th = (pthread_t *)ft_calloc(ctx->n, sizeof(pthread_t));
	if (!ctx->th)
		return (0);
	ctx->args = (t_bb_args *)ft_calloc(ctx->n, sizeof(t_bb_args));
	if (!ctx->args)
	{
		free(ctx->th);
		ctx->th = NULL;
		return (0);
	}
	return (1);
}

void	bb_mt_fill_arg_common(t_fractal *f, t_bb_mt_ctx *ctx, int i)
{
	ctx->args[i].f = f;
	ctx->args[i].seed = f->bb_seed + (unsigned int)(7919 * (i + 1));
	ctx->args[i].samples = ctx->spt;
	ctx->args[i].tid = i;
	ctx->args[i].nthreads = ctx->n;
	ctx->args[i].all = ctx->args;
	ctx->args[i].barrier = NULL;
}

void	bb_mt_cleanup_partial(t_bb_mt_ctx *ctx, int upto)
{
	int	j;

	j = 0;
	while (j < upto)
	{
		bb_free_local_hist(&ctx->args[j].local_hist);
		j++;
	}
	free(ctx->th);
	free(ctx->args);
	ctx->th = NULL;
	ctx->args = NULL;
}

void	bb_mt_finalize(t_fractal *f, t_bb_mt_ctx *ctx, uint32_t max_after_merge)
{
	f->bb_max_count = max_after_merge;
	f->bb_seed += (unsigned int)(13331 * (ctx->n + 1));
	f->bb_samples_total += (uint64_t)f->bb_samples_per_tick;
	free(ctx->th);
	free(ctx->args);
	ctx->th = NULL;
	ctx->args = NULL;
}

