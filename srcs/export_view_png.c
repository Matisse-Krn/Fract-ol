#include "fractol.h"
#include "stb_image_write.h"

static void	convert_bgra_to_rgba_line(const unsigned char *src,
					unsigned char *dst, int w)
{
	int	x;

	x = 0;
	while (x < w)
	{
		dst[0] = src[2];
		dst[1] = src[1];
		dst[2] = src[0];
		dst[3] = 255;
		src += 4;
		dst += 4;
		x++;
	}
}

static void	blit_bgra_to_rgba(t_image *img, unsigned char *dst, int dst_stride)
{
	int					y;
	const unsigned char	*src_line;
	unsigned char		*dst_line;

	y = 0;
	while (y < img->height)
	{
		src_line = (const unsigned char *)img->px_ptr
			+ (size_t)y * (size_t)img->line_length;
		dst_line = dst + (size_t)y * (size_t)dst_stride;
		convert_bgra_to_rgba_line(src_line, dst_line, img->width);
		y++;
	}
}

static int	alloc_rgba_buffer(int w, int h, unsigned char **out, int *stride)
{
	size_t	size;

	if (w <= 0 || h <= 0 || !out || !stride)
		return (0);
	size = (size_t)w * (size_t)h * 4u;
	*out = (unsigned char *)malloc(size);
	if (!*out)
		return (0);
	*stride = w * 4;
	return (1);
}

int	export_view_png(t_fractal *f, const char *filepath)
{
	int				ok;
	int				stride;
	unsigned char	*rgba;

	ok = 0;
	stride = 0;
	rgba = NULL;
	if (f->img.bits_per_pixel != 32)
		return (0);
	if (!snap_lock(&f->img))
		return (0);
	if (!alloc_rgba_buffer(f->img.width, f->img.height, &rgba, &stride))
	{
		snap_unlock(&f->img);
		return (0);
	}
	blit_bgra_to_rgba(&f->img, rgba, stride);
	snap_unlock(&f->img);
	if (stbi_write_png(filepath, f->img.width, f->img.height, 4, rgba, stride))
		ok = 1;
	free(rgba);
	return (ok);
}
