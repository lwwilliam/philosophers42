/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:24:29 by lwilliam          #+#    #+#             */
/*   Updated: 2022/12/29 02:50:20 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
// https://github.com/ucefooo/philosopher_with_bonus

int	av_check(int ac, char **av, t_rules *rules)
{
	int	count;
	int	len;

	count = 1;
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
	if (initfunct(ac, av, rules) != 0)
		return (1);
	return (0);
}

int	initfunct(int ac, char **av, t_rules *rules)
{
	rules->num_of_philo = ft_atoi(av[1]);
	rules->t_die = ft_atoi(av[2]);
	rules->t_eat = ft_atoi(av[3]);
	rules->t_sleep = ft_atoi(av[4]);
	if (rules->num_of_philo <= 0 || rules->t_die <= 0
		|| rules->t_eat <= 0 || rules->t_sleep <= 0)
		return (1);
	if (ac == 6)
	{
		rules->num_of_eat = ft_atoi(av[5]);
		if (rules->num_of_eat <= 0)
			return (1);
	}
	return (0);
}

void assign(t_rules *rules, t_philo *philo, pthread_mutex_t *pr)
{
	int	x;

	x = 0;
	while (x < rules->num_of_philo)
	{
		philo[x].rules = rules;
		philo[x].eat = 0;
		philo[x].which_philo = x + 1;
		philo[x].print = pr;
		x++;
	}
	rules->time = timestamp();
}

int	init(t_rules *rules, t_philo *philo)
{
	int				x;
	pthread_mutex_t	pr;


	x = 0;
	if (!philo->fork || !philo)
		return (1);
	while (x < rules->num_of_philo)
	{
		printf("\033[0;33mcreating mutex %d\n\033[0m", x);
		if (pthread_mutex_init(&(philo->fork[x++]), NULL) != 0)
		{
			printf("mutex init failed\n");
			return (1);
		}
	}
	if (pthread_mutex_init(&pr, NULL) != 0)
		return (1);
	assign(rules, philo, &pr);
	return (0);
}

void	dest_mutex(t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->rules->num_of_philo)
		pthread_mutex_destroy(&philo->fork[i++]);
}

void	end(t_philo *philo, t_rules *rules)
{
	int	i;

	i = 0;
	while (1)
	{
		if (philo[i].rules->t_eat == philo[i].rules->num_of_philo)
		{
			dest_mutex(philo);
			// free_param(philo, philo->fork, rules);
			return ;
		}
		if (timestamp() - philo[i].last_eat > (long long)rules->t_die)
		{
			usleep(100);
			pthread_mutex_lock(philo->print);
			printf("%lldms	%d died\n", timestamp() - rules->time, philo->which_philo);
			dest_mutex(philo);
			// free_param(philo, philo->fork, rules);
			return ;
		}
		i = (i + 1) % rules->num_of_philo;
		usleep(500);
	}
}

int	main(int ac, char **av)
{
	t_rules	*rules;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
	{
		printf("Error! <num_of_philo time_die time_eat\
time_sleep (num_eat)>\n");
		return (1);
	}
	rules = (t_rules *)malloc(sizeof(t_rules));
	if (av_check(ac, av, rules) != 0)
	{
		printf("Arguments contains error\n");
		return (1);
	}
	philo = (t_philo *)malloc(sizeof(t_philo) * (rules->num_of_philo));
	philo->fork = malloc(sizeof(char) * (rules->num_of_philo));
	if (init(rules, philo) != 0)
		return (1);
	philo->threads = (pthread_t *)malloc(sizeof(pthread_t)
			* (rules->num_of_philo));
	if (threading(rules, philo) != 0)
		printf("error\n");
	end(philo, rules);
	free(philo->fork);
	return (0);
}
