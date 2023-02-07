/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:10:33 by suchua            #+#    #+#             */
/*   Updated: 2023/01/20 22:10:33 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	g_mutex[200];

void	init2(t_arg *prev, t_arg *now, int id)
{
	now->life = prev->life;
	now->eat = prev->eat;
	now->forks = prev->forks;
	now->must_eat = prev->must_eat;
	now->philo = prev->philo;
	now->sleep = prev->sleep;
	now->id = id + 1;
}

int	init(t_arg *arg, char **av)
{
	int	i;

	if (!valid_atoi(av[1]) || !valid_atoi(av[2]) || !valid_atoi(av[3])
		|| !valid_atoi(av[4]) || !valid_atoi(av[5]))
		return (-1);
	arg[0].philo = pl_atoi(av[1]);
	arg[0].forks = arg[0].philo;
	arg[0].life = pl_atoi(av[2]);
	arg[0].eat = pl_atoi(av[3]);
	arg[0].sleep = pl_atoi(av[4]);
	arg[0].must_eat = pl_atoi(av[5]);
	arg[0].id = 1;
	if (arg[0].philo > 200 || arg[0].life < 60 || arg[0].eat < 60
		|| arg[0].sleep < 60)
		return (-1);
	return (1);
}

void	*pl_start(void *data)
{
	t_arg	*arg;

	arg = (t_arg *) data;
	while (1)
	{
		pthread_mutex_lock(&g_mutex[arg->id - 1]);
		pthread_mutex_lock(&g_mutex[arg->id % arg->philo]);
		printf("%d : Philosopher %d is eating\n", 0, arg->id);
		usleep(arg->eat * 1000);
		pthread_mutex_unlock(&g_mutex[arg->id - 1]);
		pthread_mutex_unlock(&g_mutex[arg->id % arg->philo]);
		arg->must_eat--;
		arg->life -= arg->eat;
		if (arg->must_eat == 0 || arg->life == 0)
			break ;
	}
}

int	main(int ac, char **av)
{
	t_arg		arg[200];
	pthread_t	th[200];
	int			i;

	if (ac != 6 || init(&arg[0], av) == -1)
	{
		write(2, "Invalid arguments / Wrong arguments !!\n", 39);
		return (0);
	}
	i = 0;
	while (++i < arg[0].philo)
	{
		init2(&arg[i - 1], &arg[i], i);
		pthread_mutex_init(&g_mutex[i], NULL);
	}
	i = -1;
	while (++i < arg[0].philo)
		pthread_create(&th[i], NULL, pl_start, &arg[i]);
	i = -1;
	while (++i < arg[0].philo)
		pthread_join(th[i], NULL);
	i = -1;
	while (++i < arg->philo)
		pthread_mutex_destroy(&g_mutex[i]);
	return (0);
}
