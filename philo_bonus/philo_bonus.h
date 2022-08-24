/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: slavoie <marvin@42quebec.com>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 12:31:39 by slavoie           #+#    #+#             */
/*   Updated: 2022/08/22 12:31:40 by slavoie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <string.h>
# include <semaphore.h>

typedef struct s_philo
{
	int				philo_number;
	int				nb_eat;
	pid_t			pid;
	sem_t			*state_sem;
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
	sem_t			*end;
	sem_t			*nb_philo_finish_eat;
	t_philo			*philos;
	sem_t			*forks;
	sem_t			*action_sem;
	struct timeval	creat_time;
}					t_info;

int			ft_isdigit(int c);
int			is_pos_digit(char **argv);
void		yo_its_wrong(char *str, t_info *info);
long long	convert_to_ms(struct timeval time);
void		morphee(long long time_to_wait);
long long	ft_atoll(const char *str);
char		*ft_strjoin(char const *s1, char const *s2);
char	*ft_itoa(int n);
size_t	ft_strlen(const char *str);
void	*ft_calloc(size_t count, size_t size);

void		is_sleeping(t_philo *philo);
void		do_philosopher_thing(void	*philo);
void		philo_message(t_philo *philo, char *str);

void		set_info(t_info *info, char **argv);
void		init_philo(t_info *info);
void		corrupt_the_youth(t_info *info);
void		*charon(void *void_philo);
void		*out_of_food(void *void_info);
void	drink_cigue(t_info *info);


#endif
