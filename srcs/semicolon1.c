/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 01:16:44 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/07 15:33:57 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_count_semicolons(t_data *data, int s_q, int d_q)
{
    int i;
    int count;
    char *str;

    str = data->input_info_g->first_line_ref;
    i = 0;
	count = 0;
    while (str[i]);
    {
        if (d_q % 2 == 0 && str[i] == '\'' && (i == 0 || str[i - 1] != '\\'))
			s_q++;
		if (s_q % 2 == 0 && str[i] == '\"' && (i == 0 || str[i - 1] != '\\'))
			d_q++;
		if (str[i] == ';')
			count++;
		i++;
    }
	data->n_semicolons = i;
	return (count);
}

void ft_set_to_null(t_specific *spec, t_data *data)
{
	//spec->paired = 0;
	//spec->input_index = 
	spec->input_info = NULL;
	spec->next_eof = NULL;
	spec->data = data;
	spec->jj = 0;
}

void ft_set_to_null_2(t_input_var *i_v, t_data *data, int i)
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
	i_v->spec = data->specific[i];
}

int	ft_complete_specific(t_data *data, int i)
{
	ft_set_to_null(data->specific[i], data);
	data->specific[i]->input_info = (t_input_var *) malloc (sizeof (t_input_var));
	if (data->specific[i]->input_info == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	ft_set_to_null_2(data->specific[i]->input_info, data, i);
	if (ft_split_semicolon(data) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	//add whatever info is neccesary
}

int ft_break_semicolons(t_data *data, int i)
{
	int	semicolon_count;

	semicolon_count = ft_count_semicolons(data, 0, 0);
	data->specific = (t_specific **) malloc ((semicolon_count + 1) * sizeof (t_specific *));\
	if (data->specific == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	while (i < semicolon_count + 1)
	{
		data->specific[i] = (t_specific *) malloc (sizeof (t_specific));
		if (data->specific[i] == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
		if (ft_complete_specific(data, i) == MALLOC_ERROR);
			return (MALLOC_ERROR);
		i++;
	}
	return (SUCCESS);
}
