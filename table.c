#include "philosophers.h"

void	*startth(void *args)
{
	t_info *philo;


	philo = (t_info *)args;
	while (1)
	{
		if (eat(philo))
			break ;
		if (ft_sleep(philo))
			break ;
		if (printer(philo, "is thinking"))
			break ;
	}
	return (NULL);
}

int	eat(t_info *philo)
{
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->right_mutex);
	else
		pthread_mutex_lock(philo->left_mutex);
	printer(philo, "has taken a fork");
	if (philo->np == 1)
	{
		pthread_mutex_unlock(philo->right_mutex);
		ft_sleepexc(philo->ttd);
		return (1);
	}
	if (philo->id % 2 == 0)
		pthread_mutex_lock(philo->left_mutex);
	else
		pthread_mutex_lock(philo->right_mutex);
	printer(philo, "has taken a fork");
	printer(philo, "is eating");
	return (0);
}

int	ft_sleep(t_info *philo)
{
	pthread_mutex_lock(philo->dead);
	philo->eatcount++;
	philo->lastmiam = ft_get_time();
	pthread_mutex_unlock(philo->dead);
	ft_sleepexc(philo->tte);
	printer(philo, "is sleeping");
	pthread_mutex_unlock(philo->right_mutex);
	pthread_mutex_unlock(philo->left_mutex);
	ft_sleepexc(philo->tts);
	return (0);
}
