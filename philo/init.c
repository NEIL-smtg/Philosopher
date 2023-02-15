/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/08 13:16:03 by suchua            #+#    #+#             */
/*   Updated: 2023/02/15 19:48:31 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_time(t_info *info)
{
	int			i;
	long long	start_time;

	i = -1;
	start_time = get_time();
	while (++i < info->pl_info.n_philo)
	{
		info->philo[i].t_start = start_time;
		info->philo[i].t_last_eat = start_time;
	}
}

int	init_thread_list(t_info *info)
{
	int	i;

	info->philo = malloc(sizeof(t_philo) * info->pl_info.n_philo);
	i = -1;
	while (++i < info->pl_info.n_philo)
	{
		info->philo[i].id = i + 1;
		info->philo[i].is_eating = 0;
		info->philo[i].is_die = 0;
		info->philo[i].enough_food = 0;
		info->philo[i].pl_info = info->pl_info;
		info->philo[i].t_life = info->pl_info.t_life;
		info->philo[i].print = &info->mutex_print;
		pthread_mutex_init(&info->philo[i].right, NULL);
	}
	i = -1;
	while (++i < info->pl_info.n_philo)
	{
		if (i == 0)
			info->philo[info->pl_info.n_philo - 1].left = &info->philo[i].right;
		else
			info->philo[i - 1].left = &info->philo[i].right;
	}
	return (1);
}

int	init(t_info *info, char **av, int ac)
{
	if (!valid_atoi(av[1]) || !valid_atoi(av[2]) || !valid_atoi(av[3])
		|| !valid_atoi(av[4]))
		return (-1);
	if (ac == 6 && !valid_atoi(av[5]))
		return (-1);
	info->pl_info.n_philo = pl_atoi(av[1]);
	info->pl_info.t_life = pl_atoi(av[2]);
	info->pl_info.t_eat = pl_atoi(av[3]);
	info->pl_info.t_sleep = pl_atoi(av[4]);
	if (ac == 6)
		info->pl_info.must_eat = pl_atoi(av[5]);
	else
		info->pl_info.must_eat = -42;
	if (info->pl_info.n_philo > 200 || info->pl_info.t_life < 60
		|| info->pl_info.t_eat < 60 || info->pl_info.t_sleep < 60)
		return (-1);
	pthread_mutex_init(&info->mutex_print, NULL);
	return (init_thread_list(info));
}
