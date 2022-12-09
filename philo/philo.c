/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 10:24:29 by lwilliam          #+#    #+#             */
/*   Updated: 2022/12/09 20:10:40 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"philo.h"
// https://github.com/ucefooo/rulessopher_with_bonus

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

int	main(int ac, char **av)
{
	t_rules	*rules;
	t_philo	*philo;

	if (ac != 5 && ac != 6)
	{
		printf("Error! <<->/rules num_rules time_die time_eat\
time_sleep (num_eat)>>\n");
		return (1);
	}
	rules = (t_rules *)malloc(sizeof(t_rules));
	philo->start_time = timestamp();
	if (av_check(ac, av, rules) != 0)
	{
		printf("Arguments contains error\n");
		return (1);
	}
	rules = (t_rules *)malloc(sizeof(t_rules) * (rules->num_of_philo));
	rules->fork = malloc(sizeof(char) * (rules->num_of_philo));
	if (threading(rules, philo) != 0)
		printf("error\n");
	free(rules->fork);
	return (0);
}
