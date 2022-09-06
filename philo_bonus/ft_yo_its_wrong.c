/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_yo_its_wrong.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/03 15:46:31 by slavoie           #+#    #+#             */
/*   Updated: 2022/09/06 14:56:30 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(const char *str)
{
	size_t	index;

	if (!str)
		return (0);
	index = 0;
	while (str[index])
		index++;
	return (index);
}

void	ft_putstr_fd(char *s, int fd)
{
	if (!s)
		return ;
	write(fd, s, ft_strlen(s));
}

void	yo_its_wrong(char *str, t_info *info)
{
	ft_putstr_fd(str, 2);
	if (info->philos)
		free(info->philos);
	free(info);
	exit(0);
}
