/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 22:07:02 by suchua            #+#    #+#             */
/*   Updated: 2023/04/06 17:53:44 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

long long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((long long)(tv.tv_sec * 1000 + tv.tv_usec / 1000));
}

void	destroy_all(t_philo **pl, t_info *info)
{
	int		i;
	t_philo	*p;

	i = -1;
	p = *pl;
	while (++i < info->nphilo)
		pthread_mutex_destroy(&p[i].left);
	pthread_mutex_destroy(&info->print);
	pthread_mutex_destroy(&info->read);
	free(p);
}
