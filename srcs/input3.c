/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:46:18 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/21 14:29:18 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_control_d_quote(t_data *data, t_info *info)
{
	data->control_d_g = true;
	exit_codes(EXIT_2, data);
	ft_putstr_fd("unexpected EOF while looking for matching '", 2);
	ft_putchar_fd(data->v->quote, 2);
	ft_putstr_fd("'\nsyntax error: unexpected end of file\n", 2);
	return (SUCCESS);
}

int	ft_ask_user_for_more_input(t_data *data)
{
	char	*more_input;
	t_info	*info_g;

	info_g = data->input_info_g;
	info_g->init_input = ft_join_input(info_g->init_input, "\n");
	if (info_g->init_input == NULL)
		return (error_i(MALLOC_ERROR, data));
	more_input = readline("> ");
	if (more_input == NULL)
		return (ft_control_d_quote(data, info_g));
	info_g->init_input = ft_strjoin(info_g->init_input, more_input);
	if (info_g->init_input == NULL)
		return (error_i(MALLOC_ERROR, data));
	free(more_input);
	return (SUCCESS);
}

int	ft_combine_fl_ft_2(t_data *data, int i, char **str)
{
	if (i == 0 || data->input_info_g->real_eof[i - 1] == true)
		(*str) = ft_join_input((*str), "\n");
	if ((*str) == NULL)
		return (error_i(MALLOC_ERROR, data));
	(*str) = ft_join_input((*str), data->input_info_g->text_input[i]);
	if ((*str) == NULL)
		return (error_i(MALLOC_ERROR, data));
	if (data->input_info_g->real_eof[i] == true)
		(*str) = ft_join_input((*str), data->input_info_g->list_eof[i]);
	if ((*str) == NULL)
		return (error_i(MALLOC_ERROR, data));
	return (SUCCESS);
}

int	ft_combine_fl_ft(t_data *data, int i)
{
	char	*str;

	str = ft_strdup(data->input_info_g->first_line);
	if (str == NULL)
		return (error_i(MALLOC_ERROR, data));
	while (i < data->input_info_g->n_eof)
	{
		if (ft_combine_fl_ft_2(data, i, &str) != SUCCESS)
			return (MALLOC_ERROR);
		i++;
	}
	if (data->input_info_g->terminal_input != NULL
		&& data->input_info_g->terminal_input[0] != 0
		&& (i == 0 || data->input_info_g->real_eof[i - 1] == true))
	{
		str = ft_join_input(str, "\n");
		if (str == NULL)
			return (error_i(MALLOC_ERROR, data));
	}
	data->input_info_g->first_line_and_final_text = str;
	return (SUCCESS);
}
