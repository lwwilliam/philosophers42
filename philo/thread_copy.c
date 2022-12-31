// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   thread_copy.c                                      :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2022/11/23 10:19:39 by lwilliam          #+#    #+#             */
// /*   Updated: 2022/12/31 14:55:26 by lwilliam         ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "philo.h"

// long long	time_diff(long long past, long long pres)
// {
// 	return (pres - past);
// }

// void		smart_sleep(long long time, t_philo *philo)
// {
// 	long long i;

// 	i = timestamp();
// 	while (!(philo->dead))
// 	{
// 		if (time_diff(i, timestamp()) >= time)
// 			break ;
// 		usleep(50);
// 	}
// }

// void		action_print(t_philo *philo, int id, char *string)
// {
// 	pthread_mutex_lock(&(philo->print));
// 	if (!(philo->dead))
// 	{
// 		printf("%lli ", timestamp() - philo->rules->time);
// 		printf("%i ", id + 1);
// 		printf("%s\n", string);
// 	}
// 	pthread_mutex_unlock(&(philo->print));
// 	return ;
// }

// void	philo_eats(t_philo *philo)
// {
// 	t_rules *rules;

// 	rules = philo->rules;
// 	pthread_mutex_lock(&(philo->fork[philo->left_fork]));
// 	action_print(philo, philo->which_philo, "has taken a fork");
// 	pthread_mutex_lock(&(philo->fork[philo->right_fork]));
// 	action_print(philo, philo->which_philo, "has taken a fork");
// 	pthread_mutex_lock(&(philo->meal_check));
// 	action_print(philo, philo->which_philo, "is eating");
// 	philo->last_eat = timestamp();
// 	pthread_mutex_unlock(&(philo->meal_check));
// 	smart_sleep(rules->t_eat, philo);
// 	(philo->eat)++;
// 	pthread_mutex_unlock(&(philo->fork[philo->left_fork]));
// 	pthread_mutex_unlock(&(philo->fork[philo->right_fork]));
// }

// void	*p_thread(void *void_philosopher)
// {
// 	int				i;
// 	t_philo			*philo;
// 	t_rules			*rules;

// 	i = 0;
// 	philo = (t_philo *)void_philosopher;
// 	rules = philo->rules;
// 	if (philo->which_philo % 2)
// 		usleep(15000);
// 	while (!(philo->dead))
// 	{
// 		philo_eats(philo);
// 		if (philo->all_ate)
// 			break ;
// 		action_print(philo, philo->which_philo, "is sleeping");
// 		// smart_sleep(rules->t_sleep, rules);
// 		action_print(philo, philo->which_philo, "is thinking");
// 		i++;
// 	}
// 	return (NULL);
// }

// void	exit_launcher(t_rules *rules, t_philo *philos)
// {
// 	int i;

// 	i = -1;
// 	while (++i < rules->num_of_philo)
// 		pthread_join(philos[i].threads, NULL);
// 	i = -1;
// 	while (++i < rules->num_of_philo)
// 		pthread_mutex_destroy(&(philos->fork[i]));
// 	pthread_mutex_destroy(&(philos->print));
// }

// // void	death_checker(t_rules *r, t_philo *p)
// // {
// // 	int i;

// // 	while (!(p->all_ate))
// // 	{
// // 		i = -1;
// // 		while (++i < r->num_of_philo && !(p->dead))
// // 		{
// // 			pthread_mutex_lock(&(p->meal_check));
// // 			if (time_diff(p[i].t_last_meal, timestamp()) > r->t_die)
// // 			{
// // 				action_print(r, i, "died");
// // 				r->dieded = 1;
// // 			}
// // 			pthread_mutex_unlock(&(r->meal_check));
// // 			usleep(100);
// // 		}
// // 		if (r->dieded)
// // 			break ;
// // 		i = 0;
// // 		while (r->nb_eat != -1 && i < r->nb_philo && p[i].x_ate >= r->nb_eat)
// // 			i++;
// // 		if (i == r->nb_philo)
// // 			r->all_ate = 1;
// // 	}
// // }

// int		launcher(t_rules *rules)
// {
// 	int				i;
// 	t_philo			*phi;

// 	i = 0;
// 	phi = rules->philo;
// 	rules->time = timestamp();
// 	while (i < rules->num_of_philo)
// 	{
// 		if (pthread_create(&(phi[i].threads), NULL, p_thread, &(phi[i])))
// 			return (1);
// 		phi[i].last_eat = timestamp();
// 		i++;
// 	}
// 	// death_checker(rules, rules->philosophers);
// 	exit_launcher(rules, phi);
// 	return (0);
// }