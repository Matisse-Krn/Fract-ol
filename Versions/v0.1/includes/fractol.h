#ifndef FRACTOL_H
#define FRACTOL_H

#include "../mlx_linux/mlx.h"
#include "../mlx_linux/mlx_int.h"
#include <math.h>

typedef struct s_complex_nb
{
	char	*name;
	double	real;
	double	imag;
}	t_complex;

typedef struct s_data
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct	s_vars
{
	void	*mlx;
	void	*win;
	int		radius;
}	t_vars;

#endif
