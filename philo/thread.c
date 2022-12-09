/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:30:59 by lwilliam          #+#    #+#             */
/*   Updated: 2022/12/09 21:28:01 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	dead_check(t_rules *rules, long long last_eat, long long time)
{
	last_eat = time - timestamp();
	if (last_eat >= rules->t_die)
		return (1);
	return (0);
}

long long	timestamp(void)
{	
	struct timeval	time;

	gettimeofday(&time, NULL);
	return (time.tv_usec / 1000 + time.tv_sec * 1000);
}

void	print_funct(t_philo *philo, char *action, int xphilo)
{
	long long	time;

	time = timestamp() - philo->start_time;
	printf("%lld %d %s\n", time, xphilo, action);
}

// void	eating(t_philo *philo, char y_n)
// {
// 	int	is_eating;
// 	int	is_thinking;

// 	is_eating = 0;
// 	is_thinking = 0;
// 	if (y_n == 'y')
// 	{
// 		print_funct(philo, "is eating", philo->which_philo);
// 		is_eating = 1;
// 	}
// 	if (is_eating == 0)
// 	{
// 		print_funct(philo, "is thinking", philo->which_philo);
// 		is_thinking = 1;
// 	}
// 	if (is_thinking == 1)
// 	{
// 		print_funct(philo, "is sleeping", philo->which_philo);
// 	}
// }

void	*funct(void *st)
{
	t_rules		*rules;
	long long	time;
	long long	last_eat;

	rules = (t_rules *)st;
	time = timestamp();
	while (dead_check(rules, last_eat, time) != 1)
	{
		printf("test\n");
		time = timestamp();
		if (rules->philo->which_philo == 0)
			rules->philo->left_fork = rules->num_of_philo - 1;
		else
			rules->philo->left_fork = rules->philo->which_philo - 1;
		rules->philo->right_fork = rules->philo->which_philo;
		// pthread_mutex_lock(&(philo->ptr->fork[philo->left_fork]));
		// print_funct(philo, "has taken a fork", philo->which_philo);
		// pthread_mutex_lock(&(philo->ptr->fork[philo->right_fork]));
		// print_funct(philo, "has taken a fork", philo->which_philo);
		// eating(philo, 'y');
		// usleep(1000 * philo->t_eat);
		// pthread_mutex_unlock(&(philo->ptr->fork[philo->left_fork]));
		// pthread_mutex_unlock(&(philo->ptr->fork[philo->right_fork]));
		// usleep(1000);
	}
	return (0);
}

int	threading(t_rules *rules, t_philo *philo)
{
	int	x;

	x = 0;
	printf("%d number of thread will be created\n", rules->num_of_philo);
	while (x < rules->num_of_philo)
	{
		printf("\033[0;33mcreating mutex %d\n\033[0m", x);
		if (pthread_mutex_init(&(rules->fork[x]), NULL) != 0)
		{
			printf("mutex init failed\n");
			return (1);
		}
		printf("\033[0;31mcreating thread %d\033[0m\n", x);
		philo->which_philo = x;
		// if (pthread_create(&rules->threads, NULL, funct, (void *)rules))
		// 	return (1);
		printf("\033[0;35mthread %d created\n\033[0m", x);
		x++;
		usleep(100);
	}
	printf("done\n");
	return (0);
}
