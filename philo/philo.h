/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <slavoie@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 11:10:01 by slavoie           #+#    #+#             */
/*   Updated: 2022/09/06 14:56:07 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				philo_number;
	int				nb_eat;
	pthread_t		thread;
	pthread_mutex_t	die_or_eat_mutex;
	pthread_mutex_t	*left;
	pthread_mutex_t	*right;
	pthread_mutex_t	cue;
	struct s_info	*info;
	struct timeval	last_meal;
}					t_philo;

typedef struct s_info
{
	int				nb_philo;
	long long		time_to_die;
	long long		time_to_eat;
	long long		time_to_sleep;
	int				nb_time_each_philo_must_eat;
	bool			end;
	int				nb_philo_finish_eat;
	t_philo			*philos;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message_mutex;
	struct timeval	creat_time;
}					t_info;

int			ft_isdigit(int c);
int			is_pos_digit(char **argv);
int			yo_its_wrong(char *str, t_info *info);
long long	convert_to_ms(struct timeval time);
void		morphee(long long time_to_wait);
int			ft_atoi(const char *str);

void		is_sleeping(t_philo *philo);
void		*do_philosopher_thing(void	*philo);
void		philo_message(t_philo *philo, char *str);

int			set_info(t_info *info, char **argv);
void		init_philo(t_info *info);
void		close_philo(t_info *info);
void		corrupt_the_youth(t_info *info);
void		*charon(void *void_philo);
void		*out_of_food(void *void_info);

#endif
