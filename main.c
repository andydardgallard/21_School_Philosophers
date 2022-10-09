/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:01:50 by dgallard          #+#    #+#             */
/*   Updated: 2021/07/30 16:01:50 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_check_dead(t_params *phil, int place, int fat)
{
	int	i;	
	int	time;

	i = 1;
	while (i || !phil[i - 1].full)
	{
		time = (int)get_time(phil[i - 1].start_eat);
		if (time > fat)
		{			
			phil[i - 1].died = 1;
			ft_print_status(&phil[i - 1], "died", 0);
			return (1);
		}
		if (i == place - 1)
			break ;
		i++;
	}
	return (0);
}

int	ft_check_full(t_params *phil)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	while (i && phil[i - 1].full)
	{
		if (phil[i - 1].full)
			j++;
		if (j == phil->num_phil)
			return (1);
	}
	return (0);
}

int	ft_monitor(t_params *phil, int	place, int fat)
{
	while (1)
	{
		if (ft_check_dead(phil, place, fat))
			return (1);
		if (ft_check_full(phil))
			return (1);
	}
	return (0);
}

void	ft_one_phil(t_params *params)
{
	pthread_mutex_lock(params->l_fork);
	printf("%ld %d %s\n", get_time(params->start), params->id,
		"take left fork");
	ft_timer(params->start, params->time_to_die);
	printf("%ld %d %s\n", get_time(params->start), params->id,
		"died");
	pthread_mutex_unlock(params->l_fork);
}

int	main(int argc, char **argv)
{
	t_params		params;
	t_params		*phil;
	pthread_mutex_t	print;

	if (argc != 6 && argc != 5)
		return (ft_return("Wrong number of params", 2));
	init_struct(&params);
	gettimeofday(&params.start, NULL);
	if (ft_parser(argv, argc, &params) == 2)
		return (1);
	ft_init_mutex(&params, &print);
	phil = (t_params *)malloc(sizeof(t_params) * params.num_phil);
	if (!phil)
		return (ft_return("Wrong malloc", 2));
	ft_fill_struct(params, phil, &print);
	if (params.num_phil == 1)
	{
		ft_one_phil(&phil[0]);
		free(phil);
		free(params.fork);
		return (0);
	}
	ft_start(phil);
	ft_monitor(phil, params.num_phil, params.time_to_die);
	return (0);
}
