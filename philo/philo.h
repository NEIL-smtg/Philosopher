/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 21:30:44 by suchua            #+#    #+#             */
/*   Updated: 2023/03/31 20:18:05 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

# define TAKEN 1
# define EAT 2
# define SLEEP 3
# define DIE 4
# define THINK 5

typedef struct s_info
{
	int				nphilo;
	int				tdie;
	int				teat;
	int				tsleep;
	int				num_eat;
	int				eat_req;
	int				die;
	pthread_mutex_t	modify;
	pthread_mutex_t	read;
	pthread_mutex_t	print;
}	t_info;

typedef struct s_philo
{
	t_info			*info;
	int				num_eat;
	int				id;
	int				tdie;
	long long		t_start;
	long long		t_last_eat;
	pthread_mutex_t	left;
	pthread_mutex_t	*right;
}	t_philo;

//init
int			init(int ac, char **av, t_info *info);
void		init_philo(t_info *info);

//routine
void		*routine(void *param);

//routine utils
void		msg(int type, t_philo *pl);
int			all_eaten(t_philo *pl);
int			someone_die(t_philo *pl);
int			not_enough_time(t_philo *pl, int time);
int			out_of_time(t_philo *pl);

//utils
int			valid_atoi(char *s);
int			ft_atoi(char *s);
long long	get_time(void);
void		remove_delay(int usleep_time);

#endif