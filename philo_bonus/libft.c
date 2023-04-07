/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 17:28:23 by suchua            #+#    #+#             */
/*   Updated: 2023/04/02 08:42:38 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	get_malloc_size(int n)
{
	int	size;

	size = 0;
	if (n == 0)
		return (2);
	if (n == -2147483648)
	{
		n = 214748364;
		size += 2;
	}
	else if (n < 0)
	{
		size++;
		n = -n;
	}
	while (n > 0)
	{
		n /= 10;
		size++;
	}
	return (size + 1);
}

static void	save(char *str, int n)
{
	int	i;

	i = get_malloc_size(n) - 1;
	str[i] = '\0';
	i--;
	if (n == 0)
		str[0] = '0';
	if (n == -2147483648)
	{
		str[0] = '-';
		str[i] = '8';
		n = 214748364;
		i--;
	}
	else if (n < 0)
	{
		str[0] = '-';
		n = -n;
	}
	while (n > 0)
	{
		str[i] = n % 10 + '0';
		n /= 10;
		i--;
	}
}

char	*ft_itoa(int n)
{
	char	*tmp;

	tmp = (char *) malloc (get_malloc_size(n) * sizeof(char));
	if (!tmp)
		return (NULL);
	save(tmp, n);
	return (tmp);
}
