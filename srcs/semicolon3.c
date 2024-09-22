/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:16:44 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/21 14:00:01 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_count_semicolons(t_data *data, int s_q, int d_q)
{
	int		i;
	int		count;
	char	*str;

	str = data->input_info_g->first_line_ref;
	i = 0;
	count = 0;
	while (str[i])
	{
		if (d_q % 2 == 0 && str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
			s_q++;
		if (s_q % 2 == 0 && str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
			d_q++;
		if (str[i - 1] != '\\' && str[i] == ';' && s_q % 2 == 0 && d_q % 2 == 0)
			count++;
		i++;
	}
	data->n_semicolons = count;
	return (count);
}

void	ft_set_to_null(t_spec *spec, t_data *data)
{
	spec->input_info = NULL;
	spec->next_eof = NULL;
	spec->data = data;
	spec->jj = 0;
	spec->n_eof = 0;
	spec->command_list = NULL;
	spec->no_commands = true;
}

void	ft_set_to_null_2(t_info *i_v, t_data *data, int i)
{
	i_v->init_input = NULL;
	i_v->init_input_split = NULL;
	i_v->first_line = NULL;
	i_v->first_line_split = NULL;
	i_v->search_eof = NULL;
	i_v->terminal_input = NULL;
	i_v->final_text = NULL;
	i_v->final_text_last = NULL;
	i_v->list_eof = NULL;
	i_v->n_eof = 0;
	i_v->first_line_and_final_text = NULL;
	i_v->text_input = NULL;
	i_v->real_eof = NULL;
	i_v->invalid_token = false;
	i_v->incomplete_input = false;
	i_v->first_line_vars = NULL;
	i_v->spec = data->spec[i];
}
