/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 21:06:54 by suchua            #+#    #+#             */
/*   Updated: 2023/04/02 21:36:32 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	msg(int type, t_philo *pl)
{
	sem_wait(pl->info->print);
	if (type == EAT)
		printf("%lld %d is eating\n", get_time() - pl->t_start, pl->id);
	else if (type == SLEEP)
		printf("%lld %d is sleeping\n", get_time() - pl->t_start, pl->id);
	else if (type == THINK)
		printf("%lld %d is thinking\n", get_time() - pl->t_start, pl->id);
	else if (type == TAKEN)
		printf("%lld %d has taken a fork\n", get_time() - pl->t_start, pl->id);
	else
		printf("%d %d died\n", pl->info->tdie, pl->id);
	sem_post(pl->info->print);
}

void	all_eaten(void *params)
{
	t_philo	*pl;
	int		i;

	pl = (t_philo *) params;
	i = -1;
	if (fork() != 0)
		return ;
	while (++i < pl->info->nphilo)
		sem_wait(pl[i].eaten);
	kill(0, SIGINT);
	return ;
}
