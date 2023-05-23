#include "philosophers.h"

void	joiner(t_info *philo, char **argv)
{
	int	i;

	(void)argv;
	i = 0;
	while (i < philo->np)
	{
		pthread_create(&philo[i].thread, NULL, &startth, &philo[i]);
		i++;
		usleep(100);
	}
	while (*(philo->deadcheck) != 1)
		deadcheck(philo);
	i = 0;
	while (i < philo->np)
	{
    	pthread_join(philo[i].thread, NULL);
		i++;
	}
}

void	ft_free(t_info *philo, pthread_mutex_t *forks, pthread_mutex_t *death)
{
	int	i;

	i = 0;
	while (i < philo->np)
	{
		pthread_mutex_destroy(philo[i].left_mutex);
		pthread_mutex_destroy(philo[i].right_mutex);
		i++;
	}
	pthread_mutex_destroy(philo->dead);
	free(philo->deadcheck);
	free(forks);
	free(death);
	free(philo);
}

void	deadcheck(t_info *philo)
{
	unsigned long long time;
	int	i;
	int	j;
	int	result;

	i = 0;
	j = 0;
	result = 0;
	time = 0;
	while (i < philo->np)
	{
		pthread_mutex_lock(philo->dead);
		time = ft_get_time() - philo[i].lastmiam;
		if (ft_dead(philo, i, time) || pme(philo, &j, &result))
		{
			pthread_mutex_unlock(philo->dead);
			break ;
		}
		i++;
		pthread_mutex_unlock(philo->dead);
	}
}
