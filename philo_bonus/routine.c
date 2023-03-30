/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:13:19 by suchua            #+#    #+#             */
/*   Updated: 2023/03/31 04:43:29 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pl_eat(t_philo *pl)
{	
	sem_wait(pl->info->forks);
	msg(TAKEN, pl);
	sem_wait(pl->info->forks);
	msg(TAKEN, pl);
	msg(EAT, pl);
	sem_post(pl->info->forks);
	sem_post(pl->info->forks);
	remove_delay(pl->info->teat);
	sem_wait(pl->info->modify);
	pl->t_last_eat = get_time();
	if (pl->info->eat_req)
		pl->num_eat++;
	sem_post(pl->info->modify);
}

void	pl_sleep(t_philo *pl)
{
	msg(SLEEP, pl);
	remove_delay(pl->info->tsleep);
}

int	all_eaten(t_philo *pl)
{
	int		i;

	sem_wait(pl->info->read);
	if (!pl->info->eat_req)
	{
		sem_post(pl->info->read);
		return (0);
	}
	while (pl->id != 1)
		pl--;
	i = -1;
	while (++i < pl->info->nphilo)
	{
		if (pl->num_eat < pl->info->num_eat)
		{
			sem_post(pl->info->read);
			return (0);
		}
	}
	sem_post(pl->info->read);
	return (1);
}

void	*routine(void *params)
{
	t_philo	*pl;

	pl = (t_philo *) params;
	if (pl->id % 2 == 0)
	{
		msg(THINK, pl);
		usleep(100);
	}
	while (1)
	{
		pl_eat(pl);
		if (all_eaten(pl))
			exit(EXIT_FAILURE);
		pl_sleep(pl);
		msg(THINK, pl);
	}
	return (NULL);
}
