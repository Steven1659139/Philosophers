#ifndef PHILO_H
#define PHILO_H

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

typedef struct s_philo
{
	int	philo_number;
	int nb_eat;
	struct s_info	*info;
	pthread_t	thread;
	pthread_mutex_t	state_mutex;
	pthread_mutex_t *left;
	pthread_mutex_t *right;
}					t_philo;

typedef struct s_info
{
	int	nb_philo;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nb_time_each_philo_must_eat;
}					t_info;




#endif