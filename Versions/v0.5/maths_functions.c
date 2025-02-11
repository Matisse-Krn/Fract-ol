/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:38:50 by mkerrien          #+#    #+#             */
/*   Updated: 2025/02/07 19:46:39 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/fractol.h"

/*
 * Translate the screen coordinates from their dimensions sizes (i.e 800, 800)
 * to the Mandelbrot fractal needed 'map' size (-2, 2) or (-1.5, 1.5)
*/
double	scale_map(double nb, double new_min, double new_max, double origin_max)
{
	double	origin_min;

	origin_min = 0;
	return ((new_max - new_min) * (nb - origin_min) / \
	(origin_max - origin_min) + new_min);
}

t_complex	sum_complex(t_complex z, t_complex c)
{
	t_complex	res;

	res.real = z.real + c.real;
	res.imag = z.imag + c.imag;
	return (res);
}

t_complex	square_complex(t_complex z)
{
	t_complex	res;

	res.real = (z.real * z.real) - (z.imag * z.imag);
	res.imag = 2 * z.real * z.imag;
	return (res);
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
