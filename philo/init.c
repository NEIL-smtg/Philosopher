/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:53:10 by suchua            #+#    #+#             */
/*   Updated: 2023/04/05 22:20:12 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	invalid_input(int ac, char **av)
{
	int	i;
	int	j;

	i = 0;
	while (++i < ac)
	{
		j = -1;
		while (av[i][++j])
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
		if (!valid_atoi(av[i]))
			return (1);
	}
	return (0);
}

int	init(int ac, char **av, t_info *info)
{
	if (ac < 5 || ac > 6 || invalid_input(ac, av))
		return (-1);
	info->eat_req = 0;
	if (ac == 6)
		info->eat_req = 1;
	info->nphilo = ft_atoi(av[1]);
	if (info->nphilo == 1)
		printf("0 1 has taken a fork\n0 1 die");
	if (info->nphilo <= 1)
		return (-1);
	info->tdie = ft_atoi(av[2]);
	info->teat = ft_atoi(av[3]);
	info->tsleep = ft_atoi(av[4]);
	info->die = 0;
	if (info->eat_req)
		info->num_eat = ft_atoi(av[5]);
	if (pthread_mutex_init(&info->modify, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&info->read, NULL) == -1)
		return (-1);
	if (pthread_mutex_init(&info->print, NULL) == -1)
		return (-1);
	return (1);
}

int	init_fork(t_philo pl[][250], int n)
{
	int		i;
	int		right;

	i = -1;
	while (++i < n)
	{
		pl[0][i].id = i + 1;
		if (pthread_mutex_init(&pl[0][i].left, NULL) == -1)
			return (-1);
	}
	i = -1;
	while (++i < n)
	{
		right = (i + 1) % n;
		pl[0][i].right = &pl[0][right].left;
	}
	return (1);
}

void	init_philo(t_info *info)
{
	pthread_t	th[250];
	int			i;
	t_philo		pl[250];

	i = -1;
	if (init_fork(&pl, info->nphilo) == -1)
		return ;
	while (++i < info->nphilo)
	{
		pl[i].info = info;
		pl[i].num_eat = 0;
		pl[i].t_start = get_time();
		pl[i].t_last_eat = pl[i].t_start;
		pl[i].tdie = pl->info->tdie;
		pthread_create(&th[i], NULL, routine, &pl[i]);
	}
	i = -1;
	while (++i < info->nphilo)
		pthread_join(th[i], NULL);
	i = -1;
	while (++i < info->nphilo)
		pthread_mutex_destroy(&pl[i].left);
	pthread_mutex_destroy(&info->modify);
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->read);
}
