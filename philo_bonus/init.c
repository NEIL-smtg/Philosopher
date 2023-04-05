/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:08:45 by suchua            #+#    #+#             */
/*   Updated: 2023/04/05 23:00:47 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	destroy_sem(t_info *info)
{
	sem_close(info->print);
	sem_close(info->read);
	sem_close(info->modify);
	sem_close(info->forks);
	sem_close(info->eaten);
	sem_unlink("sem_eaten");
	sem_unlink("sem_print");
	sem_unlink("sem_read");
	sem_unlink("sem_modify");
	sem_unlink("sem_forks");
}

int	init_sem(t_info *info)
{
	destroy_sem(info);
	info->print = sem_open("sem_print", O_CREAT | S_IRWXU, 0644, 1);
	info->read = sem_open("sem_read", O_CREAT | S_IRWXU, 0644, 1);
	info->modify = sem_open("sem_modify", O_CREAT | S_IRWXU, 0644, 1);
	info->forks = sem_open("sem_forks", O_CREAT | S_IRWXU, 0644, info->nphilo);
	if (info->eat_req)
		info->eaten = sem_open("sem_eaten", O_CREAT | S_IRWXU, 0644, 0);
	if (info->eat_req && info->eaten == SEM_FAILED)
		return (-1);
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
		printf("0 1 has taken a fork\n0 1 die");
	if (info->nphilo <= 1)
		return (-1);
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
	int			i;
	t_philo		pl[250];
	pid_t		id;

	i = -1;
	while (++i < info->nphilo)
	{
		pl[i].info = info;
		pl[i].num_eat = 0;
		pl[i].id = i + 1;
		pl[i].t_start = get_time();
		pl[i].t_last_eat = pl[i].t_start;
		id = fork();
		if (id == -1)
			return ;
		if (id == 0)
			routine(&pl[i]);
	}
	if (pl->info->eat_req)
		all_eaten(&pl);
	destroy_sem(info);
	waitpid(-1, NULL, 0);
	kill(0, SIGINT);
}
