/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 00:47:11 by suchua            #+#    #+#             */
/*   Updated: 2023/02/14 17:14:34 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	valid_atoi(char *str)
{
	int		i;
	int		j;
	long	sum;

	i = 0;
	sum = 0;
	j = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		++i;
	if (str[i] == '-')
		return (0);
	if (str[i] == '+')
		++i;
	while (str[i] >= '0' && str[i] <= '9')
	{
		++j;
		if (j > 10)
			break ;
		sum = sum * 10 + str[i] - '0';
		++i;
	}
	if (j > 10 || sum > 2147483647)
		return (0);
	return (1);
}

long	pl_atoi(char *str)
{
	int	i;
	int	sum;

	i = 0;
	sum = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		++i;
	if (str[i] == '+')
		++i;
	while (str[i] >= '0' && str[i] <= '9')
		sum = sum * 10 + str[i++] - '0';
	return (sum);
}

void	destroy_all(t_info *info)
{
	int		i;

	i = -1;
	while (++i < info->pl_info.n_philo)
	{
		pthread_mutex_destroy(&info->philo->right);
		free(&info->philo[i]);
	}
}
