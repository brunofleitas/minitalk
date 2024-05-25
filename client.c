/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:39:40 by bfleitas          #+#    #+#             */
/*   Updated: 2024/05/25 03:09:49 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	char_to_bits(int pid, char c)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if ((c >> i) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		i++;
		usleep(50);
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

int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char	*ft_itoa(int nbr)
{
	int		len;
	long	n_tmp;
	char	*str;

	len = 0;
	n_tmp = nbr;
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[len] = '\0';
	if (nbr == 0)
	{
		str[0] = '0';
		return (str);
	}
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
	return (str);
}

void	sighandler(int sig)
{
	(void)sig;
	write(1, "Message printed succesfully!\n", 29);
}

int	main(int argc, char **argv)
{
	int	lgth;
	struct sigaction sa;

	if (argc == 3)
	{
		sigemptyset(&sa.sa_mask);
		sigaddset(&sa.sa_mask, SIGUSR1);

		sa.sa_handler = &sighandler;
		sigaction(SIGUSR1, &sa, NULL);

		lgth = ft_strlen(argv[2]);
		send_string(atoi(argv[1]), ft_itoa(lgth));
		send_string(atoi(argv[1]), argv[2]);
	}
	return (0);
}
