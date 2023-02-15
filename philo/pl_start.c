/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:45:16 by suchua            #+#    #+#             */
/*   Updated: 2023/02/15 20:30:11 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_die(t_philo *philo)
{
	t_philo	*tmp;
	int		i;

	if (philo->t_life <= 0)
	{
		print_status(philo, DIE);
		return (1);
	}
	tmp = philo;
	i = 0;
	while (tmp[i].id != 1)
		--i;
	while (i <= philo->pl_info.n_philo)
	{
		if (tmp[i].is_die)
			return (1);
		++i;
	}
	return (0);
}

int	pl_eat(t_philo *philo)
{
	if (get_time() - philo->t_last_eat > philo->pl_info.t_life)
	{
		philo->is_die = 1;
		print_status(philo, DIE);
		return (0);
	}
	pthread_mutex_lock(&philo->right);
	pthread_mutex_lock(philo->left);
	if (philo->pl_info.must_eat >= 0 && check_must_eat(philo))
	{
		pthread_mutex_unlock(&philo->right);
		pthread_mutex_unlock(philo->left);
		return (0);
	}
	philo->t_last_eat = get_time();
	print_status(philo, EAT);
	remove_delay(philo->pl_info.t_eat);
	pthread_mutex_unlock(&philo->right);
	pthread_mutex_unlock(philo->left);
	philo->is_eating = 0;
	if (philo->pl_info.must_eat > 0)
		philo->pl_info.must_eat--;
	if (philo->pl_info.must_eat == 0)
	{
		philo->enough_food = 1;
		// printf("cme : %d\n", check_must_eat(philo));
		if (check_must_eat(philo))
			return (0);
	}
	return (1);
}

void	reset_lifespan(t_philo *philo)
{
	philo->t_life = philo->pl_info.t_life;
}

void	*pl_start(void *params)
{
	t_philo		*philo;

	philo = (t_philo *) params;
	while (1)
	{
		pthread_mutex_lock(philo->print);
		print_status(philo, THINK);
		pthread_mutex_unlock(philo->print);
		if (check_if_die(philo))
			break ;
		reset_lifespan(philo);
		if (!pl_eat(philo))
			break ;
		print_status(philo, SLEEP);
		remove_delay(philo->pl_info.t_sleep);
		if (check_if_die(philo))
			break ;
	}
	return (NULL);
}
