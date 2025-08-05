#include "fractol.h"


#include "fractol.h"
#include <sys/stat.h> // mkdir
#include <unistd.h>   // access
#include <fcntl.h>    // access macros
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h" // à inclure une fois dans le fichier

static char	*build_filename(t_fractal *f, int suffix)
{
	char	*filename;
	char	buffer[512];
	char	name_part[64];

	snprintf(name_part, sizeof(name_part),
		"fractol_%s_x=%.5f_y=%.5f_z=%.5f_iter=%d",
		f->name, f->shift_x, f->shift_y, f->zoom_rate, f->max_iterations);
	if (suffix == 0)
		snprintf(buffer, sizeof(buffer), "exports/%s.png", name_part);
	else
		snprintf(buffer, sizeof(buffer), "exports/%s_%d.png", name_part, suffix);
	filename = ft_strdup(buffer);
	return (filename);
}

static char	*generate_export_filename(t_fractal *f)
{
	int		suffix;
	char	*filename;

	suffix = 0;
	filename = build_filename(f, suffix);
	while (access(filename, F_OK) == 0)
	{
		free(filename);
		suffix++;
		filename = build_filename(f, suffix);
	}
	return (filename);
}

static void	write_image_to_png(const char *filename, t_image *img)
{
	unsigned char	*rgb;
	int				x;
	int				y;
	int				i;

	rgb = malloc(img->width * img->height * 3);
	if (!rgb)
		malloc_error();
	i = 0;
	y = -1;
	while (++y < img->height)
	{
		x = -1;
		while (++x < img->width)
		{
			char *px = img->px_ptr + y * img->line_length + x * 4;
			rgb[i++] = (unsigned char)px[2]; // R
			rgb[i++] = (unsigned char)px[1]; // G
			rgb[i++] = (unsigned char)px[0]; // B
		}
	}
	if (!stbi_write_png(filename, img->width, img->height, 3, rgb, img->width * 3))
		ft_putstr_fd("❌ Failed to write PNG file\n", 2);
	free(rgb);
}

static void	render_only_to_image(t_fractal *fractal)
{
	if (fractal->palette_mode == 'A')
		fractal->i_max = 0;
	if (fractal->mt == FALSE)
	{
		if (!ft_strcmp(fractal->name, "mandelbrot"))
			pixel_loop('M', fractal);
		else if (!ft_strcmp(fractal->name, "julia"))
			pixel_loop('J', fractal);
	}
	else
	{
		if (init_threads(fractal) == FALSE)
			return ;
	}
	/*manage_text(fractal);*/
}

void	export_image(t_fractal *fractal)
{
	t_fractal	backup;
	t_image		export;
	char		*filename;
	int			orig_iter;
	t_image		orig_img;
	// Créer dossier ./exports/ s'il n'existe pas
	mkdir("exports", 0777);

	// Sauvegarde des données de fractal
	orig_img = fractal->img;
	orig_iter = fractal->max_iterations;
	backup = duplicate_fractal(fractal);

	// Initialisation de l'image d'export
	export.width = fractal->img.full_width;
	export.height = fractal->img.full_height;
	export.img_ptr = mlx_new_image(fractal->mlx_ptr, export.width, export.height);
	if (!export.img_ptr)
		malloc_error();
	export.px_ptr = mlx_get_data_addr(export.img_ptr,
		&export.bits_per_pixel,
		&export.line_length,
		&export.endian);
	if (!export.px_ptr)
		malloc_error();
	fractal->img = export;

	// Augmentation des iterations
	fractal->max_iterations = 10000;
	// Modification aspect_ratio;
	fractal->aspect_ratio = (double)fractal->img.width / (double)fractal->img.height;


	// Rendu haute qualité
	render_only_to_image(fractal);

	// Création du nom de fichier
	filename = generate_export_filename(fractal);
	if (!filename)
		malloc_error();
	// Conversion en RGB + écriture du PNG
	write_image_to_png(filename, &export);
	free(filename);

	restore_fractal(fractal, &backup, &orig_img);
	mlx_destroy_image(fractal->mlx_ptr, export.img_ptr);
	/**fractal = backup;*/
	/*fractal->img = orig_img;*/
	/*fractal->aspect_ratio = (double)fractal->img.width / (double)fractal->img.height;*/

	ft_putstr_fd("✅ Export completed successfully !\n", 1);
}


