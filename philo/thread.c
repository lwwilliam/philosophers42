/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:30:59 by lwilliam          #+#    #+#             */
/*   Updated: 2023/01/19 17:16:04 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dead_check(t_rules *rules, t_philo *philo)
{
	int	x;

	while (!(rules->all_eaten))
	{
		x = 0;
		while (x < rules->num_of_philo && !(rules->dead))
		{
			pthread_mutex_lock(&(rules->meal_check));
			if ((timestamp() - philo[x].last_eat) > rules->t_die)
			{
				print_funct(rules, "died", x);
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
			rules->all_eaten = 1;
	}
}

void	destroy(t_rules *rules, t_philo *philo)
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

void	eating(t_philo *philo)
{
	t_rules	*rules;

	rules = philo->rules;
	if (rules->num_of_philo >= 2)
	{
		pthread_mutex_lock(&(rules->fork[philo->left_fork]));
		print_funct(rules, "has taken a fork", philo->which_philo);
		pthread_mutex_lock(&(rules->fork[philo->right_fork]));
		print_funct(rules, "has taken a fork", philo->which_philo);
	}
	pthread_mutex_lock(&(rules->meal_check));
	print_funct(rules, "is eating", philo->which_philo);
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&(rules->meal_check));
	usleep(rules->t_eat * 1000);
	(philo->eat)++;
	pthread_mutex_unlock(&(rules->fork[philo->left_fork]));
	pthread_mutex_unlock(&(rules->fork[philo->right_fork]));
}

void	*funct(void *st)
{
	int			x;
	t_philo		*philo;
	t_rules		*rules;

	x = 0;
	philo = (t_philo *)st;
	rules = philo->rules;
	if (!(philo->which_philo % 2))
	{
		print_funct(rules, "is thinking", philo->which_philo);
		usleep (15000);
	}
	while (!(rules->dead))
	{
		eating(philo);
		if (rules->all_eaten)
			break ;
		print_funct(rules, "is sleeping", philo->which_philo);
		usleep(rules->t_sleep * 1000);
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
	while (x < rules->num_of_philo)
	{
		if (pthread_create(&(philo[x].threads), NULL, funct, &(philo[x])))
			return (1);
		philo[x].last_eat = timestamp();
		x++;
	}
	dead_check(rules, philo);
	destroy(rules, philo);
	return (0);
}
