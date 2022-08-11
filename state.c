#include "philo.h"

long long	convert_to_ms(struct timeval time)
{
	long long ms;

	ms = time.tv_sec * 1000;
	ms += time.tv_usec / 1000;

	return(ms);
}

void	philo_message(t_philo *philo, char *str)
{
	long long		ms;
	struct timeval	now;

	pthread_mutex_lock(&philo->info->action_mutex);
	gettimeofday(&now, NULL);

	ms = convert_to_ms(now) - convert_to_ms(philo->info->creat_time);

	if (!philo->info->end)
		printf("%lld\t%d\t %s\n", ms, philo->philo_number, str);

	pthread_mutex_unlock(&philo->info->action_mutex);
}


void	is_sleeping(t_philo *philo)
{
	// printf("philo %d is sleeping\n", philo->philo_number);
	philo_message(philo, "is sleeping");
	usleep(philo->info->time_to_sleep * 1000);
}

void	eating(t_philo *philo)
{
	long long	ms;

	pthread_mutex_lock(&philo->state_mutex);
	gettimeofday(&philo->last_meal, NULL);
	ms = convert_to_ms(philo->last_meal) - convert_to_ms(philo->info->creat_time);
	pthread_mutex_lock(&philo->info->action_mutex);
	if (!philo->info->end)
		printf("%lld\t%d\t %s\n", ms, philo->philo_number, "is eating");
		// philo_message(philo, "is eating");
	philo->nb_eat += 1;
	if (philo->nb_eat == philo->info->nb_time_each_philo_must_eat)
		philo->info->nb_philo_finish_eat += 1;
	pthread_mutex_unlock(&philo->info->action_mutex);
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right);
	pthread_mutex_unlock(philo->left);
	pthread_mutex_unlock(&philo->state_mutex);
}

void	pick_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->left);
	// printf("philo %d taken a fork\n", philo->philo_number);
	philo_message(philo, "taken a fork");
	if (philo->info->nb_philo == 1)
	{
		usleep(philo->info->time_to_die * 1000);
		exit(0);
	}	
	pthread_mutex_lock(philo->right);
	philo_message(philo, "taken a fork");
	// printf("philo %d taken a fork\n", philo->philo_number);
}

void	thinking(t_philo *philo)
{
	// printf("philo %d is thinking\n", philo->philo_number);
	philo_message(philo, "is_thinking");
}

void	*do_philosopher_thing(void	*philo_void)
{
	t_philo *philo;

	philo = philo_void;

	// philo->info->end = 0;

	if (philo->philo_number % 2 == 0)
		usleep(philo->info->time_to_eat * 1000);

	while (!philo->info->end)
	{
		// printf("before taking a fork\n");
		pick_fork(philo);
		eating(philo);
		is_sleeping(philo);
		thinking(philo);
		printf("end routine\n");
	}
	printf("philo end\n");
	return (NULL);
}
