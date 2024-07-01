/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:28:55 by paxoc01           #+#    #+#             */
/*   Updated: 2024/07/01 11:23:11 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_write_error_i(t_cases case_code, t_data *data)
{
	if (case_code == MALLOC_ERROR)
	{
		printf("Memory allocation failed: %s\n", strerror(errno));
		data->malloc_error = true;
		return (MALLOC_ERROR);
	}
	if (case_code == INVALID_COMMAND)
	{
		ft_printf("Command '%s' not found.\n", data->input_info->first_line_split[0]);
		return (INVALID_COMMAND);
	}
	return (SUCCESS);
}

char	*ft_write_error_c(t_cases case_code, t_data *data)
{
	if (case_code == MALLOC_ERROR)
	{
		printf("Memory allocation failed: %s\n", strerror(errno));
		return (NULL);
	}
	if (case_code == INVALID_COMMAND)
	{
		ft_printf("Command '%s' not found.\n", data->input_info->first_line_split[0]);
		return (NULL);
	}
	return (NULL);
}
