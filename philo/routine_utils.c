/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 03:18:12 by suchua            #+#    #+#             */
/*   Updated: 2023/04/06 19:23:55 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	all_eaten(t_philo *pl)
{
	pthread_mutex_lock(&pl->info->read);
	if (!pl->info->eat_req)
	{
		pthread_mutex_unlock(&pl->info->read);
		return (0);
	}
	if (pl->info->eat_req && pl->info->all_eaten == pl->info->nphilo)
	{
		pthread_mutex_unlock(&pl->info->read);
		return (1);
	}
	pthread_mutex_unlock(&pl->info->read);
	return (0);
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

int	out_of_time(t_philo *pl)
{
	pthread_mutex_lock(&pl->info->read);
	if (get_time() - pl->t_last_eat > pl->info->tdie)
	{
		pl->info->die++;
		pthread_mutex_unlock(&pl->info->read);
		if (pl->info->die == 1)
			msg(DIE, pl);
		return (1);
	}
	pthread_mutex_unlock(&pl->info->read);
	return (0);
}

void	remove_delay(int usleep_time, t_philo *pl)
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
		usleep(500);
		if (someone_die(pl))
			return ;
	}
}
