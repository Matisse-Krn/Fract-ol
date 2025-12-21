#ifndef FRACTOL_H
# define FRACTOL_H

# define TRUE 1
# define FALSE 0

// # define STB_IMAGE_WRITE_IMPLEMENTATION
// # include "stb_image_write.h"
# include "mlx.h"
# include "mlx_int.h"
# include "libft.h"
# include <math.h>
# include <float.h>
# include <time.h>
# include <sys/time.h>
# include <sys/stat.h>

# include <pthread.h>

typedef struct s_complex_nb
{
	double	real;
	double	imag;
}			t_complex;

typedef struct s_image
{
	void			*img_ptr;
	char			*px_ptr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				full_width;
	int				full_height;
	int				height;
	int				width;
	pthread_mutex_t	lock;
}					t_image;

typedef struct s_fractal
{
	char		*name;
	char		*init_c_real;
	char		*init_c_imag;
	char		*last_pos;
	char		color_mode;
	char		range_color_mode;
	char		render_mode;
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
	int			exporting;
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
	/* -------- Buddhabrot -------- */
	int				bb_min_iter;
	int				bb_max_iter;
	int				bb_samples_per_tick;
	char			bb_nebula;          /* 'N' = off, 'Y' = Nebulabrot (plus tard) */
	unsigned int	bb_seed;
	uint64_t		bb_samples_total;
	uint32_t		bb_max_count;
	uint32_t		*bb_hist;           /* simple mode */
	uint32_t		*bb_hist_r;         /* Nebulabrot */
	uint32_t		*bb_hist_g;
	uint32_t		*bb_hist_b;
	t_image		img;
	t_complex	c;
}				t_fractal;

typedef struct s_img_snapshot
{
	void		*img_ptr;
	char		*px_ptr;
	int			width;
	int			height;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
	int			full_width;
	int			full_height;
}				t_img_snapshot;

typedef struct s_bb_export_ctx
{
	t_image		orig;
	t_image		tmp;
}				t_bb_export_ctx;

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
	int			local_max;
}				t_thread_args;

typedef struct s_bb_args t_bb_args;
struct s_bb_args
{
	t_fractal			*f;
	uint32_t			*local_hist;
	unsigned int		seed;
	int					samples;
	int					local_max;
	int					tid;
	int					nthreads;
	t_bb_args			*all;
	pthread_barrier_t	*barrier;
};

typedef struct s_bounds
{
	double			xmin;
	double			xmax;
	double			ymin;
	double			ymax;
}					t_bounds;

typedef struct s_bb_accum
{
	uint32_t		*hist;
	uint32_t		*max;
}					t_bb_accum;

typedef struct s_bb_mt_ctx
{
	int					n;
	int					count;
	int					spt;
	pthread_t			*th;
	t_bb_args			*args;
	pthread_barrier_t	barrier;
}						t_bb_mt_ctx;

/* Memory and error handling */
void		malloc_error(void);
char		*if_malloc_error(char *s);
void		check_valid_input_numbers(char **argv);
void		usage_error(void);

/* Program initialization */
void		data_init(t_fractal *fractal);
void		data_init_sierpinski(t_fractal *fractal);
void		invalid_depth(char **argv, t_fractal *fractal);
void		initialize_window(t_fractal *f);
void		initialize_image(t_fractal *fractal);

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
int			handle_key_julia_mandelbrot(int keysym, t_fractal *fractal);
int			handle_key_sierpinski(int keysym, t_fractal *fractal);
int			handle_key_buddhabrot(int keysym, t_fractal *fractal);
int			handle_exit(t_fractal *fractal);
int			handle_mouse_julia_mandelbrot(int button, int x, int y, t_fractal *fractal);
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
int			jump_menu(void);
int			handle_jump_choice(t_fractal *f, int choice);

/* Color management */
int			distrib_colors(t_complex *z, t_pixel *pixel, t_fractal *f);
void		change_color_mode(char mode, t_fractal *fractal);
void		change_color_sierpinski(int keysym, t_fractal *fractal);
void		swap_colors(t_fractal *fractal);
void		swap_range_color_mode(t_fractal *fractal);
int			interpolate_color(int min, int max, int i, t_fractal *fractal);
void		switch_render_mode(t_fractal *f);
char		*get_render_mode_label(char mode);

/* Adaptive mode utils */
void		find_imax_frame(char type, t_fractal *f);
int			find_imax_frame_mt(t_fractal *f);
int			iters_to_diverge_mandelbrot(t_pixel *p, t_fractal *f);
int			iters_to_diverge_julia(t_pixel *p, t_fractal *f);

/* Iterations and contrast management */
void		change_max_iterations(char sign, t_fractal *fractal);
void		change_contrast(char sign, t_fractal *fractal);
void		change_depth_sierpinski(int keysym, t_fractal *fractal);

