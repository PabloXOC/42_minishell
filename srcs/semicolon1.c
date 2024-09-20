/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:16:44 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/20 17:28:22 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_complete_specific(t_data *data, int i)
{
	ft_set_to_null(data->specific[i], data);
	data->specific[i]->input_info = (t_input_var *) malloc (sizeof (t_input_var));
	if (data->specific[i]->input_info == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	ft_set_to_null_2(data->specific[i]->input_info, data, i);
	if (ft_split_semicolon(data, i) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

int	ft_assign_eof(t_specific *spec, int s_q, int _d_q)
{
	char **text_list;
	int	i;
	int	j;

	text_list = (char **) malloc ((spec->n_eof + 1) * sizeof (char *));
	if (text_list == NULL)
			return (ft_write_error_i(MALLOC_ERROR, spec->data));
	j = spec->data->v->n_eof_saved;
	i = 0;
	while (i < spec->n_eof)
	{
		text_list[i] = ft_strdup(spec->data->input_info_g->text_input[i + j]);
		if (text_list[i] == NULL)
			return (ft_write_error_i(MALLOC_ERROR, spec->data));
		i++;
	}
	spec->data->v->n_eof_saved += spec->n_eof;
	text_list[i] = 0;
	spec->input_info->text_input = text_list;
	return (SUCCESS);
}

int ft_count_eof(t_specific *spec, int s_q, int d_q)
{
	int	i;
	int	count;
	char *str;

	i = 0;
	count = 0;
	str = spec->input_info->first_line_ref;
	while (str[i] != 0)
	{
		if (str[i] == '\"' && s_q % 2 == 0 && (i == 0 || str[i - 1] != '\\'))
			d_q++;
		if (str[i] == '\'' && d_q % 2 == 0 && (i == 0 || str[i - 1] != '\\'))
			s_q++;
		if (s_q % 2 == 0 && d_q % 2 == 0 && str[i] == '<' && str[i + 1] == '<')
			count++;
		i++;
	}
	spec->n_eof = count;
}

int ft_break_semicolons(t_data *data, int i)
{
	int	semicolon_count;

	semicolon_count = ft_count_semicolons(data, 0, 0);
	data->specific = (t_specific **) malloc ((semicolon_count + 2) * sizeof (t_specific *));
	if (data->specific == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	data->specific[semicolon_count + 1] = 0;
	while (i < semicolon_count + 1)
	{
		data->specific[i] = (t_specific *) malloc (sizeof (t_specific));
		if (data->specific[i] == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
		if (ft_complete_specific(data, i) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		ft_count_eof(data->specific[i], 0, 0);
		ft_assign_eof(data->specific[i], 0, 0);
		i++;
	}
	return (SUCCESS);
}
