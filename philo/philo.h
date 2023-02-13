/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua < suchua@student.42kl.edu.my>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 22:10:29 by suchua            #+#    #+#             */
/*   Updated: 2023/01/20 22:10:29 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# define EAT 1
# define SLEEP 2
# define THINK 3

typedef struct s_pl_info
{
	int			n_philo;
	int			t_life;
	int			t_eat;
	int			t_sleep;
	int			must_eat;
}	t_pl_info;

typedef struct s_philo
{
	int				id;
	int				is_eating;
	pthread_t		th;
	pthread_mutex_t	*left;
	pthread_mutex_t	right;
	pthread_mutex_t	*print;
	t_pl_info		pl_info;
}	t_philo;

typedef struct s_info
{
	t_pl_info		pl_info;
	t_philo			*philo;
	pthread_mutex_t	mutex_print;
}	t_info;

//process
void	*pl_start(void *params);

//init
int		init(t_info *info, char **av, int ac);

//utils
int		valid_atoi(char *str);
long	pl_atoi(char *str);
void	destroy_all(t_info *info);

#endif