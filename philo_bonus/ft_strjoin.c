/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42quebec.>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 12:00:58 by slavoie           #+#    #+#             */
/*   Updated: 2021/06/01 14:58:14 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t dst_size)
{
	size_t	index;

	index = 0;
	if (!(dst || src))
		return (0);
	while (src[index] && (index + 1) < dst_size)
	{	
		dst[index] = src[index];
		index++;
	}
	if (dst_size != 0)
		dst[index] = 0;
	while (src[index])
		index++;
	return (index);
}


size_t	ft_strlcat(char *dst, const char *src, size_t dst_size)
{
	size_t	index;

	index = 0;
	while (*dst && index < dst_size)
	{
		index++;
		dst++;
	}
	while (*src && (index + 1) < dst_size)
	{
		*dst++ = *src++;
		index++;
	}
	if (index < dst_size)
		*dst = 0;
	while (*src++)
		index++;
	return (index);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*rtn;
	size_t	len;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	rtn = malloc(len);
	if (!rtn)
		return (NULL);
	ft_strlcpy(rtn, s1, len);
	ft_strlcat(rtn, s2, len);
	return (rtn);
}
