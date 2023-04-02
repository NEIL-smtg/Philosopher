/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 20:09:39 by suchua            #+#    #+#             */
/*   Updated: 2023/04/02 08:21:04 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	valid_atoi(char *s)
{
	int		i;
	long	total;
	int		j;

	i = 0;
	j = 0;
	total = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		++j;
		if (j > 10 || total > 2147483647)
			return (0);
		total = total * 10 + s[i++] - '0';
	}
	return (1);
}

int	ft_atoi(char *s)
{
	int		i;
	int		total;

	i = 0;
	total = 0;
	while (s[i] >= '0' && s[i] <= '9')
		total = total * 10 + s[i++] - '0';
	return (total);
}

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

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	remove_delay(int usleep_time)
{
	struct timeval	i;
	struct timeval	j;
	long long		diff;

	gettimeofday(&i, NULL);
	while (1)
	{
		gettimeofday(&j, NULL);
		diff = (j.tv_sec * 1000 + j.tv_usec / 1000)
			- (i.tv_sec * 1000 + i.tv_usec / 1000);
		if (diff >= (long long) usleep_time)
			break ;
		usleep(50);
	}
}
