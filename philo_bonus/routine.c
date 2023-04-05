/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:13:19 by suchua            #+#    #+#             */
/*   Updated: 2023/04/05 23:15:11 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*check_exit(void *params)
{
	t_philo	*pl;

	pl = (t_philo *) params;
	while (1)
	{
		remove_delay(pl->info->tdie / 2);
		sem_wait(pl->info->read);
		if (get_time() - pl->t_last_eat > pl->info->tdie)
		{
			sem_post(pl->info->read);
			msg(DIE, pl);
			break ;
		}
		sem_post(pl->info->read);
	}
	waitpid(-1, NULL, 0);
	kill(0, SIGINT);
	return (NULL);
}

void	take_forks(t_philo *pl)
{
	sem_wait(pl->info->forks);
	msg(TAKEN, pl);
	sem_wait(pl->info->forks);
	msg(TAKEN, pl);
	msg(EAT, pl);
	remove_delay(pl->info->teat);
	sem_post(pl->info->forks);
	sem_post(pl->info->forks);
}

void	pl_eat(t_philo *pl)
{
	sem_wait(pl->info->modify);
	pl->t_last_eat = get_time();
	sem_wait(pl->info->read);
	if (pl->info->eat_req)
		pl->num_eat++;
 	if (pl->info->eat_req && pl->num_eat == pl->info->num_eat)
		sem_post(pl->info->eaten);
	sem_post(pl->info->read);
	sem_post(pl->info->modify);
}

void	routine(t_philo *pl)
{
	if (pl->id > pl->info->nphilo / 2)
	{
		msg(THINK, pl);
		remove_delay(pl->info->teat);
	}
	pthread_create(&pl->exit_th, NULL, &check_exit, pl);
	pthread_detach(pl->exit_th);
	while (1)
	{
		take_forks(pl);
		pl_eat(pl);
		msg(SLEEP, pl);
		remove_delay(pl->info->tsleep);
		msg(THINK, pl);
	}
}
