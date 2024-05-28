/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:39:51 by bfleitas          #+#    #+#             */
/*   Updated: 2024/05/28 16:08:11 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_first_str;


void	generate_first_string(int *c, char **str, int *str_size, int *i)
{
	if ((*c))
	{
		(*str_size) = (((*c) - 48) + ((*str_size) * 10));
	}
	else if (!(*c))
	{
		g_first_str = 1;
		ft_printf("\n%i\n", (*str_size));
		(*str) = malloc(((*str_size) + 1) * sizeof(char));
		if (!(*str))
		{
			write(2, "Error", 5);
			exit(1);
		}
		(*str)[(*str_size) + 1] = '\0';
		(*i) = 0;
	}
}

void	generate_second_string(int *c, char **str, siginfo_t **info, int *i)
{
	if ((*c))
	{
		(*str)[(*i)] = (*c);
		(*i)++;
	}
	else if (!(*c))
	{
		ft_printf("\n%i\n", *i);static int	str_size;
		ft_printf("%s\n", *str);
		free(*str);
		kill((*info)->si_pid, SIGUSR1);
		g_first_str = 0;
	}
}

void	handle_binary(int sig, siginfo_t *info, void *context)
{
	static int	c;
	static int	bit;
	static char	*str;
	static int	str_size;
	static int	i;

	(void)context;
	if (sig == SIGUSR1)
	{
		c |= (1 << bit);
	}
	if (++bit == 8)
	{
		if (g_first_str == 0)
			generate_first_string(&c, &str, &str_size, &i);
		else if (g_first_str == 1)
		{
			generate_second_string(&c, &str, &info, &i);
			str_size = 0;
		}
		bit = 0;
		c = 0;
	}
	kill((info)->si_pid, SIGUSR2);
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sa.sa_sigaction = handle_binary;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	ft_printf("PID of the server: %d\n", getpid());
	while (1)
		sleep(1);
}
