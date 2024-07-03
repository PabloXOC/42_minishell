/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:46:18 by pximenez          #+#    #+#             */
/*   Updated: 2024/07/03 17:36:39 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_control_d_quote(t_data *data, t_input_var *info)
{
	data->control_d = true;
	exit_codes(EXIT_2, data);
	ft_putstr_fd("unexpected EOF while looking for matching '", 2);
	ft_putchar_fd(data->quote, 2);
	ft_putstr_fd("'\nsyntax error: unexpected end of file\n", 2);
	return (SUCCESS);
}

int	ft_ask_user_for_more_input(t_data *data)
{
	char		*more_input;
	t_input_var	*info;

	info = data->input_info;
	info->init_input = ft_join_input(info->init_input, "\n");
	if (data->input_info->init_input == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	more_input = readline("> ");
	if (more_input == NULL)
		return (ft_control_d_quote(data, data->input_info));
	info->init_input = ft_strjoin(info->init_input, more_input);
	if (info->init_input == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	free(more_input);
	return (SUCCESS);
}

int	ft_combine_fl_ft_2(t_data *data, t_input_var *info, int i, char **str)
{
	if (i == 0 || info->real_eof[i - 1] == true)
		(*str) = ft_join_input((*str), "\n");
	if ((*str) == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	(*str) = ft_join_input((*str), info->text_input[i]);
	if ((*str) == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	if (info->real_eof[i] == true)
		(*str) = ft_join_input((*str), info->list_eof[i]);
	if ((*str) == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	return (SUCCESS);
}

int	ft_combine_fl_ft(t_data *data, t_input_var *info, int i)
{
	char	*str;

	str = ft_strdup(data->input_info->first_line);
	if (str == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	while (i < info->n_eof)
	{
		if (ft_combine_fl_ft_2(data, info, i, &str) != SUCCESS)
			return (MALLOC_ERROR);
		i++;
	}
	if (info->terminal_input != NULL && info->terminal_input[0] != 0
		&& (i == 0 || info->real_eof[i - 1] == true))
	{
		str = ft_join_input(str, "\n");
		if (str == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
	}
	data->input_info->first_line_and_final_text = str;
	return (SUCCESS);
}
