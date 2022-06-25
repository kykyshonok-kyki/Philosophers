#include "philo.h"

void	take_lfork(t_philo *cur)
{
	pthread_mutex_lock(cur->lfork);
	if (cur->state != -1)
	{
		cur->state = 1;
		my_print(cur);
	}
}

void	eat(t_philo *cur)
{
	pthread_mutex_lock(cur->rfork);
	if (cur->state != -1)
	{
		cur->state = 2;
		cur->lasteat = get_time(cur->input->start_time);
		cur->eatcnt++;
		my_print(cur);
	}
	my_sleep(cur->input->eat);
	pthread_mutex_unlock(cur->lfork);
	pthread_mutex_unlock(cur->rfork);
}

void	philo_sleep(t_philo *cur)
{
	if (cur->state != -1)
	{
		cur->state = 3;
		my_print(cur);
	}
	my_sleep(cur->input->sleep);
}

void	*philo_thread(void *params)
{
	t_philo	*cur;

	cur = params;
	while (1)
	{
		take_lfork(cur);
		eat(cur);
		philo_sleep(cur);
		if (cur->state != -1)
		{
			cur->state = 0;
			my_print(cur);
		}
	}
	return (NULL);
}
