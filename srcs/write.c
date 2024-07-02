/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:28:55 by paxoc01           #+#    #+#             */
/*   Updated: 2024/07/02 19:01:02 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ext_write_error_i(t_cases case_code, t_data *data)
{
	if (case_code == ERROR)
	{
		exit_codes(EXIT_1, data);
		data->fatal_error = true;
		return (ERROR);
	}
	return (SUCCESS);
}

int	ft_write_error_i(t_cases case_code, t_data *data)
{
	if (case_code == MALLOC_ERROR)
	{
		exit_codes(EXIT_1, data);
		ft_printf("Memory allocation failed: %s\n", strerror(errno));
		data->fatal_error = true;
		return (MALLOC_ERROR);
	}
	if (case_code == OPEN_ERROR)
	{
		exit_codes(EXIT_1, data);
		perror("Open failure");
		data->fatal_error = true;
		return (OPEN_ERROR);
	}
	if (case_code == WRITE_ERROR)
	{
		exit_codes(EXIT_1, data);
		data->fatal_error = true;
		return (WRITE_ERROR);
	}
	return (ext_write_error_i(case_code, data));
}

char	*ft_write_error_c(t_cases case_code, t_data *data)
{
	if (case_code == MALLOC_ERROR)
	{
		exit_codes(EXIT_1, data);
		ft_printf("Memory allocation failed: %s\n", strerror(errno));
		data->fatal_error = true;
		return (NULL);
	}
	if (case_code == ERROR)
	{
		exit_codes(EXIT_1, data);
		data->fatal_error = true;
		return (NULL);
	}
	if (case_code == INVALID_COMMAND)
	{
		ft_printf("Command '%s' not found.\n", data->input_info->first_line_split[0]);
		return (NULL);
	}
	return (NULL);
}
