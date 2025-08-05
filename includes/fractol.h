#ifndef FRACTOL_H
# define FRACTOL_H

# define TRUE 1
# define FALSE 0

# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include <math.h>
# include <float.h>

# include <pthread.h>



typedef struct s_complex_nb
{
	double	real;
	double	imag;
}			t_complex;

typedef struct s_image
{
	void	*img_ptr;
	char	*px_ptr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		full_width;
	int		full_height;
	int		height;
	int		width;
}			t_image;

typedef struct s_fractal
{
	char		*name;
	char		*init_c_real;
	char		*init_c_imag;
	char		*last_pos;
	char		color_mode;
	char		psy;
	char		palette_mode;
	void		*mlx_ptr;
	void		*win_ptr;
	int			max_iterations;
	int			i_max;
	int			tick_iterations;
	int			color;
	int			depth;
	int			max_depth;
	int			size;
	int			fullscreen;
	int			mt;
	double		aspect_ratio;
	double		escape_value;
	double		shift_x;
	double		shift_y;
	double		zoom_rate;
	double		init_shift_x;
	double		init_shift_y;
	double		init_zoom_rate;
	double		color_min;
	double		color_max;
	double		init_color_min;
	double		init_color_max;
	double		contrast_exponent;
	t_image		img;
	t_complex	c;
}				t_fractal;

typedef struct s_pixel
{
	int			x;
	int			y;
	int			i;
}				t_pixel;

typedef struct s_rgb
{
	int			r_min;
	int			g_min;
	int			b_min;
	int			r_max;
	int			g_max;
	int			b_max;
}				t_rgb;

typedef struct s_box
{
	int			from_x;
	int			from_y;
	int			to_x;
	int			to_y;
}				t_box;

typedef struct s_thread_arg
{
	t_fractal	*fractal;
	char		type;
	int			y_start;
	int			y_end;
} t_thread_args;

/* Memory and error handling */
void		malloc_error(void);
char		*if_malloc_error(char *s);
void		check_valid_input_numbers(char **argv);

/* Program initialization */
void		data_init(t_fractal *fractal);
void		data_init_sierpinski(t_fractal *fractal);
void		invalid_depth(char **argv, t_fractal *fractal);
void		initialize_window(t_fractal *f);
void		initialize_image(t_fractal *fractal);
void		initialize_text_image(t_fractal *fractal);

/*	Initialization utils */
void		init_mlx(t_fractal *fractal);
void		print_launch_messages(char type);
void		is_fullscreen(char **argv, t_fractal *fractal);
void		set_multi_threading(char **argv, t_fractal *fractal);

/*	Multi-threading init and routine */
int			get_multi_thread(void);
int			init_threads(t_fractal *fractal);

/* Event handling */
void		initialize_events(t_fractal *fractal);
void		initialize_events_sierpinski(t_fractal *fractal);
void		handle_key_two(int keysym, t_fractal *fractal);
void		handle_key_three(int keysym, t_fractal *fractal);
int			handle_key(int keysym, t_fractal *fractal);
int			handle_key_sierpinski(int keysym, t_fractal *fractal);
int			handle_exit(t_fractal *fractal);
int			handle_mouse(int button, int x, int y, t_fractal *fractal);
int			handle_mouse_move(int x, int y, t_fractal *fractal);

/* Fractal rendering management */
void		fractal_rendering(t_fractal *fractal);
void		handle_pixel_mandelbrot(t_pixel *pixel, t_fractal *fractal);
void		handle_pixel_julia(t_pixel *pixel, t_fractal *fractal);
void		pixel_loop(char type, t_fractal *fractal);
void		rendering_sierpinski(t_fractal *fractal);
void		draw_sierpinski_carpet(int x, int y, t_fractal *fractal);
void		my_mlx_pixel_put(t_image *data, int x, int y, int color);

/* Navigation and zooming */
void		apply_zoom(t_fractal *fractal, int x, int y, double factor);
void		displacement(char direction, t_fractal *fractal);
void		reset_view(t_fractal *fractal);

/*	"Jump to" functions */
void		jump_menu(void);
void		handle_jump_choice(t_fractal *f, int choice);

/* Color management */
int			distrib_colors(t_complex *z, t_pixel *pixel, t_fractal *f);
void		change_color_mode(char mode, t_fractal *fractal);
void		change_color_sierpinski(int keysym, t_fractal *fractal);
void		swap_colors(t_fractal *fractal);
void		swap_psy_mode(t_fractal *fractal);
int			interpolate_color(int min, int max, int i, t_fractal *fractal);

/* Iterations and contrast management */
void		change_max_iterations(char sign, t_fractal *fractal);
void		change_contrast(char sign, t_fractal *fractal);
void		change_depth_sierpinski(int keysym, t_fractal *fractal);

/* Window and text management */
char		*get_window_name(t_fractal *fractal);
void		manage_text(t_fractal *fractal);
void		put_a_string( int x, int y, char *s, t_fractal *fractal);
void		put_color_mode(t_fractal *fractal);
void		put_max_iterations(t_fractal *fractal);
void		print_shortcuts(t_fractal *fractal);
void		draw_text_boxes(t_fractal *fractal);
void		draw_a_box(t_box *box, t_fractal *fractal);
void		set_real_screen_size(t_fractal *f);

/* Mathematical utilities and complex number operations */
double		scale_map(double nb, double new_min, \
			double new_max, double origin_max);
int			get_max_depth(t_fractal *fractal);
t_complex	sum_complex(t_complex z, t_complex c);
t_complex	square_complex(t_complex z);
t_complex	julia_init_complex(t_pixel *pixel, t_fractal *fractal);

/* Argument parsing and input handling */
int			is_valid_number(const char *str);
void		init_mandelbrot(char **argv, t_fractal *fractal);
void		init_julia(char **argv, t_fractal *fractal);
void		init_sierpinski(char **argv, t_fractal *fractal);
void		init_sierpinski_depth(char **argv, t_fractal *fractal);

/* Export image to PNG */
void		export_image(t_fractal *fractal);
t_fractal	duplicate_fractal(t_fractal *src);
void		restore_fractal(t_fractal *f, t_fractal *backup, t_image *export);

#endif
