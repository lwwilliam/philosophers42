/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:28:55 by lwilliam          #+#    #+#             */
/*   Updated: 2022/12/31 15:44:49 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo	t_philo;

typedef struct s_rules
{
	int				num_of_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				num_of_eat;
	long long		time;
	t_philo			*philo;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	pthread_mutex_t	meal_check;
}	t_rules;

typedef struct s_philo
{
	int				which_philo;
	int				left_fork;
	int				right_fork;
	int				dead;
	int				eat;
	int				all_ate;
	long long		last_eat;
	t_rules			*rules;
	pthread_t		threads;
}	t_philo;

int			ft_atoi(const char *str);
int			ft_isdigit(int x);
int			ft_strlen(char *str);

int			av_check(int ac, char **av, t_rules *rules);
int			threading(t_rules *rules, t_philo *philo);
long long	timestamp(void);
int			initfunct(int ac, char **av, t_rules *rules);

#endif