/* Window and text management */
char		*get_window_name(t_fractal *fractal);
void		manage_text(t_fractal *fractal);
void		put_a_string( int x, int y, char *s, t_fractal *fractal);
void		put_zoom_and_position(t_fractal *f);
void		put_color_mode(t_fractal *fractal);
void		put_render_mode(t_fractal *f);
void		put_max_iterations(t_fractal *fractal);
void		print_shortcuts(t_fractal *fractal);
void		draw_text_boxes(t_fractal *fractal);
void		draw_a_box(t_box *box, t_fractal *fractal, int color);
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
void		init_julia(char **argv, t_fractal *f);
void		init_sierpinski(char **argv, t_fractal *fractal);
void		init_sierpinski_depth(char **argv, t_fractal *fractal);

/* Julia's presets */
void		assign_params(char **argv, t_fractal *f);
void		set_preset(char *arg, t_fractal *f);
void		set_preset6(char *arg, t_fractal *f);

/* Export image to PNG */
void		setup_export_image(t_image *export, t_fractal *fractal);
void		img_snapshot_take(t_img_snapshot *s, t_image *img);
void		img_snapshot_apply(t_image *img, const t_img_snapshot *s);
void		export_image(t_fractal *fractal);
char		*build_sierpinski_filename(t_fractal *f, int suffix);
t_fractal	duplicate_fractal(t_fractal *src);
void		restore_fractal(t_fractal *f, t_fractal *backup, \
			const t_img_snapshot *orig);
void		compute_imax_for_export(t_fractal *f);

/* Help, Man, Documentation */
void		handle_help(char **argv);
void		print_help(void);
void		print_other_notes(void);
void		print_reminder_shortcuts(void);
void		print_mandelbrot_presets(void);



/* buddhabrot_init.c */
void		init_buddhabrot(char **argv, t_fractal *f);
int			bb_alloc_histograms(t_fractal *f);
void		bb_reset_histograms(t_fractal *f);
void		bb_free_histograms(t_fractal *f);

/* buddhabrot.c */
int			buddhabrot_loop(void *param);
// void		buddhabrot_render_once(t_fractal *f);
void		bb_draw_from_histogram(t_fractal *f);

/* buddhabrot_histogram.c */
void		bb_hist_zero(uint32_t *hist, int count);
void		bb_hist_merge(uint32_t *dst, uint32_t *src, int count, uint32_t *max_out);
int			bb_world_to_screen(const t_fractal *f, double x_real, double y_imag, t_pixel *screen);
int			bb_reject_cardioid_bulb(double real_c, double imag_c);

/* buddhabrot_mt_sampling_core.c */
double		bb_rand_range(unsigned int *seed, double lo, double hi);
void		bb_orbit_accumulate(const t_fractal *f, t_complex c, int esc, t_bb_accum *acc);

/* buddhabrot_mt_ctx.c */
int			bb_mt_prepare_ctx(const t_fractal *f, t_bb_mt_ctx *ctx);
void		bb_mt_fill_arg_common(t_fractal *f, t_bb_mt_ctx *ctx, int i);
void		bb_mt_cleanup_partial(t_bb_mt_ctx *ctx, int upto);
void	bb_mt_finalize(t_fractal *f, t_bb_mt_ctx *ctx, uint32_t max_after_merge);

/* buddhabrot_color.c */
double		bb_normalize_iteration_count(uint32_t iteration_count, uint32_t iteration_max, t_fractal *fractal);

/* buddhabrot_sampling.c */
int				bb_run_samples_single(t_fractal *f, int n);
unsigned int	bb_xorshift(unsigned int *state);

/* Orchestration MT */
// void		bb_render_tick_single(t_fractal *f);
void		bb_render_tick_mt(t_fractal *f);

/* Routine thread */
void		*bb_thread_routine(void *arg);

/* Utils MT */
int			bb_alloc_local_hist(uint32_t **hist, int count);
void		bb_free_local_hist(uint32_t **hist);
int			bb_escape_iter(const t_fractal *f, t_complex c);
int			bb_run_samples_local(t_fractal *f, int n, unsigned int *seed, t_bb_accum *acc);

/* palette_utils.c */
int			bb_palette_ramp5(double t);


int	export_view_png(t_fractal *f, const char *filepath);
int	export_view_auto(t_fractal *f);

/* buddhabrot_export_utils.c */
int			ensure_exports_dir(void);
char		*generate_view_export_filename(t_fractal *f);

/* buddhabrot_mutex.c */
void		img_lock_init(t_image *img);
void		img_lock_destroy(t_image *img);
int			snap_lock(t_image *img);
void		snap_unlock(t_image *img);

#endif
