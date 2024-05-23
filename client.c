/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:39:40 by bfleitas          #+#    #+#             */
/*   Updated: 2024/05/24 00:55:18 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void send_bit(int pid, int bit)
{
    if (bit == 1) 
        kill(pid, SIGUSR1);
    else if (bit == 0)
        kill(pid, SIGUSR2);
}

void    char_to_bits(char c, unsigned char bits[7])
{
    int i;

    i = 0;
    while (i < 8)
    {
        bits[i] = (c >> (7 - i)) & 1;
        i++;
    }
}

void    send_char(int pid, char *message)
{
    char            c;
    unsigned char   bits[7];
    int             i;

    i = 0;
    c = 'a';
    char_to_bits(c, bits);
    while (i < 8)
    {
        printf("%u\n", bits[i]);
        i++;
    }
    i = 0;
    while (i < 8)
    {
        send_bit(pid, bits[i]);
        usleep(500);
        i++;
    }
}

int    main(int argc, char **argv)
{
    if (argc == 3)
    {
        send_char(atoi(argv[1]), argv[2]);
    }
    return (0);
}