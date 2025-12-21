#include "fractol.h"

static void	bb_mt_abort_launch(t_bb_mt_ctx *ctx, int created)
{
	int	i;

	i = 0;
	while (i < created)
	{
		pthread_join(ctx->th[i], NULL);
		i++;
	}
	i = 0;
	while (i < created)
	{
		bb_free_local_hist(&ctx->args[i].local_hist);
		i++;
	}
	free(ctx->th);
	free(ctx->args);
	ctx->th = NULL;
	ctx->args = NULL;
}

static int	bb_mt_launch_threads(t_bb_mt_ctx *ctx, t_fractal *f)
{
	int	i;
	int	remainder;

	i = 0;
	remainder = f->bb_samples_per_tick - (ctx->spt * ctx->n);
	while (i < ctx->n)
	{
		bb_mt_fill_arg_common(f, ctx, i);
		if (i == ctx->n - 1 && remainder > 0)
			ctx->args[i].samples += remainder;
		if (!bb_alloc_local_hist(&ctx->args[i].local_hist, ctx->count))
			return (bb_mt_abort_launch(ctx, i), 0);
		if (pthread_create(&ctx->th[i], NULL, bb_thread_routine,
				&ctx->args[i]) != 0)
		{
			bb_free_local_hist(&ctx->args[i].local_hist);
			return (bb_mt_abort_launch(ctx, i), 0);
		}
		i++;
	}
	return (1);
}

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

static uint32_t	bb_mt_merge_all_and_free(t_fractal *f, t_bb_mt_ctx *ctx)
{
	int			i;
	uint32_t	max_after_merge;

	max_after_merge = f->bb_max_count;
	i = 0;
	while (i < ctx->n)
	{
		bb_hist_merge(f->bb_hist, ctx->args[i].local_hist,
			ctx->count, &max_after_merge);
		bb_free_local_hist(&ctx->args[i].local_hist);
		i++;
	}
	return (max_after_merge);
}

void	bb_render_tick_mt(t_fractal *f)
{
	t_bb_mt_ctx	ctx;
	uint32_t	max_after_merge;

	if (!bb_mt_prepare_ctx(f, &ctx))
		return ;
	if (!bb_mt_launch_threads(&ctx, f))
		return ;
	bb_mt_join_threads(&ctx);
	max_after_merge = bb_mt_merge_all_and_free(f, &ctx);
	bb_mt_finalize(f, &ctx, max_after_merge);
}
