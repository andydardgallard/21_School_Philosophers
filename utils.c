/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:02:08 by dgallard          #+#    #+#             */
/*   Updated: 2021/07/30 16:02:08 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

long	get_time(struct timeval t)
{
	struct timeval	t2;

	gettimeofday(&t2, NULL);
	return ((t2.tv_sec - t.tv_sec) * 1000 + (t2.tv_usec - t.tv_usec) / 1000);
}

void	ft_print_status(t_params *params, char *str, int i)
{	
	pthread_mutex_lock(params->print_mutex);
	printf("%ld %d %s\n", get_time(params->start), params->id, str);
	if (i != 0)
		pthread_mutex_unlock(params->print_mutex);
}

void	ft_init_mutex(t_params *params, pthread_mutex_t	*print)
{
	int	i;	

	i = 0;
	params->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* params->num_phil);
	while (i < params->num_phil)
	{
		pthread_mutex_init(&params->fork[i], NULL);
		i++;
	}	
	pthread_mutex_init(print, NULL);
}

void	init_struct(t_params *params)
{
	params->num_phil = 0;
	params->time_to_die = 0;
	params->full = 0;
	params->time_to_eat = 0;
	params->time_sleep = 0;
	params->dinner = 0;
	params->died = 0;
}

void	ft_fill_struct(t_params params, t_params *phil,
	pthread_mutex_t	*print)
{
	int	i;	

	i = 0;
	while (i < params.num_phil)
	{
		phil[i].phil = params.phil;
		phil[i].id = i + 1;
		phil[i].num_phil = params.num_phil;
		phil[i].time_to_die = params.time_to_die;
		phil[i].full = params.full;
		phil[i].start = params.start;
		phil[i].died = params.died;
		phil[i].time_to_eat = params.time_to_eat;
		phil[i].time_sleep = params.time_sleep;
		phil[i].dinner = params.dinner;
		phil[i].l_fork = &params.fork[i];
		phil[i].print_mutex = print;
		if (params.num_phil > 1)
			phil[i].r_fork = &params.fork[(i + 1) % params.num_phil];
		i++;
	}	
}
