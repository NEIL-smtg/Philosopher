/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pl_start.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/12 17:45:16 by suchua            #+#    #+#             */
/*   Updated: 2023/02/20 20:27:59 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_die(t_philo *philo)
{
	t_philo	*tmp;
	int		i;
	int		num_philo;

	if (philo->t_life <= 0)
	{
		philo->is_die = 1;
		printf("%lld %d is die\n", philo->t_last_eat + philo->pl_info.t_life
			- philo->t_start, philo->id);
		return (1);
	}
	tmp = philo;
	i = 0;
	num_philo = philo->pl_info.n_philo;
	while (tmp->id != 1)
		--tmp;
	while (i < num_philo)
	{
		if (tmp[i].is_die)
			return (1);
		++i;
	}
	return (0);
}

int	handle_forks_lock(t_philo *philo)
{
	pthread_mutex_lock(&philo->right);
	pthread_mutex_lock(philo->left);
	if (all_enough_food(philo))
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
	return (1);
}

int	pl_eat(t_philo *philo)
{
	if (get_time() - philo->t_last_eat > philo->pl_info.t_life)
	{
		philo->is_die = 1;
		return (!print_status(philo, DIE));
	}
	if (!handle_forks_lock(philo))
		return (0);
	philo->t_life -= philo->pl_info.t_eat;
	philo->is_eating = 0;
	if (philo->pl_info.must_eat > 0)
		philo->pl_info.must_eat--;
	if (philo->pl_info.must_eat == 0)
		philo->enough_food = 1;
	return (1);
}

void	reset_lifespan(t_philo *philo)
{
	if (philo->t_life != philo->pl_info.t_life)
		philo->t_life = philo->pl_info.t_life;
}

void	*pl_start(void *params)
{
	t_philo		*philo;

	philo = (t_philo *) params;
	while (1)
	{
		pthread_mutex_lock(philo->print);
		if (!print_status(philo, THINK))
			philo->is_eating = 1;
		pthread_mutex_unlock(philo->print);
		if (check_if_die(philo) || all_enough_food(philo))
			break ;
		reset_lifespan(philo);
		if (!pl_eat(philo))
			break ;
		if (check_if_die(philo) || all_enough_food(philo))
			break ;
		print_status(philo, SLEEP);
		remove_delay(philo->pl_info.t_sleep);
		if (check_if_die(philo) || all_enough_food(philo))
			break ;
	}
	return (NULL);
}
