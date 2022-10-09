/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgallard <dgallard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/30 16:02:33 by dgallard          #+#    #+#             */
/*   Updated: 2021/07/30 16:02:33 by dgallard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "header.h"

int	ft_check_digit(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp != '\0')
	{
		if (!(*tmp >= '0' && *tmp <= '9'))
			return (-1);
		tmp++;
	}
	return (0);
}

int	ft_check_space(char sim)
{
	if ((sim == ' ' || sim == '\t' || sim == '\n'
			|| sim == '\v' || sim == '\f' || sim == '\r'))
		return (1);
	return (0);
}

int	ft_atoi(char *str)
{
	int					m;
	unsigned long int	res;

	if (ft_check_digit(str) == -1)
		return (-1);
	while (ft_check_space(*str) == 1)
		str++;
	m = 1;
	if (*str == '+' || *str == '-')
	{
		if (*str == '-')
			m = (-1);
		str++;
	}
	res = 0;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str - '0');
		if ((res > 9223372036854775807) && m == (-1))
			return (0);
		if (res > 9223372036854775807)
			return (-1);
		str++;
	}
	return (res * m);
}

int	ft_parser(char **argv, int argc, t_params *params)
{
	int		i;
	long	numb;

	i = 1;
	while (i < argc)
	{
		numb = ft_atoi(argv[i]);
		if (numb <= 0)
			return (ft_return("Incorrect number", 2));
		if (i == 1)
			params->num_phil = numb;
		else if (i == 2)
			params->time_to_die = numb;
		else if (i == 3)
			params->time_to_eat = numb;
		else if (i == 4)
			params->time_sleep = numb;
		else if (i == 5)
			params->dinner = numb;
		i++;
	}
	return (1);
}
