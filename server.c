/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 14:39:51 by bfleitas          #+#    #+#             */
/*   Updated: 2024/05/25 01:31:20 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"
/*
void    read_str_lgth(int sig, int lgth_read, int actual_bit, char * second_str)
{
    static  char actual_char;
    static  nbr = 0;

    if  (actual_char != '\0')
    {
        //transfrom char to nbr and multiply x 10;    
    }
    else
    {
        second_str = malloc(nbr + 1 *(sizeof (char)));
        lgth_read = 1;
    }
}*/
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
    //global_var->pid_recived = 0;
    global_var->i = 0;
    global_var->lgth = malloc(11 * sizeof(char));
    if (global_var->lgth == NULL)
    {
        printf("MAlloc error");
        exit(1);
    }
}

void    handle_binary(int sig)
{
    static int	c;
	static int	bit;
    static char *str;
    //static int  pid;

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
            global_var->i = 0;
            bit = 0;
		    c = 0;
        }/*
        if (global_var->pid_recived == 0 && c)
        {
            global_var->lgth[global_var->i] = c;
            global_var->i++;
            bit = 0;
		    c = 0;
        }
        else if (global_var->pid_recived == 0 && !c)
        {
            global_var->lgth[global_var->i] = c;
            global_var->pid_recived = 1;
            pid = atoi(global_var->lgth);
            free(global_var->lgth);
            global_var->i = 0;
            bit = 0;
		    c = 0;
        }*/
        else if (global_var->first_string == 1 && c)
        {
            str[global_var->i] = c;
            global_var->i++;
            bit = 0;
		    c = 0;
        }
        else if (global_var->first_string == 1 && !c)
        {
            printf("\n%s\n", str);
            c = 0;
            bit = 0;
            //kill(pid, SIGUSR1)
            free(str);
            initialize_global_var();
        }
	}
}
/*
    static  int     lgth_read = 0;
    static  int     actual_bit = 0;
    static  char    *second_str = NULL;
    static  unsigned char    c[7];
    static  int     i = 0;

    if (i < 8)
    {
        printf("%i", sig);
        c[i] |= 1 << (7 - i);
        i++;
        write (1, &c, 1);
    }
    else 
    {
        write (1, &c, 1);
        if (!lgth_read)
            read_str_lgth(sig, &lgth_read, &c, &second_str);
        else 
            printf("all the length has been readed");
    }
void    handle_binary(int sig)
{
    if (sig == SIGUSR1)
        write (1, "1", 1);
    else if (sig == SIGUSR2)
        write (1, "0", 1);
}
*/

int main()
{
    struct sigaction sa;

    sigemptyset(&sa.sa_mask);
    sigaddset(&sa.sa_mask, SIGUSR1);
    sigaddset(&sa.sa_mask, SIGUSR2);

    sa.sa_handler = &handle_binary;
    sigaction(SIGUSR1, &sa, NULL);
    sigaction(SIGUSR2, &sa, NULL);

    initialize_global_var();
    printf("PID of the server: %d\n", getpid());
    while (1)
        usleep(100);
}

