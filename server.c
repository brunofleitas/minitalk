/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:39:51 by bfleitas          #+#    #+#             */
/*   Updated: 2024/05/24 04:00:11 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void    handle_binary(int sig)
{
    if (sig == SIGUSR1)
        write (1, "1", 1);
    else if (sig == SIGUSR2)
        write (1, "0", 1);
}

int main()
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGUSR2);

    sa.sa_handler = &handle_binary;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    printf("PID of the server: %d\n", getpid());
    while (1)
    {
        sleep(1); // Espera las señales
    }
}

