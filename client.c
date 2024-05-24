/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:39:40 by bfleitas          #+#    #+#             */
/*   Updated: 2024/05/25 01:30:39 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
/*
void	send_bit(int pid, int bit)
{
	if (bit == 1)
		kill(pid, SIGUSR1);
	else if (bit == 0)
		kill(pid, SIGUSR2);
}*/

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

void	send_char(int pid, char message)
{
	char_to_bits(pid, message);
}

void	send_string(int pid, char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		send_char(pid, str[i++]);
	if (str[i] == '\0')
		send_char(pid, str[i++]);
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
	if (nbr == -2147483648)
		return ("-2147483648");
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[len] = '\0';
	if (nbr == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (nbr < 0)
	{
		len += 1;
		nbr *= -1;
		str[0] = '-';
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

/*
int	main(int argc, char **argv)
{
	int lgth;

	if (argc == 3)
	{
		lgth = ft_strlen(argv[2]); 
		send_string(atoi(argv[1]), ft_itoa(lgth));
		send_string(atoi(argv[1]), argv[2]);
	}
	return (0);
}*/

void	message_displayed(int sig)
{
	if (sig == SIGUSR1)
	{
		write(1, "Message recived and printed", 27);
		exit(1);
	}
}

int main(int argc, char **argv)
{
    struct sigaction sa;
	int lgth;

	if (argc == 3)
	{
    	//sigemptyset(&sa.sa_mask);
    	//sigaddset(&sa.sa_mask, SIGUSR1);
    	//sigaddset(&sa.sa_mask, SIGUSR2);

    	//sa.sa_handler = &message_displayed;
    	//sigaction(SIGUSR1, &sa, NULL);
    	//sigaction(SIGUSR2, &sa, NULL);

    	lgth = ft_strlen(argv[2]); 
		send_string(atoi(argv[1]), ft_itoa(lgth));
		//send_string(atoi(argv[1]), ft_itoa(getpid()));
		send_string(atoi(argv[1]), argv[2]);
    	//while (1)
    	//    usleep(100);
	}
	return (0);
}