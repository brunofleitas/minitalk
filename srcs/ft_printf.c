/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 16:08:21 by bfleitas          #+#    #+#             */
/*   Updated: 2024/04/04 15:53:05 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 Parameters: 
      arg: A pointer to the va_list containing the arguments to be formatted.
      outputType: A pointer to the character specifying the format specifier.
 Return value:
      The number of characters printed based on the format specifier.
 Description:
      This function processes the format specifier and prints the corresponding
	  argument to the standard output.
      It supports various format specifiers including 'c' for characters, 's' 
	  for strings, 'i' or 'd' for integers, 'u' for unsigned integers, 
	  'x' or 'X' for hexadecimal representation, and 'p' for pointers.
*/
int	print_format(va_list *arg, const char *outputType)
{
	int		chars_printed;
	void	*ptr;

	chars_printed = 0;
	if (*outputType == 'c')
		chars_printed += ft_putchar_fd_pf(va_arg(*arg, int), 1);
	if (*outputType == '%')
		chars_printed += ft_putchar_fd_pf('%', 1);
	if (*outputType == 's')
		chars_printed += ft_putstr_fd_pf(va_arg(*arg, char *), 1);
	if (*outputType == 'i' || *outputType == 'd')
		chars_printed += ft_putnbr_fd_pf(va_arg(*arg, int), 1);
	if (*outputType == 'u')
		chars_printed += ft_putunsnbr_fd_pf(va_arg(*arg, unsigned int), 1);
	if (*outputType == 'x')
		chars_printed += ft_put_hex_pf(va_arg(*arg, unsigned int), 1, LOW_HEX);
	if (*outputType == 'X')
		chars_printed += ft_put_hex_pf(va_arg(*arg, unsigned int), 1, UP_HEX);
	if (*outputType == 'p')
	{
		ptr = va_arg(*arg, void *);
		chars_printed += ft_put_ptr_pf(ptr, 1, LOW_HEX);
	}
	return (chars_printed);
}

/*
 Parameters: 
      output: The format string containing text to be printed and format 
	  specifiers.
      ...: Variadic arguments corresponding to the format specifiers in 
	  the output string.
 Return value:
      The number of characters printed to the standard output.
 Description:
      This function is a custom implementation of the printf function. 
	  It processes the format string, identifies format specifiers, 
	  and prints the corresponding arguments to the standard output.
*/
int	ft_printf(const char *output, ...)
{
	int		chars_printed;
	int		i;
	va_list	arg;

	chars_printed = 0;
	i = 0;
	va_start(arg, output);
	while (output[i] != 0)
	{
		if (output[i] != '%')
		{
			chars_printed += ft_putchar_fd_pf(output[i], 1);
			i++;
		}
		else
		{
			chars_printed += print_format(&arg, &output[i + 1]);
			i += 2;
		}
	}
	va_end(arg);
	return (chars_printed);
}
