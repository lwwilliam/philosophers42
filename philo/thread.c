/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:30:59 by lwilliam          #+#    #+#             */
/*   Updated: 2022/12/29 02:48:10 by lwilliam         ###   ########.fr       */
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

	pthread_mutex_lock(philo->print);
	time = timestamp() - philo->rules->time;
	printf("%lld %d %s\n", time, xphilo, action);
	pthread_mutex_unlock(philo->print);
}

void	which_fork(t_philo *philo)
{
	if (philo->which_philo == 0)
		philo->left_fork = philo->rules->num_of_philo - 1;
	else
		philo->left_fork = philo->which_philo - 1;
	philo->right_fork = philo->which_philo;
}

void	*funct(void *st)
{
	t_philo		*philo;

	philo = (t_philo *)st;
	if (philo->which_philo % 2 == 0)
		usleep (10);
	philo->last_eat = timestamp();
	while (1)
	{
		which_fork(philo);
		pthread_mutex_lock(&(philo->fork[philo->left_fork]));
		print_funct(philo, "has taken a fork", philo->which_philo);
		pthread_mutex_lock(&(philo->fork[philo->right_fork]));
		print_funct(philo, "has taken a fork", philo->which_philo);
		print_funct(philo, "is eating", philo->which_philo);
		philo->eat++;
		if (philo->eat == philo->rules->t_eat)
			philo->rules->t_eat++;
		philo->last_eat = timestamp();
		pthread_mutex_unlock(&(philo->fork[philo->left_fork]));
		pthread_mutex_unlock(&(philo->fork[philo->right_fork]));
		print_funct(philo, "is sleeping", philo->which_philo);
		usleep(philo->rules->t_sleep * 1000);
		print_funct(philo, "is thinking", philo->which_philo);
		
	}
	printf("test\n");
	return (0);
}

int	threading(t_rules *rules, t_philo *philo)
{
	int	x;

	x = 0;
	philo->rules = rules;
	printf("%d number of thread will be created\n", rules->num_of_philo);
	while (x < rules->num_of_philo)
	{
		printf("\033[0;31mcreating thread %d\033[0m\n", x);
		philo->which_philo = x;
		if (pthread_create(&philo->threads[x], NULL, funct, philo))
			return (1);
		printf("\033[0;35mthread %d created\n\033[0m", x);
		x++;
		usleep(100);
	}
	return (0);
}
