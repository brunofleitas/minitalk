/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:39:51 by bfleitas          #+#    #+#             */
/*   Updated: 2024/05/29 16:54:41 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_first_str;

/*
 Parameters: 
     int *c: Pointer to the digit to process.
     char **str: Pointer to the string to allocate.
     int *str_size: Pointer to the calculated size of the string.
     int *i: Pointer to the index for string manipulation.
 Description:
     Calculates the size of the string to be generated based on digits received
	 through 'c'. Upon receiving a zero ('0'), allocates memory for the string 
	 initializes it, and prepares for the next phase of string generation by 
	 setting 'g_first_str' to 1.
*/
void	generate_first_string(int *c, char **str, int *str_size, int *i)
{
	if ((*c))
		(*str_size) = (((*c) - 48) + ((*str_size) * 10));
	else if (!(*c))
	{
		g_first_str = 1;
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

/*
 Parameters: 
     int *c: Pointer to the character to append.
     char **str: Pointer to the string being built.
     siginfo_t **info: Pointer to signal info for sending SIGUSR1.
     int *i: Pointer to the current position in the string.
 Description:
     Appends a character to the string if 'c' is non-zero. If 'c' is zero, 
	 prints the string length, the string itself, frees the allocated memory 
	 for the string, sends SIGUSR1 to the original sender, and resets 
	 'g_first_str' to indicate readiness for a new string generation cycle.
*/
void	generate_second_string(int *c, char **str, siginfo_t **info, int *i)
{
	if ((*c))
	{
		(*str)[(*i)] = (*c);
		(*i)++;
	}
	else if (!(*c))
	{
		ft_printf("%s\n", *str);
		free(*str);
		kill((*info)->si_pid, SIGUSR1);
		g_first_str = 0;
	}
}

/*
 Parameters: 
     int sig: Signal type.
     siginfo_t *info: Signal info.
     void *context: Unused context.
 Description:
     Processes SIGUSR1 signals, accumulating bits into a byte. Generates a 
	 string upon collecting 8 bits, toggling between first and second string 
	 generation based on 'g_first_str'. Responds with SIGUSR2.
*/
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

/*
 Function: main
 Parameters: 
     None
 Return value:
     int: Does not return due to the infinite loop.
 Description:
     Sets up signal handling for SIGUSR1 and SIGUSR2, prints the server's PID
	 and enters an infinite loop.
*/
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
