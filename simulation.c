/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:01:59 by dgallard          #+#    #+#             */
/*   Updated: 2021/07/30 16:01:59 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

void	ft_timer(struct timeval start_time, int time_sleep)
{
	long	wait;

	wait = get_time(start_time) + time_sleep;
	while (get_time(start_time) < wait)
		usleep(500);
}

void	ft_take_fork(t_params *params)
{		
	pthread_mutex_lock(params->l_fork);
	ft_print_status(params, "take left fork", 1);
	pthread_mutex_lock(params->r_fork);
	ft_print_status(params, "take right fork", 1);
	gettimeofday(&params->start_eat, NULL);
	ft_print_status(params, "is eating", 1);
	ft_timer(params->start, params->time_to_eat);
	pthread_mutex_unlock(params->l_fork);
	pthread_mutex_unlock(params->r_fork);
}

void	ft_sleep(t_params *params)
{		
	ft_print_status(params, "is sleeping", 1);
	ft_timer(params->start, params->time_sleep);
}

void	*ft_simulation(void *tmp)
{
	int			count;
	t_params	*params;

	count = -1;
	params = (t_params *)tmp;
	if (params->dinner)
		count = params->dinner;
	while (count)
	{	
		if (params->id % 2 == 1)
			usleep(10);
		ft_take_fork(params);
		ft_sleep(params);
		ft_print_status(params, "is thinking", 1);
		if (count != -1)
			count--;
	}
	params->full = 1;
	return (NULL);
}

void	ft_start(t_params *params)
{
	int			i;

	i = 0;
	while (i < params[0].num_phil)
	{
		if (params->died == 0)
		{
			pthread_create(&params[i].phil, NULL,
				ft_simulation, &params[i]);
			usleep(10);
			i++;
		}
	}
}
