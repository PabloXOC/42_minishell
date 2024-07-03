/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes_errors_coms.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/07/03 13:16:31 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_handle_arg_n(char **command, int n_arg, t_data *data)
{
	int	i;

	i = 0;
	while (command[i] != 0)
		i++;
	if (i == n_arg)
		return (false);
	else
	{
		if (ft_strncmp(command[0], "exit", ft_strlen(command[0])) == 0)
		{
			ft_putstr_fd(command[0], 2);
			ft_putstr_fd(": invalid argument\n", 2);
			exit_codes(EXIT_128, data);
			data->exit = true;
		}
		else
		{
			ft_putstr_fd(command[0], 2);
			ft_putstr_fd(": too many arguments\n", 2);
			exit_codes(EXIT_2, data);
		}
		return (true);
	}
}

bool	ft_check_for_flags(char **command, t_data *data)
{
	if (command[1] == 0)
		return (false);
	else if (command[1][0] == '-')
	{
		ft_putstr_fd(command[0], 2);
		ft_putstr_fd(": no flags accepted for this command\n", 2);
		exit_codes(EXIT_2, data);
		return (true);
	}
	else
		return (false);
}

bool	ft_command_args_errors(char **command, t_data *data)
{
	if (command[0] == NULL)
		return (false);
	if (ft_strncmp(command[0], "echo", ft_strlen(command[0])) == 0)
		return (false);
	if (ft_strncmp(command[0], "pwd", ft_strlen(command[0])) == 0)
		return (ft_check_for_flags(command, data));
	if (ft_strncmp(command[0], "cd", ft_strlen(command[0])) == 0)
	{
		if (command[1] == NULL)
			return (false);
		else if (ft_handle_arg_n(command, 2, data) == false)
			return (false);
		else
			return (true);
	}
	if (ft_strncmp(command[0], "export", ft_strlen(command[0])) == 0)
		return (ft_check_for_flags(command, data));
	if (ft_strncmp(command[0], "unset", ft_strlen(command[0])) == 0)
		return (ft_check_for_flags(command, data));
	if (ft_strncmp(command[0], "env", ft_strlen(command[0])) == 0)
		return (ft_handle_arg_n(command, 1, data));
	if (ft_strncmp(command[0], "exit", ft_strlen(command[0])) == 0)
		return (ft_handle_arg_n(command, 1, data));
	return (false);
}

int	return_builtin_exit_code(char **command)
{
	if (ft_strncmp(command[0], "exit", ft_strlen(command[0])) == 0)
		return (EXIT_128);
	return (EXIT_2);
}
