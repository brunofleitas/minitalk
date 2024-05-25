/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:39:51 by bfleitas          #+#    #+#             */
/*   Updated: 2024/05/25 03:55:55 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_global	*g_var = NULL;

void	initialize_g_var(void)
{
	g_var = malloc(sizeof(t_global));
	if (g_var == NULL)
	{
		printf("MAlloc error");
		exit(1);
	}
	g_var->first_string = 0;
	g_var->i = 0;
	g_var->lgth = malloc(11 * sizeof(char));
	if (g_var->lgth == NULL)
	{
		printf("MAlloc error");
		exit(1);
	}
}

void	generate_first_string(int *c, char **str)
{
	if ((*c))
	{
		g_var->lgth[g_var->i] = (*c);
		g_var->i++;
	}
	else if (!(*c))
	{
		g_var->lgth[g_var->i] = (*c);
		g_var->first_string = 1;
		(*str) = malloc((atoi(g_var->lgth) + 1) * sizeof(char));
		free(g_var->lgth);
		g_var->i = 0;
	}
}

void	generate_second_string(int *c, char **str, siginfo_t **info)
{
	if ((*c))
	{
		(*str)[g_var->i] = (*c);
		g_var->i++;
	}
	else if (!(*c))
	{
		printf("%s\n", *str);
		free(*str);
		initialize_g_var();
		kill((*info)->si_pid, SIGUSR1);
	}
}

void	handle_binary(int sig, siginfo_t *info, void *context)
{
	static int	c;
	static int	bit;
	static char	*str;

	(void)context;
	if (sig == SIGUSR1)
		c |= (1 << bit);
	if (++bit == 8)
	{
		if (g_var->first_string == 0)
			generate_first_string(&c, &str);
		else if (g_var->first_string == 1)
			generate_second_string(&c, &str, &info);
		bit = 0;
		c = 0;
	}
}

int	main(void)
{
	struct sigaction	sa;

	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_sigaction = handle_binary;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	initialize_g_var();
	printf("PID of the server: %d\n", getpid());
	while (1)
		usleep(100);
}
