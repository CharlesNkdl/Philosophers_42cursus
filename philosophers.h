#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_info {
	int	id;
	int	np;
	int	ttd;
	int	tte;
	int	tts;
	int	pme;
	int	eatcount;
	int	*deadcheck;
	unsigned long long	lastmiam;
	unsigned long long	start;
	pthread_t	thread;
	pthread_mutex_t	*dead;
	pthread_mutex_t *left_mutex;
	pthread_mutex_t *right_mutex;
}		t_info;

int	checker_args(int argc, char **argv);
void	ft_sleepexc(int	tts);
unsigned long long	ft_get_time(void);
int	ft_atoi(char *str);
void	ft_free(t_info *philo, pthread_mutex_t *forks, pthread_mutex_t *death);
int	ft_dead(t_info *philo, int i, unsigned long long time);
void	deadcheck(t_info *philo);
int	printer(t_info *philo, char *status);
int	pme(t_info *philo, int *j, int *result);
int	eat(t_info *philo);
int	ft_sleep(t_info *philo);
void	*startth(void *args);


#endif
