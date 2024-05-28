/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_char_string.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 14:43:16 by bfleitas          #+#    #+#             */
/*   Updated: 2024/03/20 14:19:44 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
 Parameters: 
      c: The character to be printed.
      fd: The file descriptor where the character will be printed.
 Return value:
      The number of characters printed, which is always 1.
 Description:
      This function writes a single character to the specified file descriptor.
      It uses the write system call to output the character and returns 1, 
	  indicating one character was printed.
*/
int	ft_putchar_fd_pf(char c, int fd)
{
	write(fd, &c, 1);
	return (1);
}

/*
 Parameters: 
      s: The string whose length is to be determined.
 Return value:
      The length of the string.
 Description:
      This function calculates and returns the length of a string.
      It iterates through the string until it encounters the null 
	  character '\0', incrementing a counter for each character.
*/
int	ft_strlen_pf(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

/*
 Parameters: 
      s: The string to be printed.
      fd: The file descriptor where the string will be printed.
 Return value:
      The number of characters printed.
 Description:
      This function prints a string to the specified file descriptor.
      If the string is NULL, it prints "(null)" and returns 6.
      Otherwise, it iterates through the string, printing each character 
	  using ft_putchar_fd_pf, and returns the number of characters printed.
*/
int	ft_putstr_fd_pf(char *s, int fd)
{
	int	i;

	i = 0;
	if (s == NULL)
	{
		write(fd, "(null)", 6);
		return (6);
	}
	while (s[i] != '\0')
	{
		ft_putchar_fd_pf(s[i], fd);
		i++;
	}
	return (i);
}
