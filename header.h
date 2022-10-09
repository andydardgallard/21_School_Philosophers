/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:01:38 by dgallard          #+#    #+#             */
/*   Updated: 2021/07/30 16:01:38 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HEADER_H
# define HEADER_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_params
{
	int				id;
	int				num_phil;
	int				time_to_die;
	int				full;
	int				time_to_eat;
	int				time_sleep;
	int				dinner;
	int				died;	
	pthread_t		phil;
	struct timeval	start_eat;
	struct timeval	start;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*fork;
	pthread_mutex_t	*print_mutex;
}					t_params;

void	ft_start(t_params *params);
long	get_time(struct timeval time);
void	init_struct(t_params *params);
int		ft_return(char *str, int result);
int		ft_check_dead(t_params *phil, int place, int fat);
int		ft_parser(char **argv, int argc, t_params *params);
void	ft_print_status(t_params *params, char *str, int i);
void	ft_timer(struct timeval start_time, int time_sleep);
void	ft_init_mutex(t_params *params, pthread_mutex_t	*print);
void	ft_fill_struct(t_params params, t_params *phil, pthread_mutex_t	*print);
#endif
