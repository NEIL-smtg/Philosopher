/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:45:16 by suchua            #+#    #+#             */
/*   Updated: 2023/02/14 22:20:39 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	remove_delay(int sleep_time)
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
		if (diff >= (long long) sleep_time)
			break ;
		usleep(50);
	}
}

void	print_status(t_philo *philo, int type)
{
	t_philo		*pre;
	t_philo		*next;
	long long	diff;

	diff = get_time() - philo->start_time;
	if (type == SLEEP)
	{
		philo->t_life -= philo->pl_info.t_sleep;
		printf("%lld : Philosopher %d is sleeping\n", diff, philo->id);
		remove_delay(philo->pl_info.t_sleep);
	}
	if (type == EAT)
		printf("%lld : Philosopher %d has taken a fork\n", diff, philo->id);
	if (type == DIE)
		printf("%lld : Philosopher %d die\n", diff, philo->id);
	if (type == EAT || type == SLEEP || type == DIE)
		return ;
	get_pre_next(philo, &pre, &next);
	if (pre->is_eating || next->is_eating)
	{
		philo->t_life -= philo->pl_info.t_eat;
		printf("%lld : Philosopher %d is thinking\n", diff, philo->id);
		remove_delay(philo->pl_info.t_eat);
	}
	else
		return ;
}

int	check_must_eat(t_philo *philo)
{
	t_philo	*tmp;
	int		i;

	tmp = philo;
	while (philo->id != 1)
		tmp--;
	i = -1;
	while (++i < philo->pl_info.n_philo)
	{
		if (!tmp->enough_food)
			return (0);
		tmp++;
	}
	return (1);
}

void	*pl_start(void *params)
{
	t_philo		*philo;

	philo = (t_philo *) params;
	while (1)
	{
		print_status(philo, THINK);
		if (philo->t_life <= 0)
		{
			print_status(philo, DIE);
			break ;
		}
		philo->t_life = philo->pl_info.t_life;
		pthread_mutex_lock(&philo->right);
		pthread_mutex_lock(philo->left);
		philo->is_eating = 1;
		print_status(philo, EAT);
		remove_delay(philo->pl_info.t_sleep);
		pthread_mutex_unlock(&philo->right);
		pthread_mutex_unlock(philo->left);
		philo->is_eating = 0;
		if (philo->pl_info.must_eat > 0)
			philo->pl_info.must_eat--;
		if (philo->pl_info.must_eat == 0)
		{
			philo->enough_food = 1;
			if (check_must_eat(philo))
				break ;
		}
		print_status(philo, SLEEP);
		if (philo->t_life <= 0)
		{
			print_status(philo, DIE);
			break ;
		}
	}
	return (NULL);
}
