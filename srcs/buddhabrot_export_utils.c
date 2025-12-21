
#include "fractol.h"
#include <errno.h>

int	ensure_exports_dir(void)
{
	struct stat	st;

	if (stat("exports", &st) == 0)
		return (S_ISDIR(st.st_mode));
	if (errno != ENOENT)
		return (0);
	if (mkdir("exports", 0755) == 0)
		return (1);
	if (errno == EEXIST)
		return (1);
	return (0);
}

static char	*build_view_filename(t_fractal *f, int suffix)
{
	char	buffer[512];
	char	name_part[320];

	if (f->range_color_mode == 'Y')
	{
		snprintf(name_part, sizeof(name_part), "fractol_%s_x=%.5f_y=%.5f"
			"_z=%.5f_iter=%d_mode=%s_psy=on_color=%c_view_%dx%d",
			f->name, f->shift_x, f->shift_y, f->zoom_rate, f->max_iterations,
			get_render_mode_label(f->render_mode), f->color_mode,
			f->img.width, f->img.height);
	}
	else
	{
		snprintf(name_part, sizeof(name_part), "fractol_%s_x=%.5f_y=%.5f"
			"_z=%.5f_iter=%d_mode=%s_psy=off_color=%c_view_%dx%d",
			f->name, f->shift_x, f->shift_y, f->zoom_rate, f->max_iterations,
			get_render_mode_label(f->render_mode), f->color_mode,
			f->img.width, f->img.height);
	}
	if (suffix == 0)
		snprintf(buffer, sizeof(buffer), "exports/%s.png", name_part);
	else
		snprintf(buffer, sizeof(buffer), "exports/%s_%d.png", name_part, suffix);
	return (ft_strdup(buffer));
}

char	*generate_view_export_filename(t_fractal *f)
{
	int		suffix;
	char	*filename;

	if (!ensure_exports_dir())
		return (NULL);
	suffix = 0;
	filename = build_view_filename(f, suffix);
	while (filename && access(filename, F_OK) == 0)
	{
		free(filename);
		suffix++;
		filename = build_view_filename(f, suffix);
	}
	return (filename);
}
