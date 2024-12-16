/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_exit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 11:40:01 by pximenez          #+#    #+#             */
/*   Updated: 2024/11/06 11:42:16 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_full_n(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] != 0)
	{
		if (ft_isdigit(str[i]) == 0)
			return (false);
		i++;
	}
	return (true);
}

static int	ft_atoi_exit(const char *str)
{
	int	loop;
	int	temp;
	int	sign;

	temp = 0;
	loop = 0;
	sign = 1;
	while (str[loop] == 32)
		loop++;
	if (str[loop] == '+' || str[loop] == '-')
	{
		if (str[loop] == '-')
			sign = -1;
		loop++;
	}
	while (str[loop] >= '0' && str[loop] <= '9')
	{
		temp = 10 * temp + str[loop] - '0';
		loop++;
	}
	return (temp * sign);
}

static int	count_arg(char **args)
{
	int	i;

	i = 0;
	while (args[i] != 0)
		i++;
	return (i);
}

int	handle_exit(t_command *full_com, t_data *data)
{
	data->exit = true;
	write(1, "exit\n", 5);
	if (count_arg(full_com->content) == 1)
		exit_codes(EXIT_0, data);
	else if (count_arg(full_com->content) > 2)
	{
		write(2, "exit: too many arguments\n", 25);
		exit_codes(EXIT_1, data);
	}
	else if (is_full_n(full_com->content[1]) == false)
	{
		write(2, "exit: numeric argument required\n", 32);
		return (exit_codes(EXIT_2, data));
	}
	else
		exit_codes(ft_atoi_exit(full_com->content[1]), data);
	return (SUCCESS);
}
