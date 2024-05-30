/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:39:40 by bfleitas          #+#    #+#             */
/*   Updated: 2024/05/30 12:54:55 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static int	g_c_recevied;

/*
 Parameters:
		int pid: Process ID to which the character will be sent as bits.
		char c: Character to be converted to bits and sent.
 Description:
		Converts a single character 'c' into its binary representation and sends
		each bit to the specified process ID using SIGUSR1 for a bit set to 1 and
		SIGUSR2 for a bit set to 0. Waits for confirmation that each bit
		has been received before proceeding to the next bit.
*/
void	char_to_bits(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		g_c_recevied = 0;
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		while (g_c_recevied != 1)
			usleep(100);
	}
}

/*
 Parameters:
		int pid: Process ID to which the string will be sent.
		char *str: String to be converted to bits and sent.
 Description:
		Converts each character of the input string to bits and sends them to the
		specified process ID using the 'char_to_bits' function. Ensures that the
		null terminator of the string is also processed.
*/
void	send_string(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		char_to_bits(pid, str[i++]);
	if (str[i] == '\0')
		char_to_bits(pid, str[i++]);
}

/*
 Parameters:
		int sig: Signal type (SIGUSR1 or SIGUSR2).
		siginfo_t *info: Signal info (ignored).
		void *context: Unused context (ignored).
 Description:
		Handles SIGUSR1 and SIGUSR2 signals. Sets 'g_c_received' to 1 upon
		receiving SIGUSR2. Prints a success message upon receiving SIGUSR1.
*/
void	sighandler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGUSR2)
		g_c_recevied = 1;
	if (sig == SIGUSR1)
		write(1, "Message printed succesfully!\n", 29);
}

/*
 Parameters:
		int argc: Argument count.
		char **argv: Argument vector.
 Return value:
		int: Returns 0 on normal execution.
 Description:
		If exactly three arguments are passed, configures signal handling for
		SIGUSR1 and SIGUSR2 using a custom sigaction structure. Converts the
		length of the third argument to a string and sends it along with the
		first argument as part of a string generation process. Then, sends the
		literal content of the third argument. The program ends normally after
		performing these operations.
*/
int	main(int argc, char **argv)
{
	int					lgth;
	struct sigaction	sa;
	int					i;
	char				*str;

	if (argc == 3)
	{
		sigemptyset(&sa.sa_mask);
		sigaddset(&sa.sa_mask, SIGUSR1);
		sigaddset(&sa.sa_mask, SIGUSR2);
		sa.sa_flags = SA_RESTART | SA_SIGINFO;
		sa.sa_sigaction = sighandler;
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		i = 0;
		while (argv[2][i] != '\0')
			i++;
		lgth = i;
		str = ft_itoa(lgth);
		send_string(ft_atoi(argv[1]), str);
		free(str);
		send_string(ft_atoi(argv[1]), argv[2]);
	}
	return (0);
}
