/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 10:30:59 by lwilliam          #+#    #+#             */
/*   Updated: 2023/01/20 14:31:44 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dead_check(t_rules *r, t_philo *p)
{
	int	x;

	while (!(r->all_eaten))
	{
		x = 0;
		while (x < r->num_of_philo && !(r->dead))
		{
			pthread_mutex_lock(&(r->meal_check));
			if ((timestamp() - p[x].last_eat) > r->t_die)
			{
				print_funct(r, "died", x);
				r->dead = 1;
			}
			pthread_mutex_unlock(&(r->meal_check));
			usleep(100);
			x++;
		}
		if (r->dead)
			break ;
		x = 0;
		while (r->n_eat != -1 && x < r->num_of_philo && p[x].eat >= r->n_eat)
			x++;
		if (x == r->num_of_philo)
			r->all_eaten = 1;
	}
}

int	eating(t_philo *philo)
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
	else
		return (1);
	pthread_mutex_lock(&(rules->meal_check));
	print_funct(rules, "is eating", philo->which_philo);
	philo->last_eat = timestamp();
	pthread_mutex_unlock(&(rules->meal_check));
	usleep(rules->t_eat * 1000);
	(philo->eat)++;
	pthread_mutex_unlock(&(rules->fork[philo->left_fork]));
	pthread_mutex_unlock(&(rules->fork[philo->right_fork]));
	return (0);
}

void	start(t_rules *rules, t_philo *philo)
{
	if (!(philo->which_philo % 2))
	{
		print_funct(rules, "is thinking", philo->which_philo);
		usleep(1000);
	}
}

void	*funct(void *st)
{
	int			x;
	t_philo		*philo;
	t_rules		*rules;

	x = 0;
	philo = (t_philo *)st;
	rules = philo->rules;
	start(rules, philo);
	while (!(rules->dead))
	{
		if (eating(philo) == 0)
		{
			if (rules->all_eaten)
				break ;
			print_funct(rules, "is sleeping", philo->which_philo);
			usleep(rules->t_sleep * 1000);
			print_funct(rules, "is thinking", philo->which_philo);
		}
		if (rules->all_eaten)
			break ;
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
