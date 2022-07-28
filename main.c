#include "philo.h"

void	set_info(t_info *info, char **argv)
{
	info->nb_philo = atoi(argv[1]);
	info->time_to_die = atoi(argv[2]);
	info->time_to_eat = atoi(argv[3]);
	info->time_to_sleep = atoi(argv[4]);
	if (argv[5])
		info->nb_time_each_philo_must_eat = atoi(argv[5]);

}



int main(int argc, char **argv)
{
	t_info	*info;

	info = malloc(sizeof(t_info));

	if (argc != 5 && argc != 6)
		{
			printf("Mauvaise nombre d'Argument");

			exit(0);
		}
	set_info(info, argv);
	// printf("nb_philo = %d\ntime_to_die = %d\ninfo->time_to_eat = %d\ninfo->time_to_sleep = %d\ninfo->nb_time_each_philo_must_eat = %d\n", info->nb_philo, info->time_to_die, info->time_to_eat, info->time_to_sleep, info->nb_time_each_philo_must_eat);

	// pthread_create()





}