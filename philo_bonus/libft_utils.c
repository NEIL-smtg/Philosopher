/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/02 08:41:38 by suchua            #+#    #+#             */
/*   Updated: 2023/04/02 08:43:15 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		++i;
	return (i);
}

void	concat(char *str, char const *a)
{
	size_t	n;

	n = ft_strlen(str);
	while (*a)
		str[n++] = *(a++);
	str[n] = 0;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	total_size;
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	total_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *) malloc (total_size * sizeof(char));
	if (!str)
		return (NULL);
	*str = 0;
	concat(str, s1);
	concat(str, s2);
	return (str);
}
