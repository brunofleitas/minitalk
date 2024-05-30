/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/28 23:43:51 by bfleitas          #+#    #+#             */
/*   Updated: 2024/05/30 12:59:04 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

/*
 Parameters:
		int nbr: Integer to convert to a string.
 Return value:
		char*: Pointer to the newly allocated string representation of 'nbr'.
 Description:
		Converts an integer 'nbr' to its ASCII string representation. Allocates
		memory for the resulting string,
			including space for the null terminator.
		Handles special cases such as converting 0 to "0".
*/

void	convert_nbr_to_str(long n_tmp, int *len, char **str, int nbr)
{
	while (n_tmp)
	{
		n_tmp /= 10;
		(*len) += 1;
	}
	while (nbr)
	{
		(*str)[--(*len)] = (nbr % 10) + '0';
		nbr /= 10;
	}
}

char	*ft_itoa(int nbr)
{
	static int	len;
	long		n_tmp;
	char		*str;

	len = 0;
	n_tmp = nbr;
	str = (char *)malloc(sizeof(char) * len + 1);
	if (!str)
		return (NULL);
	str[len] = '\0';
	if (nbr == 0)
		str[0] = '0';
	else
		convert_nbr_to_str(n_tmp, &len, &str, nbr);
	return (str);
}
