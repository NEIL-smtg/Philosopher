/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:13:19 by suchua            #+#    #+#             */
/*   Updated: 2023/03/30 21:17:09 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*routine(void *params)
{
	t_philo	*pl;

	pl = (t_philo *) params;
	if (pl->id % 2 == 0)
	{
		msg(THINK, pl);
		usleep(100);
	}
	exit(EXIT_SUCCESS);
}
