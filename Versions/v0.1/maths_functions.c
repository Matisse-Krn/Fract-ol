/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:38:50 by mkerrien          #+#    #+#             */
/*   Updated: 2025/01/05 20:29:05 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "includes/fractol.h"

void	add_complex(void)
{ 
	t_complex z1;
	t_complex z2;
	t_complex res;

	z1.name = "z1";
	z1.real=2;
	z1.imag=3;

	z2.name="z2";
	z2.real=1;
	z2.imag=-2;

	res.name="res";
	res.real=z1.real+z2.real;
	res.imag=z1.imag+z2.imag;

	printf("%s = '%f + %fi'\n", res.name, res.real, res.imag);
	return ;
}

void	mult_complex(void)
{
	t_complex z1;
	t_complex z2;
	t_complex res;
	
	z1.name = "z1";
	z1.real = 2;
	z1.imag = 3;

	z2.name = "z2";
	z2.real = 1;
	z2.imag = -2;

	res.name = "res";
	res.real = (z1.real*z2.real) - (z1.imag*z2.imag);
	res.imag = (z1.real*z2.imag) + (z1.imag*z2.real);

	printf("%s = '%f + %fi'\n", res.name, res.real, res.imag);
	return ;
}

void	absolute_value_complex(void)
{
	t_complex z;
	double res;
	
	z.name = "z1";
	z.real = 3;
	z.imag = 3;

	res = sqrt(pow(z.real,2) + pow(z.imag, 2));
	printf("|%s| = %f\n", z.name, res);
	return ;
}

int	main(void)
{
	printf("ADDITION :\n\n");
	add_complex();
	printf("\n----------------------------------\n\n");
	printf("MULTIPLICATION :\n\n");
	mult_complex();
	printf("\n----------------------------------\n\n");
	printf("ABSOLUTE VALUE (=\"MODULE\") :\n\n");
	absolute_value_complex();*/
	return (0);
}

// Multiplier deux nombres complexes : (a + bi)*(c + di) = (ac - bd)+(ad + bc)i
// Additionner deux nombres complexes : (a + bi)+(c + di) = (a+c) + (b+d)i
// Module d'un nombre complexe : |z| = √(reel^2 + imaginaire^2)
