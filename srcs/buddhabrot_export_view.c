#include "fractol.h"
#include "stb_image_write.h"

static void	convert_bgra_to_rgba_line(const unsigned char *src,
					unsigned char *dst, int w)
{
	int	x;

	x = -1;
	while (++x < w)
	{
		dst[0] = src[2];
		dst[1] = src[1];
		dst[2] = src[0];
		dst[3] = 255;
		src += 4;
		dst += 4;
	}
}

static void	blit_bgra_to_rgba(t_image *img, unsigned char *dst, int dst_stride)
{
	int					y;
	const unsigned char	*src_line;
	unsigned char		*dst_line;

	y = -1;
	while (++y < img->height)
	{
		src_line = (const unsigned char *)img->px_ptr
			+ (size_t)y * (size_t)img->line_length;
		dst_line = dst + (size_t)y * (size_t)dst_stride;
		convert_bgra_to_rgba_line(src_line, dst_line, img->width);
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

static int	export_view_png(t_fractal *f, const char *filepath)
{
	int				ok;
	int				w;
	int				h;
	int				stride;
	unsigned char	*rgba;

	if (f->img.bits_per_pixel != 32)
		return (0);
	ok = 0;
	w = f->img.width;
	h = f->img.height;
	rgba = NULL;
	if (!snap_lock(&f->img))
		return (0);
	if (!alloc_rgba_buffer(w, h, &rgba, &stride))
	{
		snap_unlock(&f->img);
		return (0);
	}
	blit_bgra_to_rgba(&f->img, rgba, stride);
	snap_unlock(&f->img);
	if (stbi_write_png(filepath, w, h, 4, rgba, stride))
		ok = 1;
	free(rgba);
	return (ok);
}

int	export_view_auto(t_fractal *f)
{
	char	*path;
	int		ok;

	ok = 0;
	if (!ensure_exports_dir())
		return (0);
	path = generate_view_export_filename(f);
	if (!path)
		return (0);
	if (export_view_png(f, path))
		ok = 1;
	free(path);
	return (ok);
}
