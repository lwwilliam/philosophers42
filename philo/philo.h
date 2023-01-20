/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:28:55 by lwilliam          #+#    #+#             */
/*   Updated: 2023/01/20 14:32:03 by lwilliam         ###   ########.fr       */
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

typedef struct s_rules	t_rules;

typedef struct s_philo
{
	int				which_philo;
	int				eat;
	int				left_fork;
	int				right_fork;
	long long		last_eat;
	pthread_t		threads;
	t_rules			*rules;
}	t_philo;

typedef struct s_rules
{
	int				num_of_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				n_eat;
	int				dead;
	int				all_eaten;
	long long		start_time;	
	pthread_mutex_t	meal_check;
	pthread_mutex_t	*fork;
	pthread_mutex_t	print;
	t_philo			*philo;
}	t_rules;

int			ft_atoi(const char *str);
int			ft_isdigit(int x);
int			ft_strlen(char *str);
long long	timestamp(void);
void		print_funct(t_rules *rules, char *action, int xphilo);

int			av_check(int ac, char **av, t_rules *rules);
int			threading(t_rules *rules, t_philo *philo);
int			av_assign(int ac, char **av, t_rules *rules);
void		destroy(t_rules *rules, t_philo *philo);

#endif