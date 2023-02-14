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

int	main(int ac, char **av)
{
	int			i;
	t_info		info;

	if (ac < 5 || ac > 6 || init(&info, av, ac) == -1)
	{
		write(2, "Invalid arguments / Wrong arguments !!\n", 39);
		return (0);
	}
	init_time(&info);
	i = -1;
	while (++i < info.pl_info.n_philo)
	{
		pthread_create(&info.philo[i].th, NULL, &pl_start, &info.philo[i]);
	}
	i = -1;
	while (++i < info.pl_info.n_philo)
		pthread_join(info.philo[i].th, NULL);
	// destroy_all(&info);
	return (0);
}
