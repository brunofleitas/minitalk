/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:39:40 by bfleitas          #+#    #+#             */
/*   Updated: 2024/05/28 15:45:31 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static	int g_c_recevied;

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

void	send_string(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		char_to_bits(pid, str[i++]);
	if (str[i] == '\0')
		char_to_bits(pid, str[i++]);
}

char	*ft_itoa(int nbr)
{
	int		len;
	long	n_tmp;
	char	*str;

	len = 0;
	n_tmp = nbr;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nbr == 0)
		str[0] = '0';
	else 
	{
		while (n_tmp)
		{
			n_tmp /= 10;
			len += 1;
		}
		while (nbr)
		{
			str[--len] = (nbr % 10) + '0';
			nbr /= 10;
		}
	}
	return (str);
}

void	sighandler(int sig, siginfo_t *info, void *context)
{
	(void) info;
	(void) context;
	if (sig == SIGUSR2)
		g_c_recevied = 1;
	if (sig == SIGUSR1)
		write(1, "Message printed succesfully!\n", 29);
}

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
