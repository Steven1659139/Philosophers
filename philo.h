#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>

typedef struct s_philo
{
	int	philo_number;
	int nb_eat;
	pthread_t	thread;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
	struct s_info	*info;
	struct timeval last_meal;
}					t_philo;

typedef struct s_info
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_time_each_philo_must_eat;
	t_philo		*philos;
	pthread_mutex_t	*forks;
	struct timeval creat_time;
}					t_info;



int	ft_isdigit(int c);
int	is_pos_digit(char **argv);
void	*is_sleeping(t_philo *philo);
void	*do_philosopher_thing(void	*philo);


#endif