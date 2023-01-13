/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:30:59 by lwilliam          #+#    #+#             */
/*   Updated: 2023/01/13 19:09:44 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_funct(t_rules *rules, char *action, int xphilo)
{
	long long	time;

	pthread_mutex_lock(&(rules->print));
	time = timestamp() - rules->start_time;
	if (!(rules->dead))
		printf("%lld %d %s\n", time, xphilo + 1, action);
	pthread_mutex_unlock(&(rules->print));
}

void	which_fork(t_philo *philo)
{
	if (philo->which_philo == 0)
		philo->left_fork = philo->rules->num_of_philo - 1;
	else
		philo->left_fork = philo->which_philo - 1;
	philo->right_fork = philo->which_philo;
}

void	dead_check(t_rules *rules, t_philo *philo)
{
	int	x;

	while (!(rules->eaten))
	{
		x = 0;
		while (x < rules->num_of_philo && !(rules->dead))
		{
			pthread_mutex_lock(&(rules->meal_check));
			if ((timestamp() - philo[x].last_eat) > rules->t_die)
			{
				print_funct(rules, "Died", x);
				rules->dead = 1;
			}
			pthread_mutex_unlock(&(rules->meal_check));
			usleep(100);
			x++;
		}
		if (rules->dead)
			break ;
		x = 0;
		while (rules->num_of_eat != -1 && x < rules->num_of_philo
			&& philo[x].eat >= rules->num_of_eat)
			x++;
		if (x == rules->num_of_philo)
			rules->eaten = 1;
	}
}

void		smart_sleep(long long time, t_rules *rules)
{
	long long i;

	i = timestamp();
	while (!(rules->dead))
	{
		if ((timestamp() - i) >= time)
			break ;
		usleep(50);
	}
}

void	exit_launcher(t_rules *rules, t_philo *philo)
{
	int	x;

	x = 0;
	while (x < rules->num_of_philo)
		pthread_join(philo[x++].threads, NULL);
	x = 0;
	while (x < rules->num_of_philo)
		pthread_mutex_destroy(&(rules->fork[x++]));
	pthread_mutex_destroy(&(rules->print));
}

void	*funct(void *st)
{
	int			x;
	t_philo		*philo;
	t_rules		*rules;

	x = 0;
	philo = (t_philo *)st;
	rules = philo->rules;
	if (philo->which_philo % 2)
		usleep (15000);
	while (!(rules->dead))
	{
		// which_fork(philo);
		pthread_mutex_lock(&(rules->fork[philo->left_fork]));
		print_funct(rules, "has taken a fork", philo->which_philo);
		pthread_mutex_lock(&(rules->fork[philo->right_fork]));
		print_funct(rules, "has taken a fork", philo->which_philo);
		pthread_mutex_lock(&(rules->meal_check));
		print_funct(rules, "is eating", philo->which_philo);
		philo->last_eat = timestamp();
		pthread_mutex_unlock(&(rules->meal_check));
		// usleep(rules->t_eat * 1000);
		smart_sleep(rules->t_eat, rules);
		(philo->eat)++;
		pthread_mutex_unlock(&(rules->fork[philo->left_fork]));
		pthread_mutex_unlock(&(rules->fork[philo->right_fork]));
		if (rules->eaten)
			break ;
		print_funct(rules, "is sleeping", philo->which_philo);
		// usleep(rules->t_sleep * 1000);
		smart_sleep(rules->t_sleep, rules);
		print_funct(rules, "is thinking", philo->which_philo);
		x++;
	}
	return (NULL);
}

int	threading(t_rules *rules, t_philo *philo)
{
	int	x;

	x = 0;
	rules->start_time = timestamp();
	printf("%d number of thread will be created\n", rules->num_of_philo);
	while (x < rules->num_of_philo)
	{
		printf("\033[0;31mcreating thread %d\033[0m\n", x + 1);
		if (pthread_create(&(philo[x].threads), NULL, funct, &(philo[x])))
			return (1);
		philo[x].last_eat = timestamp();
		printf("\033[0;35mthread %d created\n\033[0m", x + 1);
		x++;
	}
	dead_check(rules, philo);
	exit_launcher(rules, philo);
	return (0);
}
