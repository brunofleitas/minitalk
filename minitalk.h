/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:50:02 by bfleitas          #+#    #+#             */
/*   Updated: 2024/05/30 12:55:27 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

/* ************************************************************************** */
/* LIBRARIES                                                                  */
/* ************************************************************************** */
# include <signal.h>
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>
/* ************************************************************************** */
/* FUNCTIONS                                                                  */
/* ************************************************************************** */

/*AUXILIARY FUNCTIONS*/
char	*ft_itoa(int nbr);
int		ft_atoi(const char *nptr);

/*TO PRINT CHARS AND STRINGS*/
int		ft_putchar_fd_pf(char c, int fd);
int		ft_strlen_pf(const char *s);
int		ft_putstr_fd_pf(char *s, int fd);

/*TO PRINT NUMBERS*/
int		print_digit_pf(long n, int fd);
int		recursive_pf(long n, int fd);
int		ft_putnbr_fd_pf(int n, int fd);
int		ft_putunsnbr_fd_pf(unsigned int n, int fd);

/*THE MAIN PRINTF FUNCTION AND THE SPECIFIER FUNCTION*/
int		print_format(va_list *arg, const char *outputType);
int		ft_printf(const char *output, ...);

#endif
