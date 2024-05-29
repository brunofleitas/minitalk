/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_nbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:44:16 by bfleitas          #+#    #+#             */
/*   Updated: 2024/03/15 14:03:55 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 Parameters: 
      n: The long integer whose digit is to be printed.
      fd: The file descriptor where the digit will be printed.
 Return value:
      The number of characters printed, which is always 1.
 Description:
      This function prints the digit of a long integer to the specified 
	  file descriptor.
      It converts the long integer to its corresponding ASCII character 
	  by adding '0' to it, writes the character to the file descriptor 
	  using the write system call, and returns 1, indicating one character 
	  was printed.
*/
int	print_digit_pf(long n, int fd)
{
	char	num;

	num = n + '0';
	write(fd, &num, 1);
	return (1);
}

/*
 Parameters: 
      n: The long integer to be printed.
      fd: The file descriptor where the integer will be printed.
 Return value:
      The number of characters printed.
 Description:
      This function prints a long integer to the specified file 
	  descriptor using recursion.
      It first checks if the number is greater than 9, and if so, 
	  it recursively calls itself with the number divided by 10.
      Then, it prints the last digit of the number by calling print_digit_pf
	  with the remainder of the number divided by 10.
      The function returns the total number of characters printed.
*/
int	recursive_pf(long n, int fd)
{
	int	count;

	count = 0;
	if (n > 9)
		count += recursive_pf(n / 10, fd);
	count += print_digit_pf(n % 10, fd);
	return (count);
}

/*
 Parameters: 
      n: The integer to be printed.
      fd: The file descriptor where the integer will be printed.
 Return value:
      The number of characters printed.
 Description:
      This function prints an integer to the specified file descriptor.
      If the integer is negative, it prints a minus sign and converts 
	  the integer to its absolute value.
      It then checks if the absolute value is less than 10, in which case
	  it prints the digit directly.
      Otherwise, it uses a recursive function to print each digit of the number.
      The function returns the total number of characters printed.
*/
int	ft_putnbr_fd_pf(int n, int fd)
{
	long	nb;
	int		count;

	count = 0;
	nb = n;
	if (n < 0)
	{
		write(fd, "-", 1);
		nb = nb * -1;
		count++;
	}
	if (nb < 10)
		count += print_digit_pf(nb, fd);
	else
		count += recursive_pf(nb, fd);
	return (count);
}

/*
 Parameters: 
      n: The unsigned integer to be printed.
      fd: The file descriptor where the integer will be printed.
 Return value:
      The number of characters printed.
 Description:
      This function prints an unsigned integer to the specified file descriptor.
      It checks if the number is less than 10, in which case it prints the 
	  digit directly.
      Otherwise, it uses a recursive function to print each digit of the number.
      The function returns the total number of characters printed.
*/
int	ft_putunsnbr_fd_pf(unsigned int n, int fd)
{
	long	nb;
	int		count;

	count = 0;
	nb = n;
	if (nb < 10)
		count += print_digit_pf(nb, fd);
	else
		count += recursive_pf(nb, fd);
	return (count);
}
