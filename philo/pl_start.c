/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:45:16 by suchua            #+#    #+#             */
/*   Updated: 2023/02/13 19:02:05 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_pre_next(t_philo *philo, t_philo **pre, t_philo **next)
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

void	print_status(t_philo *philo, int type)
{
	t_philo	*pre;
	t_philo	*next;

	if (type == SLEEP)
		printf("Philosopher %d is sleeping\n", philo->id);
	if (type == EAT)
		printf("Philosopher %d has taken a fork\n", philo->id);
	if (type == EAT || type == SLEEP)
		return ;
	set_pre_next(philo, &pre, &next);
	if (pre->is_eating || next->is_eating)
		printf("Philosopher %d is thinking\n", philo->id);
	else
		return ;
}

void	*pl_start(void *params)
{
	t_philo	*philo;

	philo = (t_philo *) params;
	// while (1)
	// {
		print_status(philo, THINK);
		pthread_mutex_lock(&philo->right);
		pthread_mutex_lock(philo->left);
		philo->is_eating = 1;
		print_status(philo, EAT);
		usleep(philo->pl_info.t_sleep * 1000);
		pthread_mutex_unlock(&philo->right);
		pthread_mutex_unlock(philo->left);
		philo->is_eating = 0;
		if (philo->pl_info.must_eat != -42)
			philo->pl_info.must_eat--;
		print_status(philo, SLEEP);
	// }
	return (NULL);
}
