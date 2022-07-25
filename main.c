#include "philo.h"

void	set_info(t_philo *info, char **argv)
{
	info->nb_philo = atoi(argv[1]);
	info->time_to_die = atoi(argv[2]);
	info->time_to_eat = atoi(argv[3]);
	info->time_to_sleep = atoi(argv[4]);
	if (argv[6])
		info->nb_time_each_philo_must_eat = atoi(argv[5]);

}



int main(int argc, char **argv)
{
	t_philo	*info;

	info = malloc(sizeof(t_philo));

	if (argc != 5 && argc != 6)
		printf("Mauvaise nombre d'Argument");
	set_info(info, argv);
}