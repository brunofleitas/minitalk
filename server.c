/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:39:51 by bfleitas          #+#    #+#             */
/*   Updated: 2024/05/25 03:11:27 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

t_global    *global_var = NULL;

void    initialize_global_var()
{
    global_var = malloc(sizeof(t_global));
    if (global_var == NULL)
    {
        printf("MAlloc error");
        exit(1);
    }    
    global_var->first_string = 0;
    global_var->i = 0;
    global_var->lgth = malloc(11 * sizeof(char));
    if (global_var->lgth == NULL)
    {
        printf("MAlloc error");
        exit(1);
    }
}

void    handle_binary(int sig, siginfo_t *info, void *context)
{
    static int	c;
	static int	bit;
    static char *str;

    (void)context;
	if (sig == SIGUSR1)
		c |= (1 << bit);
	if (++bit == 8)
	{
        if (global_var->first_string == 0 && c)
        {
            global_var->lgth[global_var->i] = c;
            global_var->i++;
            bit = 0;
		    c = 0;
        }
        else if (global_var->first_string == 0 && !c)
        {
            global_var->lgth[global_var->i] = c;
            global_var->first_string = 1;
            str = malloc((atoi(global_var->lgth) + 1) * sizeof(char));
            free(global_var->lgth);
            global_var->i = 0;
            bit = 0;
		    c = 0;
        }
        else if (global_var->first_string == 1 && c)
        {
            str[global_var->i] = c;
            global_var->i++;
            bit = 0;
		    c = 0;
        }
        else if (global_var->first_string == 1 && !c)
        {
            printf("%s\n", str);
            c = 0;
            bit = 0;
            kill(info->si_pid, SIGUSR1);
            free(str);
            initialize_global_var();
        }
	}
}

int main()
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGUSR2);

    sa.sa_sigaction = handle_binary;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    initialize_global_var();
    printf("PID of the server: %d\n", getpid());
    while (1)
        usleep(100);
}
