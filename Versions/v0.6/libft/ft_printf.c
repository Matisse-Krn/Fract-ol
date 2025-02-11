/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/28 15:24:34 by mkerrien          #+#    #+#             */
/*   Updated: 2024/11/28 15:26:17 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_handling_specifiers(char specifier, va_list args)
{
	int	count;

	count = 0;
	if (specifier == '%')
		count += ft_putchar('%');
	else if (specifier == 'c')
		count += ft_putchar(va_arg(args, int));
	else if (specifier == 's')
		count += ft_putstr(va_arg(args, char *));
	else if (specifier == 'd' || specifier == 'i')
		count += ft_putnbr(va_arg(args, int));
	else if (specifier == 'u')
		count += ft_putunbr(va_arg(args, unsigned int));
	else if (specifier == 'x')
		count += ft_puthex(va_arg(args, unsigned int), 0);
	else if (specifier == 'X')
		count += ft_puthex(va_arg(args, unsigned int), 1);
	else if (specifier == 'p')
		count += ft_putptr(va_arg(args, void *));
	else
		count += ft_putchar('%');
	return (count);
}

int	ft_printf(const char *format, ...)
{
	va_list			args;
	unsigned int	i;
	int				count;

	if (!format)
		return (-1);
	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
			count += ft_handling_specifiers(format[++i], args);
		else
			count += ft_putchar(format[i]);
		i++;
	}
	va_end(args);
	return (count);
}
/*
#include <stdio.h>

int	main(void)
{
	int		o_res;
	int		my_res;
	char	*test;

	// Test simple string
	ft_printf("TEST SIMPLE STRING :\n\n");
	o_res = printf("Hello !\n");
	my_res = ft_printf("Hello !\n");
	ft_printf("Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf("________________________________\n\n");
	// Test %%
	ft_printf("TEST %%%% :\n\n");
	o_res = printf("I like the percent 42%%\n");
	my_res = ft_printf("I like the percent 42%%\n");
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test with consecutive %%
	o_res = printf("%% %% %% %%\n");
	my_res = ft_printf("%% %% %% %%\n");
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test with consecutive %%
	o_res = printf("This is %% tricky %% but %% fun %%\n");
	my_res = ft_printf("This is %% tricky %% but %% fun %%\n");
	ft_printf("Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf("________________________________\n\n");
	ft_printf("TESTS %%c :\n\n");
	// Test %c with simple character
	o_res = printf("This is the char 'c' : %c\n", 'c');
	my_res = ft_printf("This is the char 'c' : %c\n", 'c');
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %c with '\0' character
	o_res = printf("This is the char '\\0' : %c\n", '\0');
	my_res = ft_printf("This is the char '\\0' : %c\n", '\0');
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %c with backspace (ascii 8) character
	o_res = printf("This is the char '\\a' : %c\n", 7);
	my_res = ft_printf("This is the char '\\a' : %c\n", 7);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test with %c passed by his ascii equivalent
	o_res = printf("This should be a star : %c\n", 42);
	my_res = ft_printf("This should be a star : %c\n", 42);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test multiple %c, mixed
	o_res = printf("%c%c2 = %c\n", '4', 42, 56);
	my_res = ft_printf("%c%c2 = %c\n", '4', 42, 56);
	ft_printf("Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf("________________________________\n\n");
	ft_printf("TESTS %%s :\n\n");
	// Test %s with standard string
	o_res = printf("%s\n", "Hello World !");
	my_res = ft_printf("%s\n", "Hello World !");
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %s with empty string
	o_res = printf("%s\n", "");
	my_res = ft_printf("%s\n", "");
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %s with multiple strings
	o_res = printf("%s%s\n", "Hello", " World !");
	my_res = ft_printf("%s%s\n", "Hello", " World !");
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %s = NULL (must compile without flags)
//	o_res = printf("%s\n", NULL);
//	my_res = ft_printf("%s\n", NULL);
//	ft_printf("Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf("________________________________\n\n");
	ft_printf("TESTS %%d :\n\n");
	// Test %d with 0
	o_res = printf("%d\n", 0);
	my_res = ft_printf("%d\n", 0);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %d with -0
	o_res = printf("%d\n", -0);
	my_res = ft_printf("%d\n", -0);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test a simple %d
	o_res = printf("%d\n", 42);
	my_res = ft_printf("%d\n", 42);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %d with INT_MAX
	o_res = printf("%d\n", 2147483647);
	my_res = ft_printf("%d\n", 2147483647);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %d with INT_MAX and INT_MIN (must compile without flags)
//	o_res = printf("INT_MAX = %d || INT_MIN = %d\n", 2147483647, -2147483648);
//	my_res = ft_printf("INT_MAX = %d || INT_MIN = %d\n", \
//2147483647, -2147483648);
//	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %d with INT_MAX overflow (must compile without flags)
//	o_res = printf("INT_MIN passed by INT_MAX overflow : %d\n", 2147483648);
//	my_res = ft_printf("INT_MIN passed by INT_MAX overflow : %d\n", 2147483648);
//	ft_printf("Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf("________________________________\n\n");
	ft_printf("TESTS %%i :\n\n");
	// Test %i with 0
	o_res = printf("%i\n", 0);
	my_res = ft_printf("%i\n", 0);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %i with -0
	o_res = printf("%i\n", -0);
	my_res = ft_printf("%i\n", -0);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test a simple %i
	o_res = printf("%i\n", 42);
	my_res = ft_printf("%i\n", 42);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %i with INT_MAX
	o_res = printf("%i\n", 2147483647);
	my_res = ft_printf("%i\n", 2147483647);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %i with INT_MAX and INT_MIN (must compile without flags)
//	o_res = printf("INT_MAX = %i || INT_MIN = %i\n", 2147483647, -2147483648);
//	my_res = ft_printf("INT_MAX = %i || INT_MIN = %i\n", \
//2147483647, -2147483648);
//	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %i with INT_MAX overflow (must compile without flags)
//	o_res = printf("INT_MIN passed by INT_MAX overflow : %i\n", 2147483648);
//	my_res = ft_printf("INT_MIN passed by INT_MAX overflow : %i\n", 2147483648);
//	ft_printf("Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf("________________________________\n\n");
	ft_printf("TESTS %%u :\n\n");
	// Test %u with 0
	o_res = printf("%u\n", 0);
	my_res = ft_printf("%u\n", 0);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test a simple %u
	o_res = printf("%u\n", 42);
	my_res = ft_printf("%u\n", 42);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %u with UINT_MAX (must compile without flags)
//	o_res = printf("%u\n", 4294967295);
//	my_res = ft_printf("%u\n", 4294967295);
//	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %u with UINT_MAX and UINT_MIN (0) (must compile without flags)
//	o_res = printf("UINT_MAX = %u || UINT_MIN = %u\n", 4294967295, 0);
//	my_res = ft_printf("UINT_MAX = %u || UINT_MIN = %u\n", 4294967295, 0);
//	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %u with INT_MAX overflow (must compile without flags)
//	o_res = printf("UINT_MIN passed by UINT_MAX overflow : %u\n", 4294967296);
//	my_res = ft_printf("UINT_MIN passed by UINT_MAX overflow : \
//%u\n", 4294967296);
//	ft_printf("Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf("________________________________\n\n");
	ft_printf("TESTS %%x :\n\n");
	// Test %x with 0
	o_res = printf("%x\n", 0);
	my_res = ft_printf("%x\n", 0);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test a simple %x
	o_res = printf("%x\n", -42);
	my_res = ft_printf("%x\n", -42);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %x with specific value
	o_res = printf("%x\n", 0xdeadbeef);
	my_res = ft_printf("%x\n", 0xdeadbeef);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %x consecutive addresses
	o_res = printf("42 = %x    43 = %x    44 = %x\n", 42, 43, 44);
	my_res = ft_printf("42 = %x    43 = %x    44 = %x\n", 42, 43, 44);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %x with NULL (must compile without flags)
//	o_res = printf("%x\n", NULL);
//	my_res = ft_printf("%x\n", NULL);
//	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %x with a char * variable (must compile without flags)
//	test = "Hello World !";
//	o_res = printf("%x\n", test);
//	my_res = ft_printf("%x\n", test);
//	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %x with ULONG_MAX (must compile without flags)
//	o_res = printf("%x\n", 18446744073709551615);
//	my_res = ft_printf("%x\n", 18446744073709551615);
//	ft_printf("Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf("________________________________\n\n");
	ft_printf("TESTS %%X :\n\n");
	// Test %X with 0
	o_res = printf("%X\n", 0);
	my_res = ft_printf("%X\n", 0);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test a simple %X
	o_res = printf("%X\n", -42);
	my_res = ft_printf("%X\n", -42);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %X with specific value
	o_res = printf("%X\n", 0xDEADBEEF);
	my_res = ft_printf("%X\n", 0xDEADBEEF);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %X consecutive addresses
	o_res = printf("42 = %X    43 = %X    44 = %X\n", 42, 43, 44);
	my_res = ft_printf("42 = %X    43 = %X    44 = %X\n", 42, 43, 44);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %X with NULL (must compile without flags)
//	o_res = printf("%X\n", NULL);
//	my_res = ft_printf("%X\n", NULL);
//	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %X with a char * variable (must compile without flags)
//	o_res = printf("%X\n", test);
//	my_res = ft_printf("%X\n", test);
//	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %X with ULONG_MAX (must compile without flags)
//	o_res = printf("%X\n", 18446744073709551615);
//	my_res = ft_printf("%X\n", 18446744073709551615);
//	ft_printf("Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf("________________________________\n\n");
	ft_printf("TESTS %%p :\n\n");
	// Test a simple %p (must compile without flags)
//	o_res = printf("%p\n", -42);
//	my_res = ft_printf("%p\n", -42);
//	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %p consecutive addresses (must compile without flags)
//	o_res = printf("42 = %p    43 = %p    44 = %p\n", 42, 43, 44);
//	my_res = ft_printf("42 = %p    43 = %p    44 = %p\n", 42, 43, 44);
//	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %p with NULL (must compile without flags)
	o_res = printf("%p\n", NULL);
	my_res = ft_printf("%p\n", NULL);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %p with a char * variable
	o_res = printf("%p\n", &test);
	my_res = ft_printf("%p\n", &test);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %p with invalid address (must compile without flags)
//	o_res = printf("%p\n", 0xFFFFFFFFFFFFFFFFFFFFFF);
//	my_res = ft_printf("%p\n", 0xFFFFFFFFFFFFFFFFFFFFFF);
//	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %p with ULONG_MAX (must compile without flags)
//	o_res = printf("%p\n", 18446744073709551615);
//	my_res = ft_printf("%p\n", 18446744073709551615);
//	ft_printf("Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf("________________________________\n\n");
	ft_printf("MIXED AND OTHER TESTS :\n\n");
	// Test %c, %s, %d, %i, %u, %% and text
	o_res = ft_printf(" % \n");
	my_res = ft_printf(" % \n");
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	o_res = ft_printf(NULL);
	my_res = ft_printf(NULL);
	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	o_res = printf("Hi %c My name is %s and I hope you enjoy \
this correction !\nIt's maybe my %dst, my %ind or my %urd retry, \
so I hope you will give me a great 100%%...? :D\n", '!', "Matisse", \
1, 2, 3);
	my_res = ft_printf("Hi %c My name is %s and I hope you enjoy \
this correction !\nIt's maybe my %dst, my %ind or my %urd retry, \
so I hope you will give me a great 100%%...? :D\n", '!', "Matisse", \
1, 2, 3);
	ft_printf("Original res : %d || My res : %d\n", o_res, my_res);
	// Test %x, %X, %p and text, with NULL (must compile without flags)
//	o_res = printf("NULL is equivalent to %x (%X in uppercase, but...) \
//and his address is '%p'.\n", NULL, NULL, NULL);
//	my_res = ft_printf("NULL is equivalent to %x (%X in uppercase, but...) \
//and his address is '%p'.\n", NULL, NULL, NULL);
//	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test with invalid specifier (must compile without flags)
//	o_res = printf("Unsupported specifier : %t\n");
//	my_res = ft_printf("Unsupported specifier : %t\n");
//	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	// Ultimate stress test (all specifiers) (must compile without flags)
//	o_res = printf("Char: %c, Str: %s, Dec: %d, Hex: %x, Hex (up): %X, \
//Ptr: %p, Unsigned: %u, Percent: %%\n", '!', "Stress Test", -12345, \
//0xABCDEF, 0xABCDEF, &test, 4294967295);
//	my_res = ft_printf("Char: %c, Str: %s, Dec: %d, Hex: %x, Hex (up): %X, \
//Ptr: %p, Unsigned: %u, Percent: %%\n", '!', "Stress Test", -12345, \
//0xABCDEF, 0xABCDEF, &test, 4294967295);
//	ft_printf("Original res : %d || My res : %d\n\n", o_res, my_res);
	return (0);
}
*/
