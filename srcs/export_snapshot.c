#include "fractol.h"

void	img_snapshot_take(t_img_snapshot *s, t_image *img)
{
	s->img_ptr = img->img_ptr;
	s->px_ptr = img->px_ptr;
	s->width = img->width;
	s->height = img->height;
	s->bits_per_pixel = img->bits_per_pixel;
	s->line_length = img->line_length;
	s->endian = img->endian;
	s->full_width = img->full_width;
	s->full_height = img->full_height;
}

void	img_snapshot_apply(t_image *img, const t_img_snapshot *s)
{
	img->img_ptr = s->img_ptr;
	img->px_ptr = s->px_ptr;
	img->width = s->width;
	img->height = s->height;
	img->bits_per_pixel = s->bits_per_pixel;
	img->line_length = s->line_length;
	img->endian = s->endian;
	img->full_width = s->full_width;
	img->full_height = s->full_height;
}

