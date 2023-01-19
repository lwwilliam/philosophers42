/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:24:29 by lwilliam          #+#    #+#             */
/*   Updated: 2023/01/19 22:41:15 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"

int	av_check(int ac, char **av, t_rules *rules)
{
	int	count;
	int	len;

	count = 1;
	if (ac != 5 && ac != 6)
	{
		printf("Error! <num_of_philo time_die time_eat \
time_sleep (num_eat)>\n");
		return (1);
	}
	while (count < ac)
	{
		len = 0;
		while (len < ft_strlen(av[count]))
		{
			if (!ft_isdigit(av[count][len]))
				return (1);
			len++;
		}
		count++;
	}
	if (av_assign(ac, av, rules) != 0)
		return (1);
	return (0);
}

int	av_assign(int ac, char **av, t_rules *rules)
{
	rules->num_of_philo = ft_atoi(av[1]);
	rules->t_die = ft_atoi(av[2]);
	rules->t_eat = ft_atoi(av[3]);
	rules->t_sleep = ft_atoi(av[4]);
	rules->all_eaten = 0;
	rules->dead = 0;
	if (rules->num_of_philo <= 0 || rules->t_die <= 0
		|| rules->t_eat <= 0 || rules->t_sleep <= 0)
		return (1);
	if (ac == 6)
	{
		rules->num_of_eat = ft_atoi(av[5]);
		if (rules->num_of_eat <= 1)
			return (1);
	}
	else
			rules->num_of_eat = -1;
	return (0);
}

void	assign(t_rules *rules, t_philo *philo)
{
	int	x;

	x = rules->num_of_philo;
	while (--x >= 0)
	{
		philo[x].rules = rules;
		philo[x].last_eat = 0;
		philo[x].eat = 0;
		philo[x].which_philo = x;
		philo[x].left_fork = x;
		philo[x].right_fork = (x + 1) % rules->num_of_philo;
	}
}

int	mutex(t_rules *rules, t_philo *philo)
{
	int	x;

	x = rules->num_of_philo;
	if (!rules->fork || !philo)
		return (1);
	while (--x >= 0)
	{
		if (pthread_mutex_init(&(rules->fork[x]), NULL) != 0)
		{
			printf("mutex init failed\n");
			return (1);
		}
	}
	if (pthread_mutex_init(&(rules->print), NULL) != 0)
		return (1);
	if (pthread_mutex_init(&(rules->meal_check), NULL) != 0)
		return (1);
	assign(rules, philo);
	return (0);
}

int	main(int ac, char **av)
{
	t_rules	*rules;

	rules = malloc(sizeof(t_rules));
	if (av_check(ac, av, rules) != 0)
	{
		free(rules);
		printf("Arguments contains error\n");
		return (1);
	}
	rules->fork = malloc(sizeof(char) * (300));
	rules->philo = malloc(sizeof(char) * (300));
	if (mutex(rules, rules->philo))
		return (1);
	if (threading(rules, rules->philo) != 0)
		printf("error\n");
	free(rules->fork);
	free(rules->philo);
	free(rules);
	return (0);
}
