#include "philo.h"

void	*is_sleeping(t_philo *philo)
{
	printf("philo %d is sleeping\n", philo->philo_number);
	usleep(philo->info->time_to_sleep * 1000);
	return (NULL);
}

void	*do_philosopher_thing(void	*philo)
{
	is_sleeping(philo);
	return (NULL);



}
