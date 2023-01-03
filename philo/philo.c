/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:24:29 by lwilliam          #+#    #+#             */
/*   Updated: 2023/01/03 23:41:01 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
// https://github.com/ucefooo/philosopher_with_bonus

int	av_check(int ac, char **av, t_rules *rules)
{
	int	count;
	int	len;

	count = 1;
	if (ac != 5 && ac != 6)
	{
		printf("Error! <num_of_philo time_die time_eat\
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
	rules->eaten = 0;
	rules->dead = 0;
	if (rules->num_of_philo <= 0 || rules->t_die <= 0
		|| rules->t_eat <= 0 || rules->t_sleep <= 0)
		return (1);
	if (ac == 6)
	{
		rules->num_of_eat = ft_atoi(av[5]);
		if (rules->num_of_eat <= 0)
			return (1);
		else
			rules->num_of_eat = -1;
	}
	return (0);
}

void assign(t_rules *rules, t_philo *philo)
{
	int	x;

	x = 0;
	while (x < rules->num_of_philo)
	{
		philo[x].rules = rules;
		philo[x].last_eat = 0;
		philo[x].eat = 0;
		philo[x].which_philo = x;
		x++;
	}
}

int	mutex(t_rules *rules, t_philo *philo)
{
	int	x;

	x = 0;
	if (!rules->fork || !philo)
		return (1);
	while (x < rules->num_of_philo)
	{
		printf("\033[0;33mcreating mutex %d\n\033[0m", x + 1);
		if (pthread_mutex_init(&(rules->fork[x++]), NULL) != 0)
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
	t_philo	*philo;

	rules = malloc(sizeof(t_rules));
	if (av_check(ac, av, rules) != 0)
	{
		printf("Arguments contains error\n");
		return (1);
	}
	philo = (t_philo *)malloc(sizeof(t_philo) * (rules->num_of_philo));
	rules->fork = malloc(sizeof(char) * (rules->num_of_philo));
	if (mutex(rules, philo))
		return (1);
	if (threading(rules, philo) != 0)
		printf("error\n");
	return (0);
}

// void	dest_mutex(t_philo *philo)
// {
// 	int	i;

// 	i = 0;
// 	while (i < philo->rules->num_of_philo)
// 		pthread_mutex_destroy(&philo->rules->fork[i++]);
// }

// void	end(t_philo *philo, t_rules *rules)
// {
// 	int	i;

// 	i = 0;
// 	while (1)
// 	{
// 		if (philo[i].total_eat == philo[i].rules->num_of_philo)
// 		{
// 			dest_mutex(philo);
// 			// free_param(philo, rules->fork, rules);
// 			return ;
// 		}
// 		if (timestamp() - philo[i].last_eat > (long long)rules->t_die)
// 		{
// 			usleep(100);
// 			pthread_mutex_lock(&(rules->print));
// 			printf("%lldms %d died\n", timestamp() - rules->time, philo->which_philo + 1);
// 			dest_mutex(philo);
// 			// free_param(philo, rules->fork, rules);
// 			return ;
// 		}
// 		i = (i + 1) % rules->num_of_philo;
// 		usleep(500);
// 	}
// }
