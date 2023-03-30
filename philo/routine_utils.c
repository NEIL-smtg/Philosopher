/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 03:18:12 by suchua            #+#    #+#             */
/*   Updated: 2023/03/30 18:46:06 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msg(int type, t_philo *pl)
{
	pthread_mutex_lock(&pl->info->print);
	if (type == TAKEN)
		printf("%lld %d has taken a fork\n", get_time() - pl->t_start, pl->id);
	else if (type == EAT)
		printf("%lld %d is eating\n", get_time() - pl->t_start, pl->id);
	else if (type == SLEEP)
		printf("%lld %d is sleeping\n", get_time() - pl->t_start, pl->id);
	else if (type == DIE)
		printf("%d %d died\n", pl->info->tdie, pl->id);
	else
		printf("%lld %d is thinking\n", get_time() - pl->t_start, pl->id);
	pthread_mutex_unlock(&pl->info->print);
}

int	all_eaten(t_philo *pl)
{
	int	i;

	pthread_mutex_lock(&pl->info->read);
	if (!pl->info->eat_req)
	{
		pthread_mutex_unlock(&pl->info->read);
		return (0);
	}
	i = -1;
	while (pl->id != 1)
		pl--;
	while (++i < pl->info->nphilo)
	{
		if (pl->num_eat < pl->info->num_eat)
		{
			pthread_mutex_unlock(&pl->info->read);
			return (0);
		}
	}
	pthread_mutex_unlock(&pl->info->read);
	return (1);
}

int	someone_die(t_philo *pl)
{
	pthread_mutex_lock(&pl->info->read);
	if (pl->info->die > 0)
	{
		pthread_mutex_unlock(&pl->info->read);
		return (1);
	}
	pthread_mutex_unlock(&pl->info->read);
	return (0);
}

int	not_enough_time(t_philo *pl, int time)
{
	pthread_mutex_lock(&pl->info->read);
	if (pl->tdie - time < 0)
	{
		pthread_mutex_lock(&pl->info->modify);
		pl->info->die++;
		if (pl->info->die == 1)
		{
			remove_delay(100);
			msg(DIE, pl);
		}
		pthread_mutex_unlock(&pl->info->modify);
		pthread_mutex_unlock(&pl->info->read);
		return (1);
	}
	pthread_mutex_unlock(&pl->info->read);
	return (0);
}
