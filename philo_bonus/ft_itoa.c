/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 13:57:11 by slavoie           #+#    #+#             */
/*   Updated: 2022/09/06 14:56:25 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

char	*ft_strdup(const char *s1)
{
	char	*rtn;
	int		len;
	int		index;

	index = 0;
	len = ft_strlen(s1);
	rtn = ft_calloc(len + 1, sizeof(char));
	if (!rtn)
		return (0);
	while (len--)
		rtn[index++] = *s1++;
	rtn[index] = 0;
	return (rtn);
}

static char	*ft_reverse_string(char *str, int index, int neg)
{
	char	*rtn;
	int		j;

	j = 0;
	if (neg)
		rtn = (char *)ft_calloc((index + 2), sizeof(char));
	else
		rtn = (char *)ft_calloc((index + 1), sizeof(char));
	if (rtn == 0)
		return (NULL);
	if (neg)
		rtn[j++] = '-';
	while (index > 0)
	{
		rtn[j] = str[index - 1];
		j++;
		index--;
	}
	rtn[j] = 0;
	return (rtn);
}

static char	*ft_make_str(int n, int neg)
{
	char	*rtn;
	int		unit;
	char	str[11];
	int		index;

	index = 0;
	while (n > 9)
	{
		unit = n % 10;
		str[index++] = unit + '0';
		n /= 10;
	}
	str[index++] = n + '0';
	rtn = ft_reverse_string(str, index, neg);
	return (rtn);
}

char	*ft_itoa(int n)
{
	char	*rtn;
	int		neg;

	neg = 0;
	if (n == -2147483648)
	{
		rtn = ft_strdup("-2147483648");
		return (rtn);
	}
	if (n < 0)
	{
		neg++;
		n *= -1;
	}
	rtn = ft_make_str(n, neg);
	return (rtn);
}
