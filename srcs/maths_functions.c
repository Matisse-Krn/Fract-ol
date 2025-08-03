#include "fractol.h"

/*
 * Maps a value from an original range [0, origin_max] to a new range 
	[new_min, new_max] using linear interpolation.
 * 
 * @param nb The input value to be mapped.
 * @param new_min The minimum value of the new range.
 * @param new_max The maximum value of the new range.
 * @param origin_max The maximum value of the original range.
 * @return The mapped value in the new range.
*/
double	scale_map(double nb, double new_min, double new_max, double origin_max)
{
	double	origin_min;

	origin_min = 0;
	return ((new_max - new_min) * (nb - origin_min) / \
	(origin_max - origin_min) + new_min);
}

/*
 * Adds two complex numbers and returns the result.
 * 
 * @param z The first complex number.
 * @param c The second complex number.
 * @return The sum of z and c.
 * 
 * Complex number representation:
	- z.real: Real part
	- z.imag: Imaginary part
*/
t_complex	sum_complex(t_complex z, t_complex c)
{
	t_complex	res;

	res.real = z.real + c.real;
	res.imag = z.imag + c.imag;
	return (res);
}

/*
 * Squares a complex number following the formula:
		(a + bi)^2 = (a^2 - b^2) + (2ab)i.
 * 
 * @param z The complex number to square.
 * @return The squared complex number.
*/
t_complex	square_complex(t_complex z)
{
	t_complex	res;

	res.real = (z.real * z.real) - (z.imag * z.imag);
	res.imag = 2 * z.real * z.imag;
	return (res);
}

/*
 * Initializes a complex number for the Julia set based on the 
	pixel's position, taking into account zoom and displacement.
 * 
 * @param pixel A pointer to the pixel structure containing coordinates.
 * @param fractal A pointer to the fractal structure.
 * @return The initialized complex number.
*/
t_complex	julia_init_complex(t_pixel *pixel, t_fractal *fractal)
{
	t_complex	z;
	double		x_range;

	x_range = fractal->zoom_rate * fractal->aspect_ratio;
	z.real = scale_map(pixel->x, -x_range, x_range, fractal->img.width)
		+ fractal->shift_x;
	z.imag = scale_map(pixel->y, fractal->zoom_rate, -fractal->zoom_rate,
			fractal->img.height) + fractal->shift_y;
	return (z);
}

/*
		// Avec z1 = (a + bi)  et  z2 = (c + di)
// Multiplier deux nombres complexes : (a + bi)*(c + di) = (ac - bd)+(ad + bc)i

void	add_complex(void)
{
	t_complex	z1;
	t_complex	z2;
	t_complex	res;

	z1.real = 2;
	z1.imag = 3;
	z2.real = 1;
	z2.imag = -2;
	res.real = z1.real + z2.real;
	res.imag = z1.imag + z2.imag;
	printf("'%f + %fi'\n", res.real, res.imag);
	return ;
}

void	mult_complex(void)
{
	t_complex	z1;
	t_complex	z2;
	t_complex	res;

	z1.real = 2;
	z1.imag = 3;
	z2.real = 1;
	z2.imag = -2;
	res.real = (z1.real * z2.real) - (z1.imag * z2.imag);
	res.imag = (z1.real * z2.imag) + (z1.imag * z2.real);
	printf("'%f + %fi'\n", res.real, res.imag);
	return ;
}

void	absolute_value_complex(void)
{
	t_complex	z;
	double		res;

	z.real = 3;
	z.imag = 3;
	res = sqrt(pow(z.real, 2) + pow(z.imag, 2));
	printf("|z| = %f\n", res);
	return ;
}
*/
/*
int	main(void)
{
	printf("ADDITION :\n\n");
	add_complex();
	printf("\n----------------------------------\n\n");
	printf("MULTIPLICATION :\n\n");
	mult_complex();
	printf("\n----------------------------------\n\n");
	printf("ABSOLUTE VALUE (=\"MODULE\") :\n\n");
	absolute_value_complex();
	return (0);
}
*/
		// Avec z1 = (a + bi)  et  z2 = (c + di)
// Multiplier deux nombres complexes : (a + bi)*(c + di) = (ac - bd)+(ad + bc)i
// Additionner deux nombres complexes : (a + bi)+(c + di) = (a+c) + (b+d)i
// Module d'un nombre complexe : |z| = √(reel^2 + imaginaire^2)
