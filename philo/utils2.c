/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/20 14:31:18 by lwilliam          #+#    #+#             */
/*   Updated: 2023/01/20 14:32:09 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
