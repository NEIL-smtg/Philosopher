/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:59:29 by suchua            #+#    #+#             */
/*   Updated: 2023/03/31 05:29:24 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pl_eat_utils(t_philo *pl)
{
	pthread_mutex_lock(&pl->info->modify);
	pl->t_last_eat = get_time();
	pl->tdie = pl->info->tdie - pl->info->teat;
	pl->num_eat++;
	pthread_mutex_unlock(&pl->info->modify);
}

void	pl_eat(t_philo *pl)
{
	if (not_enough_time(pl, pl->info->teat))
		return ;
	pthread_mutex_lock(&pl->left);
	if (someone_die(pl))
	{
		pthread_mutex_unlock(&pl->left);
		return ;
	}
	msg(TAKEN, pl);
	pthread_mutex_lock(pl->right);
	if (someone_die(pl))
	{
		pthread_mutex_unlock(&pl->left);
		pthread_mutex_unlock(pl->right);
		return ;
	}
	msg(TAKEN, pl);
	msg(EAT, pl);
	pl_eat_utils(pl);
	remove_delay(pl->info->teat);
	pthread_mutex_unlock(pl->right);
	pthread_mutex_unlock(&pl->left);
}

int	pl_sleep(t_philo *pl)
{
	if (not_enough_time(pl, pl->info->tsleep))
		return (0);
	msg(SLEEP, pl);
	remove_delay(pl->info->tsleep);
	if (someone_die(pl))
		return (0);
	pthread_mutex_lock(&pl->info->modify);
	pl->tdie -= pl->info->tsleep;
	pthread_mutex_unlock(&pl->info->modify);
	return (1);
}

void	*routine(void *param)
{
	t_philo	*pl;

	pl = (t_philo *) param;
	if (pl->id % 2 == 0)
	{
		msg(THINK, pl);
		usleep(100);
	}
	while (1)
	{
		pl_eat(pl);
		if (all_eaten(pl))
			return (NULL);
		if (someone_die(pl))
			return (NULL);
		if (!pl_sleep(pl))
			return (NULL);
		msg(THINK, pl);
	}
	return (NULL);
}
