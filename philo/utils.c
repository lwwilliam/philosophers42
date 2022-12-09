/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lwilliam <lwilliam@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/23 12:37:23 by lwilliam          #+#    #+#             */
/*   Updated: 2022/12/09 13:32:06 by lwilliam         ###   ########.fr       */
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
