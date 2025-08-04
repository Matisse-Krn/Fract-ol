/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkerrien <mkerrien@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 18:46:00 by mkerrien          #+#    #+#             */
/*   Updated: 2025/03/09 20:03:55 by mkerrien         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_handling_specifiers(int fd, char specifier, va_list args)
{
	int	count;

	count = 0;
	if (specifier == '%')
		count += ft_putchar_fd('%', fd);
	else if (specifier == 'c')
		count += ft_putchar_fd(va_arg(args, int), fd);
	else if (specifier == 's')
		count += ft_putstr_fd(va_arg(args, char *), fd);
	else if (specifier == 'd' || specifier == 'i')
		count += ft_putnbr_fd(va_arg(args, int), fd);
	else if (specifier == 'u')
		count += ft_putunbr_fd(va_arg(args, unsigned int), fd);
	else if (specifier == 'x')
		count += ft_puthex_fd(va_arg(args, unsigned int), 0, fd);
	else if (specifier == 'X')
		count += ft_puthex_fd(va_arg(args, unsigned int), 1, fd);
	else if (specifier == 'p')
		count += ft_putptr_fd(va_arg(args, void *), fd);
	else
		count += ft_putchar_fd('%', fd);
	return (count);
}

int	ft_printf_fd(int fd, const char *format, ...)
{
	va_list			args;
	unsigned int	i;
	int				count;

	if (fd < 0 || fd >= 1024 || !format)
		return (-1);
	va_start(args, format);
	i = 0;
	count = 0;
	while (format[i])
	{
		if (format[i] == '%')
			count += ft_handling_specifiers(fd, format[++i], args);
		else
			count += ft_putchar_fd(format[i], fd);
		i++;
	}
	va_end(args);
	return (count);
}
/*
#include <stdio.h>

int	main(void)
{
	int		fd;
	int		o_res;
	int		my_res;
	char	*test;

	fd = 2;
	// Test simple string
	ft_printf_fd(fd, "TEST SIMPLE STRING :\n\n");
	o_res = printf("Hello !\n");
	my_res = ft_printf_fd(fd, "Hello !\n");
	ft_printf_fd(fd, "Original res : %d || My res : %d\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	ft_printf_fd(fd, "________________________________\n\n");
	// Test %%
	ft_printf_fd(fd, "TEST %%%% :\n\n");
	o_res = printf("I like the percent 42%%\n");
	my_res = ft_printf_fd(fd, "I like the percent 42%%\n");
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test with consecutive %%
	o_res = printf("%% %% %% %%\n");
	my_res = ft_printf_fd(fd, "%% %% %% %%\n");
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test with consecutive %%
	o_res = printf("This is %% tricky %% but %% fun %%\n");
	my_res = ft_printf_fd(fd, "This is %% tricky %% but %% fun %%\n");
	ft_printf_fd(fd, "Original res : %d || My res : %d\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	ft_printf_fd(fd, "________________________________\n\n");
	ft_printf_fd(fd, "TESTS %%c :\n\n");
	// Test %c with simple character
	o_res = printf("This is the char 'c' : %c\n", 'c');
	my_res = ft_printf_fd(fd, "This is the char 'c' : %c\n", 'c');
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %c with '\0' character
	o_res = printf("This is the char '\\0' : %c\n", '\0');
	my_res = ft_printf_fd(fd, "This is the char '\\0' : %c\n", '\0');
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %c with backspace (ascii 8) character
	o_res = printf("This is the char '\\a' : %c\n", 7);
	my_res = ft_printf_fd(fd, "This is the char '\\a' : %c\n", 7);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test with %c passed by his ascii equivalent
	o_res = printf("This should be a star : %c\n", 42);
	my_res = ft_printf_fd(fd, "This should be a star : %c\n", 42);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test multiple %c, mixed
	o_res = printf("%c%c2 = %c\n", '4', 42, 56);
	my_res = ft_printf_fd(fd, "%c%c2 = %c\n", '4', 42, 56);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	ft_printf_fd(fd, "________________________________\n\n");
	ft_printf_fd(fd, "TESTS %%s :\n\n");
	// Test %s with standard string
	o_res = printf("%s\n", "Hello World !");
	my_res = ft_printf_fd(fd, "%s\n", "Hello World !");
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %s with empty string
	o_res = printf("%s\n", "");
	my_res = ft_printf_fd(fd, "%s\n", "");
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %s with multiple strings
	o_res = printf("%s%s\n", "Hello", " World !");
	my_res = ft_printf_fd(fd, "%s%s\n", "Hello", " World !");
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %s = NULL (must compile without flags)
//	o_res = printf("%s\n", NULL);
//	my_res = ft_printf_fd(fd, "%s\n", NULL);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf_fd(fd, "________________________________\n\n");
	ft_printf_fd(fd, "TESTS %%d :\n\n");
	// Test %d with 0
	o_res = printf("%d\n", 0);
	my_res = ft_printf_fd(fd, "%d\n", 0);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %d with -0
	o_res = printf("%d\n", -0);
	my_res = ft_printf_fd(fd, "%d\n", -0);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test a simple %d
	o_res = printf("%d\n", 42);
	my_res = ft_printf_fd(fd, "%d\n", 42);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %d with INT_MAX
	o_res = printf("%d\n", 2147483647);
	my_res = ft_printf_fd(fd, "%d\n", 2147483647);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %d with INT_MAX and INT_MIN (must compile without flags)
//	o_res = printf("INT_MAX = %d || INT_MIN = %d\n", 2147483647, -2147483648);
//	my_res = ft_printf_fd(fd, "INT_MAX = %d || INT_MIN = %d\n", \
//2147483647, -2147483648);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %d with INT_MAX overflow (must compile without flags)
//	o_res = printf("INT_MIN passed by INT_MAX overflow : %d\n", 2147483648);
//	my_res = ft_printf_fd(fd, "INT_MIN passed by INT_MAX overflow : %d\n",\
// 2147483648);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf_fd(fd, "________________________________\n\n");
	ft_printf_fd(fd, "TESTS %%i :\n\n");
	// Test %i with 0
	o_res = printf("%i\n", 0);
	my_res = ft_printf_fd(fd, "%i\n", 0);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %i with -0
	o_res = printf("%i\n", -0);
	my_res = ft_printf_fd(fd, "%i\n", -0);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test a simple %i
	o_res = printf("%i\n", 42);
	my_res = ft_printf_fd(fd, "%i\n", 42);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %i with INT_MAX
	o_res = printf("%i\n", 2147483647);
	my_res = ft_printf_fd(fd, "%i\n", 2147483647);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %i with INT_MAX and INT_MIN (must compile without flags)
//	o_res = printf("INT_MAX = %i || INT_MIN = %i\n", 2147483647, -2147483648);
//	my_res = ft_printf_fd(fd, "INT_MAX = %i || INT_MIN = %i\n", \
//2147483647, -2147483648);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %i with INT_MAX overflow (must compile without flags)
//	o_res = printf("INT_MIN passed by INT_MAX overflow : %i\n", 2147483648);
//	my_res = ft_printf_fd(fd, "INT_MIN passed by INT_MAX overflow : %i\n",
// 2147483648);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf_fd(fd, "________________________________\n\n");
	ft_printf_fd(fd, "TESTS %%u :\n\n");
	// Test %u with 0
	o_res = printf("%u\n", 0);
	my_res = ft_printf_fd(fd, "%u\n", 0);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test a simple %u
	o_res = printf("%u\n", 42);
	my_res = ft_printf_fd(fd, "%u\n", 42);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %u with UINT_MAX (must compile without flags)
//	o_res = printf("%u\n", 4294967295);
//	my_res = ft_printf_fd(fd, "%u\n", 4294967295);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %u with UINT_MAX and UINT_MIN (0) (must compile without flags)
//	o_res = printf("UINT_MAX = %u || UINT_MIN = %u\n", 4294967295, 0);
//	my_res = ft_printf_fd(fd, "UINT_MAX = %u || UINT_MIN = %u\n", 4294967295, 0);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %u with INT_MAX overflow (must compile without flags)
//	o_res = printf("UINT_MIN passed by UINT_MAX overflow : %u\n", 4294967296);
//	my_res = ft_printf_fd(fd, "UINT_MIN passed by UINT_MAX overflow : \
//%u\n", 4294967296);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf_fd(fd, "________________________________\n\n");
	ft_printf_fd(fd, "TESTS %%x :\n\n");
	// Test %x with 0
	o_res = printf("%x\n", 0);
	my_res = ft_printf_fd(fd, "%x\n", 0);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test a simple %x
	o_res = printf("%x\n", -42);
	my_res = ft_printf_fd(fd, "%x\n", -42);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %x with specific value
	o_res = printf("%x\n", 0xdeadbeef);
	my_res = ft_printf_fd(fd, "%x\n", 0xdeadbeef);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %x consecutive addresses
	o_res = printf("42 = %x    43 = %x    44 = %x\n", 42, 43, 44);
	my_res = ft_printf_fd(fd, "42 = %x    43 = %x    44 = %x\n", 42, 43, 44);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %x with NULL (must compile without flags)
//	o_res = printf("%x\n", NULL);
//	my_res = ft_printf_fd(fd, "%x\n", NULL);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %x with a char * variable (must compile without flags)
//	test = "Hello World !";
//	o_res = printf("%x\n", test);
//	my_res = ft_printf_fd(fd, "%x\n", test);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %x with ULONG_MAX (must compile without flags)
//	o_res = printf("%x\n", 18446744073709551615);
//	my_res = ft_printf_fd(fd, "%x\n", 18446744073709551615);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf_fd(fd, "________________________________\n\n");
	ft_printf_fd(fd, "TESTS %%X :\n\n");
	// Test %X with 0
	o_res = printf("%X\n", 0);
	my_res = ft_printf_fd(fd, "%X\n", 0);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test a simple %X
	o_res = printf("%X\n", -42);
	my_res = ft_printf_fd(fd, "%X\n", -42);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %X with specific value
	o_res = printf("%X\n", 0xDEADBEEF);
	my_res = ft_printf_fd(fd, "%X\n", 0xDEADBEEF);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %X consecutive addresses
	o_res = printf("42 = %X    43 = %X    44 = %X\n", 42, 43, 44);
	my_res = ft_printf_fd(fd, "42 = %X    43 = %X    44 = %X\n", 42, 43, 44);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %X with NULL (must compile without flags)
//	o_res = printf("%X\n", NULL);
//	my_res = ft_printf_fd(fd, "%X\n", NULL);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %X with a char * variable (must compile without flags)
//	o_res = printf("%X\n", test);
//	my_res = ft_printf_fd(fd, "%X\n", test);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %X with ULONG_MAX (must compile without flags)
//	o_res = printf("%X\n", 18446744073709551615);
//	my_res = ft_printf_fd(fd, "%X\n", 18446744073709551615);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf_fd(fd, "________________________________\n\n");
	ft_printf_fd(fd, "TESTS %%p :\n\n");
	// Test a simple %p (must compile without flags)
//	o_res = printf("%p\n", -42);
//	my_res = ft_printf_fd(fd, "%p\n", -42);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %p consecutive addresses (must compile without flags)
//	o_res = printf("42 = %p    43 = %p    44 = %p\n", 42, 43, 44);
//	my_res = ft_printf_fd(fd, "42 = %p    43 = %p    44 = %p\n", 42, 43, 44);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %p with NULL (must compile without flags)
	o_res = printf("%p\n", NULL);
	my_res = ft_printf_fd(fd, "%p\n", NULL);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %p with a char * variable
	o_res = printf("%p\n", &test);
	my_res = ft_printf_fd(fd, "%p\n", &test);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %p with invalid address (must compile without flags)
//	o_res = printf("%p\n", 0xFFFFFFFFFFFFFFFFFFFFFF);
//	my_res = ft_printf_fd(fd, "%p\n", 0xFFFFFFFFFFFFFFFFFFFFFF);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test %p with ULONG_MAX (must compile without flags)
//	o_res = printf("%p\n", 18446744073709551615);
//	my_res = ft_printf_fd(fd, "%p\n", 18446744073709551615);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n", o_res, my_res);
	ft_printf_fd(fd, "________________________________\n\n");
	ft_printf_fd(fd, "MIXED AND OTHER TESTS :\n\n");
	// Test %c, %s, %d, %i, %u, %% and text
//	o_res = printf(" % \n");
//	my_res = ft_printf_fd(fd, " % \n");
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	o_res = printf(NULL);
	my_res = ft_printf_fd(fd, NULL);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	o_res = printf("Hi %c My name is %s and I hope you enjoy \
this correction !\nIt's maybe my %dst, my %ind or my %urd retry, \
so I hope you will give me a great 100%%...? :D\n", '!', "Matisse", \
1, 2, 3);
	my_res = ft_printf_fd(fd, "Hi %c My name is %s and I hope you enjoy \
this correction !\nIt's maybe my %dst, my %ind or my %urd retry, \
so I hope you will give me a great 100%%...? :D\n", '!', "Matisse", \
1, 2, 3);
	ft_printf_fd(fd, "Original res : %d || My res : %d\n", o_res, my_res);
	if (o_res != my_res)
		printf("!! ERROR !!\n");
	// Test %x, %X, %p and text, with NULL (must compile without flags)
//	o_res = printf("NULL is equivalent to %x (%X in uppercase, but...) \
//and his address is '%p'.\n", NULL, NULL, NULL);
//	my_res = ft_printf_fd(fd, "NULL is equivalent to %x (%X in uppercase, \
//but...) and his address is '%p'.\n", NULL, NULL, NULL);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	// Test with invalid specifier (must compile without flags)
//	o_res = printf("Unsupported specifier : %t\n");
//	my_res = ft_printf_fd(fd, "Unsupported specifier : %t\n");
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	// Ultimate stress test (all specifiers) (must compile without flags)
//	o_res = printf("Char: %c, Str: %s, Dec: %d, Hex: %x, Hex (up): %X, \
//Ptr: %p, Unsigned: %u, Percent: %%\n", '!', "Stress Test", -12345, \
//0xABCDEF, 0xABCDEF, &test, 4294967295);
//	my_res = ft_printf_fd(fd, "Char: %c, Str: %s, Dec: %d, Hex: %x, Hex (up): \
//%X, Ptr: %p, Unsigned: %u, Percent: %%\n", '!', "Stress Test", -12345, \
//0xABCDEF, 0xABCDEF, &test, 4294967295);
//	ft_printf_fd(fd, "Original res : %d || My res : %d\n\n", o_res, my_res);
	return (0);
}
*/
