#include "fractol.h"

void	img_lock_init(t_image *img)
{
	if (!img)
		return ;
	pthread_mutex_init(&img->lock, NULL);
}

void	img_lock_destroy(t_image *img)
{
	if (!img)
		return ;
	pthread_mutex_destroy(&img->lock);
}

int	snap_lock(t_image *img)
{
	int	ret;

	if (!img)
		return (0);
	ret = pthread_mutex_lock(&img->lock);
	if (ret != 0)
		return (0);
	return (1);
}

void	snap_unlock(t_image *img)
{
	if (!img)
		return ;
	pthread_mutex_unlock(&img->lock);
}
