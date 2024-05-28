/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 15:24:28 by bfleitas          #+#    #+#             */
/*   Updated: 2024/03/11 16:53:33 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

/* ************************************************************************** */
/*                              EXTERNAL LIBRARY                              */
/* ************************************************************************** */

# include <stdarg.h>
# include <unistd.h>

/* ************************************************************************** */
/*                              DEFINITIONS                                   */
/* ************************************************************************** */

# define LOW_HEX "0123456789abcdef"
# define UP_HEX "0123456789ABCDEF"

/* ************************************************************************** */
/*                               FUNCTIONS                                    */
/* ************************************************************************** */

/*TO PRINT CHARS AND STRINGS*/
int		ft_putchar_fd_pf(char c, int fd);
int		ft_strlen_pf(const char *s);
int		ft_putstr_fd_pf(char *s, int fd);

/*TO PRINT NUMBERS*/
int		print_digit_pf(long n, int fd);
int		recursive_pf(long n, int fd);
int		ft_putnbr_fd_pf(int n, int fd);
int		ft_putunsnbr_fd_pf(unsigned int n, int fd);

/*TO PRINT NUMBERS IN HEXADECIMAL*/
int		ft_generate_hex_pf(unsigned long long n, char *hex,
			const char *hex_chars);
void	ft_reverse_string_pf(char *str, int length);
int		ft_convert_to_hex_pf(unsigned long long n, char *hex,
			const char *hex_chars);
int		ft_put_hex_pf(unsigned long long n, int fd, const char *hex_chars);
int		ft_put_ptr_pf(void *ptr, int fd, const char *hex_chars);

/*THE MAIN PRINTF FUNCTION AND THE SPECIFIER FUNCTION*/
int		print_format(va_list *arg, const char *outputType);
int		ft_printf(const char *output, ...);

#endif
