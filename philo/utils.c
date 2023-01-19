/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:37:23 by lwilliam          #+#    #+#             */
/*   Updated: 2023/01/19 16:40:01 by lwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *str)
{
	int	x;
	int	neg;
	int	num;

	x = 0;
	neg = 1;
	num = 0;
	while ((str[x] >= '\t' && str[x] <= '\r') || str[x] == ' ')
		x++;
	if (str[x] == '-' || str[x] == '+')
	{
		if (str[x] == '-')
			neg *= -1;
		x++;
	}
	while (str[x] && str[x] >= '0' && str[x] <= '9')
	{
		num = (num * 10) + str[x] - '0';
		x++;
	}
	return (num * neg);
}

int	ft_isdigit(int x)
{
	if (x >= '0' && x <= '9')
		return (1);
	return (0);
}

int	ft_strlen(char *str)
{
	int	x;

	x = 0;
	while (str[x] != '\0')
		x++;
	return (x);
}

long long	timestamp(void)
{	
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_usec / 1000) + (time.tv_sec * 1000));
}

void	print_funct(t_rules *rules, char *action, int xphilo)
{
	long long	time;

	pthread_mutex_lock(&(rules->print));
	time = timestamp() - rules->start_time;
	if (!(rules->dead))
		printf("%lld %d %s\n", time, xphilo + 1, action);
	pthread_mutex_unlock(&(rules->print));
}
