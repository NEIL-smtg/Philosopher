/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:59:29 by suchua            #+#    #+#             */
/*   Updated: 2023/04/06 19:26:01 by suchua           ###   ########.fr       */
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
		printf("%lld %d is sleeping\n",
			get_time() - pl->t_start - pl->info->tsleep, pl->id);
	else if (type == DIE)
		printf("%d %d died\n", pl->info->tdie, pl->id);
	else
		printf("%lld %d is thinking\n", get_time() - pl->t_start, pl->id);
	pthread_mutex_unlock(&pl->info->print);
}

void	pl_eat_utils(t_philo *pl)
{
	pthread_mutex_lock(&pl->info->read);
	pl->t_last_eat = get_time();
	pl->num_eat++;
	if (pl->info->eat_req && pl->num_eat == pl->info->num_eat)
		pl->info->all_eaten++;
	pthread_mutex_unlock(&pl->info->read);
}

void	pl_eat(t_philo *pl)
{
	pthread_mutex_lock(&pl->left);
	if (someone_die(pl) || all_eaten(pl) || out_of_time(pl))
	{
		pthread_mutex_unlock(&pl->left);
		return ;
	}
	msg(TAKEN, pl);
	pthread_mutex_lock(pl->right);
	if (someone_die(pl) || all_eaten(pl) || out_of_time(pl))
	{
		pthread_mutex_unlock(&pl->left);
		pthread_mutex_unlock(pl->right);
		return ;
	}
	msg(TAKEN, pl);
	msg(EAT, pl);
	pl_eat_utils(pl);
	remove_delay(pl->info->teat, pl);
	pthread_mutex_unlock(pl->right);
	pthread_mutex_unlock(&pl->left);
}

void	*routine(void *param)
{
	t_philo	*pl;

	pl = (t_philo *) param;
	if (pl->id % 2 == 0)
	{
		msg(THINK, pl);
		remove_delay(pl->info->teat, pl);
	}
	while (1)
	{
		if (out_of_time(pl))
			return (NULL);
		pl_eat(pl);
		if (all_eaten(pl) || someone_die(pl) || out_of_time(pl))
			return (NULL);
		remove_delay(pl->info->tsleep, pl);
		if (all_eaten(pl) || someone_die(pl) || out_of_time(pl))
			return (NULL);
		msg(SLEEP, pl);
		msg(THINK, pl);
	}
	return (NULL);
}
