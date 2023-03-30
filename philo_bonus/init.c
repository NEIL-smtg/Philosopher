/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:08:45 by suchua            #+#    #+#             */
/*   Updated: 2023/03/30 21:14:43 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

void	destroy_sem(t_info *info)
{
	sem_close(info->print);
	sem_close(info->read);
	sem_close(info->modify);
	sem_close(info->forks);
	sem_unlink("sem_print");
	sem_unlink("sem_read");
	sem_unlink("sem_modify");
	sem_unlink("sem_forks");
}

int	init_sem(t_info *info)
{
	info->print = sem_open("sem_print", O_CREAT, 0644, 1);
	info->read = sem_open("sem_read", O_CREAT, 0644, 1);
	info->modify = sem_open("sem_modify", O_CREAT, 0644, 1);
	info->forks = sem_open("sem_forks", O_CREAT, 0644, info->nphilo);
	if (info->print == SEM_FAILED || info->read == SEM_FAILED
		|| info->modify == SEM_FAILED || info->forks == SEM_FAILED)
		return (-1);
	return (1);
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
	{
		printf("0 1 has taken a fork\n");
		printf("0 1 die\n");
		return (-1);
	}
	info->tdie = ft_atoi(av[2]);
	info->teat = ft_atoi(av[3]);
	info->tsleep = ft_atoi(av[4]);
	info->die = 0;
	if (info->eat_req)
		info->num_eat = ft_atoi(av[5]);
	return (init_sem(info));
}

void	init_philo(t_info *info)
{
	pthread_t	th[200];
	int			i;
	t_philo		pl[200];
	pid_t		id;

	i = -1;
	while (++i < info->nphilo)
	{
		pl[i].info = info;
		pl[i].num_eat = 0;
		pl[i].id = i + 1;
		pl[i].tdie = pl->info->tdie;
		pl[i].t_start = get_time();
		id = fork();
		if (id == 0)
			pthread_create(&th[i], NULL, routine, &pl[i]);
	}
	i = -1;
	while (++i < info->nphilo)
	{
		pthread_join(th[i], NULL);
		waitpid(0, &info->pl_status, 0);
	}
	destroy_sem(info);
}
