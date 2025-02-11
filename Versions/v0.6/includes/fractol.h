/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 03:38:25 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/08 06:12:55 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include "../libft/libft.h"
# include <math.h>
# include <float.h>

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
	void		*mlx_ptr;
	void		*win_ptr;
	int			max_iterations;
	int			tick_iterations;
	int			color;
	int			depth;
	int			size;
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

void		malloc_error(void);
char		*if_malloc_error(char *s);

void		data_init(t_fractal *fractal);
void		initialize_window(t_fractal *fractal);
void		initialize_image(t_fractal *fractal);
void		initialize_text_image(t_fractal *fractal);
void		initialize_events(t_fractal *fractal);

int			handle_key(int keysym, t_fractal *fractal);
void		handle_key_two(int keysym, t_fractal *fractal);
void		handle_key_three(int keysym, t_fractal *fractal);
int			handle_exit(t_fractal *fractal);
int			handle_mouse(int button, int x, int y, t_fractal *fractal);
int			handle_mouse_move(int x, int y, t_fractal *fractal);

void		my_mlx_pixel_put(t_image *data, int x, int y, int color);
void		fractal_rendering(t_fractal *fractal);
void		apply_zoom(t_fractal *fractal, int x, int y, double factor);
void		displacement(char direction, t_fractal *fractal);
void		change_max_iterations(char sign, t_fractal *fractal);
void		reset_view(t_fractal *fractal);

double		scale_map(double nb, double new_min, \
			double new_max, double origin_max);
t_complex	sum_complex(t_complex z, t_complex c);
t_complex	square_complex(t_complex z);
t_complex	julia_init_complex(t_pixel *pixel, t_fractal *fractal);

char		*get_window_name(t_fractal *fractal);
void		manage_text(t_fractal *fractal);
void		draw_text_boxes(t_fractal *fractal);
void		draw_a_box(t_box *box, t_fractal *fractal);
void		print_shortcuts(t_fractal *fractal);
void		put_max_iterations(t_fractal *fractal);
void		put_a_string( int x, int y, char *s, t_fractal *fractal);
void		put_color_mode(t_fractal *fractal);

void		change_contrast(char sign, t_fractal *fractal);
void		change_color_mode(char mode, t_fractal *fractal);
void		swap_colors(t_fractal *fractal);
void		swap_psy_mode(t_fractal *fractal);
int			interpolate_color(int min, int max, int i, t_fractal *fractal);

void		render_sierpinski(t_fractal *fractal);

#endif
