/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/24 14:50:02 by bfleitas          #+#    #+#             */
/*   Updated: 2024/05/25 01:29:53 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


//libraries server:
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

//libraries client:
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_global
{
	int				first_string;
	//int				pid_recived;
	int 			i;
	char			*lgth;
}					t_global;