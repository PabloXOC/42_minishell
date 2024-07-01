/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_save_input.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 16:02:00 by paxoc01           #+#    #+#             */
/*   Updated: 2024/07/01 11:51:28 by pximenez         ###   ########.fr       */
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
		return (true);
	return (false);
}

bool	check_if_we_save_variables(t_data *data, t_input_var *info)
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
		else if (ft_charcomp(info->first_line_split[i], "|") == true)
			return (false);
		else if (ft_there_is_equal(info->first_line_split[i]) == false)
			return (false);
		else if (ft_isspecial(data->input_info->first_line_split[i]) == true)
			return (false);
		else if (ft_starts_with_number(info->first_line_split[i]) == true)
			return (false);
		if (data->input_info->first_line_split[i] != 0)
			i++;
	}
	return (true);
}
