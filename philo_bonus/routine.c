/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:13:19 by suchua            #+#    #+#             */
/*   Updated: 2023/03/31 05:40:33 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	pl_eat(t_philo *pl)
{
	sem_wait(pl->info->read);
	if (pl->tdie - pl->info->teat < 0)
	{
		sem_wait(pl->info->modify);
		pl->info->die++;
		sem_post(pl->info->modify);
	}
	sem_post(pl->info->read);
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
	if (pl->num_eat >= pl->info->num_eat)
		sem_post(pl->sem_eaten);
	pl->tdie = pl->info->tdie - pl->info->teat;
	sem_post(pl->info->modify);
}

void	pl_sleep(t_philo *pl)
{
	msg(SLEEP, pl);
	remove_delay(pl->info->tsleep);
	sem_wait(pl->info->modify);
	pl->tdie -= pl->info->tsleep;
	sem_post(pl->info->modify);
}

void	*check_death(void *params)
{
	t_philo	*pl;

	pl = (t_philo *) params;
	while (1)
	{
		remove_delay(pl->info->tdie / 2);
		if (pl->info->die)
		{
			if (pl->info->die == 1)
			{
				usleep(100);
				msg(DIE, pl);
			}
			break ;
		}
	}
	waitpid(-1, NULL, 0);
	kill(0, SIGINT);
	return (NULL);
}

void	routine(t_philo *pl)
{
	if (pl->id % 2 == 0)
	{
		msg(THINK, pl);
		usleep(100);
	}
	pthread_create(&pl->th, NULL, &check_death, pl);
	while (1)
	{
		pl_eat(pl);
		pl_sleep(pl);
		msg(THINK, pl);
	}
	pthread_join(pl->th, NULL);
}
