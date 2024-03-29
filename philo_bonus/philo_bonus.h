/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suchua <suchua@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/30 18:52:02 by suchua            #+#    #+#             */
/*   Updated: 2023/04/07 19:11:53 by suchua           ###   ########.fr       */
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
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>

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
	sem_t			*modify;
	sem_t			*eaten;
	sem_t			*forks;
}	t_info;

typedef struct s_philo
{
	t_info			*info;
	int				num_eat;
	int				id;
	long long		t_start;
	long long		t_last_eat;
	pthread_t		exit_th;
	sem_t			*read;
	char			*semread_name;
}	t_philo;

void		init_philo(t_info *info);
int			init(int ac, char **av, t_info *info);

//utils
int			invalid_input(int ac, char **av);
int			valid_atoi(char *s);
int			ft_atoi(char *s);
long long	get_time(void);
void		remove_delay(int usleep_time);

//libft
char		*ft_strjoin(char *s1, char *s2);
char		*ft_itoa(int n);
size_t		ft_strlen(char const *s);

//routine
void		routine(t_philo *pl);
int			not_enough_time(t_philo *pl, int time);
void		all_eaten(void *params);

//print pl status
void		msg(int type, t_philo *pl);

#endif