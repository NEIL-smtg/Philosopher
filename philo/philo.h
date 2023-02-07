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
# define THINK 2
# define SLEEP 3

typedef struct s_arg
{
	int		philo;
	int		life;
	int		eat;
	int		sleep;
	int		must_eat;
	int		forks;
	int		id;
}	t_arg;

//utils
int		valid_atoi(char *str);
long	pl_atoi(char *str);


#endif