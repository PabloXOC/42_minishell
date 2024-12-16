/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 12:28:55 by paxoc01           #+#    #+#             */
/*   Updated: 2024/11/11 17:02:30 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ext_error_i(t_cases case_code, t_data *data)
{
	if (case_code == ERROR)
	{
		exit_codes(EXIT_1, data);
		data->fatal_error = true;
		return (ERROR);
	}
	if (case_code == INCOMPLETE_INPUT)
	{
		exit_codes(EXIT_8, data);
		data->input_info_g->incomplete_input = true;
		ft_printf("msh: syntax error: open quotes\n");
		return (INCOMPLETE_INPUT);
	}
	return (SUCCESS);
}

int	error_i(t_cases case_code, t_data *data)
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
		data->open_error = true;
		return (OPEN_ERROR);
	}
	if (case_code == WRITE_ERROR)
	{
		exit_codes(EXIT_1, data);
		data->v->write_error = true;
		return (WRITE_ERROR);
	}
	return (ext_error_i(case_code, data));
}

char	*error_c(t_cases case_code, t_data *data, t_spec *spec)
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
		ft_printf("Command '%s' not found.\n",
			spec->input_info->first_line_split[0]);
		return (NULL);
	}
	return (NULL);
}
