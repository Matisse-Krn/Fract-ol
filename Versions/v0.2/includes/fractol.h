/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/13 03:38:25 by mkerrien          #+#    #+#             */
/*   Updated: 2025/01/13 06:35:48 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../mlx_linux/mlx.h"
# include "../mlx_linux/mlx_int.h"
# include "../libft/libft.h"
# include <math.h>

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
//	double	ratio;
}			t_image;

typedef struct s_fractal
{
	char	*name;
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	img;
	int		max_iterations;
	double	escape_value;
	double	shift_x;
	double	shift_y;
}			t_fractal;

void		my_mlx_pixel_put(t_image *data, int x, int y, int color);
void		data_init(t_fractal *fractal);
void		initialize_window(t_fractal *fractal);
void		initialize_image(t_fractal *fractal);
double		scale_map(double nb, double new_min, \
			double new_max, double origin_max);
void		fractal_rendering(t_fractal *fractal);
void		initialize_events(t_fractal *fractal);

int			handle_key(int keysym, t_fractal *fractal);
int			handle_exit(t_fractal *fractal);

t_complex	sum_complex(t_complex z, t_complex c);
t_complex	square_complex(t_complex z);

#endif
