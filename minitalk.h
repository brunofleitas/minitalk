/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:50:02 by bfleitas          #+#    #+#             */
/*   Updated: 2024/05/25 03:46:37 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */
/* LIBRARIES                                                                  */
/* ************************************************************************** */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* ************************************************************************** */
/* GLOBAL VARIABLE                                                            */
/* ************************************************************************** */
typedef struct s_global
{
	int		first_string;
	int		i;
	char	*lgth;
}			t_global;