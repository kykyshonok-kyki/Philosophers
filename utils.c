#include "philo.h"

void	print_full(pthread_mutex_t *print_m)
{
	usleep(10);
	pthread_mutex_lock(print_m);
	printf(END_EAT);
}

void	my_print(t_philo *cur)
{
	long int	time;
	int			state;

	state = cur->state;
	time = get_time(cur->input->start_time);
	pthread_mutex_lock(cur->print_m);
	if (cur->input->isend)
		usleep(500);
	if (state == 1)
		printf("%7ld %3d has taken a fork\n", time, cur->pos + 1);
	else if (state == 2)
		printf("%7ld %3d has taken a fork\n%7ld %3d is eating\n", time,
			cur->pos + 1, time, cur->pos + 1);
	else if (state == 3)
		printf("%7ld %3d is sleeping\n", time, cur->pos + 1);
	else if (state == 0)
		printf("%7ld %3d is thinking\n", time, cur->pos + 1);
	else if (state == -1)
		printf("%7ld %3d died\n", time, cur->pos + 1);
	if (state != -1)
		pthread_mutex_unlock(cur->print_m);
}

long int	get_time(long int start_time)
{
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	return (cur_time.tv_usec / 1000 + cur_time.tv_sec * 1000 - start_time);
}

void	my_sleep(int ttsleep)
{
	long int		time;
	long int		esleep_time;
	struct timeval	cur_time;

	gettimeofday(&cur_time, NULL);
	time = cur_time.tv_usec / 1000 + cur_time.tv_sec * 1000;
	esleep_time = time + ttsleep;
	while (time < esleep_time)
	{
		usleep(100);
		gettimeofday(&cur_time, NULL);
		time = cur_time.tv_usec / 1000 + cur_time.tv_sec * 1000;
	}
}

int	my_atoi(char *str)
{
	int	num;

	num = 0;
	if (*str == 0)
		return (-1);
	while (*str != 0)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		num *= 10;
		num += *str - '0';
		str++;
	}
	return (num);
}
