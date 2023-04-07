/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:13:19 by suchua            #+#    #+#             */
/*   Updated: 2023/04/07 20:35:01 by suchua           ###   ########.fr       */
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
		sem_wait(pl->read);
		if (get_time() - pl->t_last_eat > pl->info->tdie)
		{
			sem_post(pl->read);
			msg(DIE, pl);
			break ;
		}
		sem_post(pl->read);
	}
	waitpid(-1, NULL, 0);
	kill(0, SIGINT);
	return (NULL);
}

void	pl_eat(t_philo *pl)
{
	sem_wait(pl->info->forks);
	msg(TAKEN, pl);
	sem_wait(pl->info->forks);
	msg(TAKEN, pl);
	msg(EAT, pl);
	sem_wait(pl->read);
	pl->t_last_eat = get_time();
	sem_post(pl->read);
	remove_delay(pl->info->teat);
	sem_wait(pl->read);
	if (pl->info->eat_req)
		pl->num_eat++;
	if (pl->info->eat_req && pl->num_eat == pl->info->num_eat)
		sem_post(pl->info->eaten);
	sem_post(pl->read);
	sem_post(pl->info->forks);
	sem_post(pl->info->forks);
}

void	routine(t_philo *pl)
{	
	pl->semread_name = ft_strjoin("sem_read_", ft_itoa(pl->id));
	sem_close(pl->read);
	sem_unlink(pl->semread_name);
	pl->read = sem_open(pl->semread_name, O_CREAT | S_IRWXU, 0644, 1);
	free(pl->semread_name);
	if (pl->id % 2 == 0)
	{
		msg(THINK, pl);
		remove_delay(pl->info->teat);
	}
	pthread_create(&pl->exit_th, NULL, &check_exit, pl);
	pthread_detach(pl->exit_th);
	while (1)
	{
		pl_eat(pl);
		msg(SLEEP, pl);
		remove_delay(pl->info->tsleep);
		msg(THINK, pl);
	}
}
