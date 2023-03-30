/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:52:02 by suchua            #+#    #+#             */
/*   Updated: 2023/03/30 21:15:45 by suchua           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/time.h>

# define EAT 1
# define SLEEP 2
# define THINK 3
# define DIE 4
# define TAKEN 5

typedef struct s_info
{
	int				nphilo;
	int				tdie;
	int				teat;
	int				tsleep;
	int				num_eat;
	int				eat_req;
	int				die;
	int				pl_status;
	sem_t			*print;
	sem_t			*read;
	sem_t			*modify;
	sem_t			*forks;
}	t_info;

typedef struct s_philo
{
	t_info			*info;
	int				num_eat;
	int				id;
	int				tdie;
	long long		t_start;
	long long		t_last_eat;
}	t_philo;

void		init_philo(t_info *info);
int			init(int ac, char **av, t_info *info);

//utils
int			valid_atoi(char *s);
int			ft_atoi(char *s);
long long	get_time(void);
void		remove_delay(int usleep_time);

//routine
//wait - 1 , post + 1
void		*routine(void *params);

//print pl status
void		msg(int type, t_philo *pl);

#endif