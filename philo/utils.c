/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:09:47 by slavoie           #+#    #+#             */
/*   Updated: 2022/09/06 14:56:19 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	int	rtn;

	rtn = (c <= '9' && c >= '0');
	return (rtn);
}

int	is_pos_digit(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (argv[i])
	{
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]))
				return (0);
			j++;
		}
		j = 0;
		i++;
	}
	return (1);
}

int	ft_atoi(const char *str)
{
	long long	n;
	int			negation;

	n = 0;
	negation = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	while (*str == '+' || *str == '-')
	{
		if (n >= 1)
			return (0);
		if (*str == '-')
			negation++;
		n++;
		str++;
	}
	n = 0;
	if (*str == '+' && negation > 0)
		return (n);
	while (*str >= '0' && *str <= '9')
		n = n * 10 + *str++ - '0';
	if (negation)
		n *= -1;
	return (n);
}
