/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 14:24:00 by suchua            #+#    #+#             */
/*   Updated: 2023/02/20 20:27:47 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	remove_delay(int usleep_time)
{
	struct timeval	i;
	struct timeval	j;
	long long		diff;

	gettimeofday(&i, NULL);
	while (1)
	{
		gettimeofday(&j, NULL);
		diff = (j.tv_sec * 1000 + j.tv_usec / 1000)
			- (i.tv_sec * 1000 + i.tv_usec / 1000);
		if (diff >= (long long) usleep_time)
			break ;
		usleep(50);
	}
}

int	all_enough_food(t_philo *philo)
{
	t_philo	*tmp;
	int		i;
	int		num_philo;

	tmp = philo;
	num_philo = philo->pl_info.n_philo;
	tmp -= tmp->id - 1;
	i = -1;
	while (++i < num_philo)
	{
		if (!tmp[i].enough_food)
			return (0);
	}
	return (1);
}

void	get_pre_next(t_philo *philo, t_philo **pre, t_philo **next)
{
	int		num_philo;

	num_philo = philo->pl_info.n_philo;
	if (philo->id == 1)
		*pre = philo + (num_philo - 1);
	else
		*pre = philo - 1;
	if (philo->id == num_philo)
		*next = philo - (num_philo - 1);
	else
		*next = philo + 1;
}

int	print_status(t_philo *philo, int type)
{
	t_philo		*pre;
	t_philo		*next;
	long long	diff;

	diff = get_time() - philo->t_start;
	if (type == SLEEP)
		printf("%lld %d is sleeping\n", diff, philo->id);
	if (type == EAT)
		printf("%lld %d is eating\n", diff, philo->id);
	if (type == DIE)
		printf("%lld %d die\n", diff, philo->id);
	if (type == EAT || type == SLEEP || type == DIE)
		return (1);
	get_pre_next(philo, &pre, &next);
	if (pre->is_eating || next->is_eating)
	{
		printf("%lld %d is thinking\n", diff, philo->id);
		return (1);
	}
	philo->t_life -= philo->pl_info.t_eat;
	return (0);
}
