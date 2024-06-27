/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_save_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:02:00 by paxoc01           #+#    #+#             */
/*   Updated: 2024/06/27 16:33:51 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_charcomp(const char *str1, const char *str2)
{
	size_t		i;

	i = 0;
	while (str1[i] != 0 && str2[i] != 0)
	{
		if (str1[i] - str2[i] != 0)
			return (false);
		i++;
	}
	if (str1[i] != 0 || str2[i] != 0)
		return (false);
	return (true);
}

static bool	ft_isalnum_bool(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= 48 && c <= 57))
		return (true);
	else
		return (false);
}

bool	ft_isspecial(const char *str)
{
	size_t		i;

	i = 0;
	while (str[i] != '=')
	{
		if (ft_isalnum_bool(str[i]) == false && str[i] != '_')
			return (true);
		i++;
	}
	return (false);
}

bool	ft_starts_with_number(const char *str)
{
	if (str[0] >= '0' && str[0] <= '9')
		return (false);
	return (true);
}

bool	check_if_we_save_variables(t_data *data)
{
	int	i;

	i = 0;
	while (data->input_info->first_line_split[i] != 0)
	{
		if (ft_charcomp(data->input_info->first_line_split[i], ">") == true
			|| ft_charcomp(data->input_info->first_line_split[i], "<") == true
			|| ft_charcomp(data->input_info->first_line_split[i], ">>") == true
			|| ft_charcomp(data->input_info->first_line_split[i], "<<") == true)
			i++;
		else if (ft_charcomp(data->input_info->first_line_split[i], "|") == true) //we have pipes
			return (false);
		else if (ft_there_is_equal(data->input_info->first_line_split[i]) == false) //we dont have an equal sign
			return (false);
		else if (ft_isspecial(data->input_info->first_line_split[i]) == true) //we have a special character
			return (false);
		else if (ft_starts_with_number(data->input_info->first_line_split[i]) == true) //starts with a number
			return (false);
		if (data->input_info->first_line_split[i] != 0)
			i++;
	}
	return (true);
}
