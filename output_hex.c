/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_hex.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 15:11:28 by bfleitas          #+#    #+#             */
/*   Updated: 2024/03/15 14:38:42 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 Parameters: 
      n: The unsigned long long integer to be converted to a hexadecimal string.
      hex: The buffer where the hexadecimal string will be stored.
      hex_chars: The string containing the hexadecimal characters 
	  (e.g., "0123456789abcdef").
 Return value:
      The length of the generated hexadecimal string.
 Description:
      This function converts an unsigned long long integer to a hexadecimal
	  string representation.
      It starts by checking if the number is zero, in which case it simply sets
	  the first character of the hex string to '0'.
      Otherwise, it iterates through the number, converting each digit to its
	  corresponding hexadecimal character
      by using the modulus operator with 16 and the hex_chars string as a
	  lookup table.
      The function then divides the number by 16 to process the next digit.
      The resulting hexadecimal string is null-terminated and the length of the
	  string is returned.
*/
int	ft_generate_hex_pf(unsigned long long n, char *hex, const char *hex_chars)
{
	int	i;

	i = 0;
	if (n == 0)
	{
		hex[i++] = '0';
	}
	else
	{
		while (n != 0)
		{
			hex[i++] = hex_chars[n % 16];
			n /= 16;
		}
	}
	hex[i] = '\0';
	return (i);
}

/*
 Parameters: 
      str: The string to be reversed.
      length: The length of the string.
 Return value:
      None.
 Description:
      This function reverses a string in place.
      It uses two pointers, one starting at the beginning of the string and 
	  the other at the end.
      It swaps the characters at these pointers, then moves the pointers 
	  towards each other until they meet in the middle.
      This effectively reverses the string without needing additional space.
*/
void	ft_reverse_string_pf(char *str, int length)
{
	int		left;
	int		right;
	char	temp;

	left = 0;
	right = length - 1;
	while (left < right)
	{
		temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		left++;
		right--;
	}
}

/*
 Parameters: 
      n: The unsigned long long integer to be converted to a hexadecimal string.
      hex: The buffer where the hexadecimal string will be stored.
      hex_chars: The string containing the hexadecimal characters 
	  (e.g., "0123456789abcdef").
 Return value:
      The length of the generated hexadecimal string.
 Description:
      This function converts an unsigned long long integer to a hexadecimal 
	  string representation.
      It generates the hexadecimal string by calling ft_generate_hex_pf, 
	  which fills the hex buffer with the hexadecimal digits.
      Then, it reverses the generated hexadecimal string in place using 
	  ft_reverse_string_pf, as the generated string is in reverse order.
      Finally, it returns the length of the hexadecimal string.
*/
int	ft_convert_to_hex_pf(unsigned long long n, char *hex, const char *hex_chars)
{
	int	length;

	length = ft_generate_hex_pf(n, hex, hex_chars);
	ft_reverse_string_pf(hex, length);
	return (length);
}

/*
 Parameters: 
      n: The unsigned long long integer to be printed as hexadecimal.
      fd: The file descriptor where the hexadecimal representation will be 
	  printed.
      hex_chars: The string containing the hexadecimal characters 
	  (e.g., "0123456789abcdef").
 Return value:
      The number of characters printed.
 Description:
      This function prints the hexadecimal representation of an unsigned 
	  long long integer to the specified file descriptor.
      It first converts the integer to a hexadecimal string using 
	  ft_convert_to_hex_pf, then writes the hexadecimal string to the file
	  descriptor using the write system call.
      The function returns the number of characters printed.
*/
int	ft_put_hex_pf(unsigned long long n, int fd, const char *hex_chars)
{
	char	hex[32];
	int		count;

	count = ft_convert_to_hex_pf(n, hex, hex_chars);
	write(fd, hex, count);
	return (count);
}

int	ft_put_ptr_pf(void *ptr, int fd, const char *hex_chars)
{
	int	counter;

	counter = 0;
	if (ptr == NULL)
		counter += ft_putstr_fd_pf("(nil)", 1);
	else
	{
		counter += ft_putstr_fd_pf("0x", 1);
		counter += ft_put_hex_pf((unsigned long)ptr, fd, hex_chars);
	}
	return (counter);
}
