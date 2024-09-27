/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:16:44 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/27 14:11:59 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_complete_specific(t_data *data, int i)
{
	ft_set_to_null(data->spec[i], data);
	data->spec[i]->input_info = (t_info *) malloc (sizeof (t_info));
	if (data->spec[i]->input_info == NULL)
		return (error_i(MALLOC_ERROR, data));
	ft_set_to_null_2(data->spec[i]->input_info, data, i);
	if (ft_split_semicolon(data, i) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

int	ft_assign_eof(t_spec *spec)
{
	char	**text_list;
	int		i;
	int		j;

	text_list = (char **) malloc ((spec->n_eof + 1) * sizeof (char *));
	if (text_list == NULL)
		return (error_i(MALLOC_ERROR, spec->data));
	j = spec->data->v->n_eof_saved;
	i = 0;
	while (i < spec->n_eof)
	{
		text_list[i] = ft_strdup(spec->data->input_info_g->text_input[i + j]);
		if (text_list[i] == NULL)
			return (error_i(MALLOC_ERROR, spec->data));
		i++;
	}
	spec->data->v->n_eof_saved += spec->n_eof;
	text_list[i] = 0;
	spec->input_info->text_input = text_list;
	return (SUCCESS);
}

void	ft_count_eof(t_spec *spec, int s_q, int d_q)
{
	int		i;
	int		count;
	char	*str;

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

int	ft_break_semicolons(t_data *data, int i)
{
	int	semicolon_count;

	semicolon_count = ft_count_semicolons(data, 0, 0);
	data->spec = (t_spec **) malloc ((semicolon_count + 2) * sizeof (t_spec *));
	if (data->spec == NULL)
		return (error_i(MALLOC_ERROR, data));
	data->spec[semicolon_count + 1] = 0;
	while (i < semicolon_count + 1)
	{
		data->spec[i] = (t_spec *) malloc (sizeof (t_spec));
		if (data->spec[i] == NULL)
			return (error_i(MALLOC_ERROR, data));
		if (ft_complete_specific(data, i) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		ft_count_eof(data->spec[i], 0, 0);
		if (ft_assign_eof(data->spec[i]))
			return (MALLOC_ERROR);
		i++;
	}
	return (SUCCESS);
}
