/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bfleitas <bfleitas@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 11:35:24 by bfleitas          #+#    #+#             */
/*   Updated: 2024/03/01 11:17:37 by bfleitas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
  Parameters: 
      str: The string to convert to an integer.
  Return value:
      The integer value parsed from the string.
  Description:
      This function converts a string representation of an 
	  integer to an integer value.
      It skips leading whitespace characters, handles sign characters,
	  and processes numeric characters.
      The resulting integer is returned.
*/
int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	result = 0;
	sign = 1;
	while (nptr[i] != 0 && ((nptr[i] == ' ')
			|| (nptr[i] >= 9 && nptr[i] <= 13)))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] != 0 && (nptr[i] >= '0' && nptr[i] <= '9'))
	{
		result = (nptr[i] - 48) + (result * 10);
		i++;
	}
	return (sign * result);
}
