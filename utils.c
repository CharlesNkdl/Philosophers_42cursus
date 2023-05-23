#include "philosophers.h"

int	checker_args(int argc, char **argv)
{
	int	i;
	int	j;

	j = 0;
	i = 1;
	while (i < argc)
	{
		while (argv[i][j])
		{
			if (argv[i][j] >= '0' && argv[i][j] <= '9')
				j++;
			else
				return (1);
		}
		j = 0;
		i++;
	}
	return (0);
}

void	ft_sleepexc(int	tts)
{
	unsigned long long	time;

	time = 0;
	time = ft_get_time();
	while (ft_get_time() - time < (unsigned long long)tts)
		usleep(50);
}

unsigned long long	ft_get_time(void)
{
	struct timeval	timevalue;
	unsigned long long time;

	time = 0;
	timevalue.tv_sec = 0;
	timevalue.tv_usec = 0;
	gettimeofday(&timevalue, NULL);
	time = timevalue.tv_sec * 1000 + timevalue.tv_usec / 1000;
	return (time);
}

int	ft_atoi(char *str)
{
	int 	i;
	int		sign;
	int		result;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r')
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + str[i] - 48;
		i++;
	}
	return (result * sign);
}
