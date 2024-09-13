/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:20:50 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/13 11:16:03 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_malloc_eof(t_data *data, t_input_var *info, int i)
{
	info->list_eof = (char **) malloc ((info->n_eof + 1) * (sizeof (char *)));
	if (info->list_eof == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	info->text_input = (char **) malloc ((info->n_eof + 1) * (sizeof (char *)));
	if (info->text_input == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	info->real_eof = (bool *) malloc ((info->n_eof) * (sizeof (bool)));
	if (info->real_eof == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	while (i < info->n_eof)
	{
		info->real_eof[i] = true;
		i++;
	}
	info->list_eof[info->n_eof] = 0;
	info->text_input[info->n_eof] = 0;
	return (SUCCESS);
}

int	ft_add_text(t_data *data, t_input_var *info_g, int i)
{
	char	*more_input;
	char	*temp;

	more_input = NULL;
	info_g->terminal_input = ft_join_input(info_g->terminal_input, "\n");
	if (info_g->terminal_input == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	more_input = readline("> ");
	if (more_input == NULL)
		return (ft_control_d_heredoc(data, info_g, i));
	else
	{
		temp = ft_strjoin(info_g->terminal_input, more_input);
		if (info_g->terminal_input != NULL)
			free(info_g->terminal_input);
		info_g->terminal_input = temp;
	}
	free(more_input);
	return (SUCCESS);
}

//for every << we must compare the eof
int	ft_get_ter_input(t_data *data, t_input_var *info_g, int i, char *f_line)
{
	info_g->list_eof[data->v->k] = ft_find_eof(f_line, i + 2, data);
	if (info_g->list_eof[data->v->k] == NULL)
		return (MALLOC_ERROR);
	while (data->exit == false)
	{
		while (info_g->terminal_input != 0 && info_g->terminal_input[data->v->ii] != 0)
		{
			if (info_g->terminal_input[data->v->ii] == '\n'
				&& ft_compare_eof(&info_g->terminal_input[data->v->ii + 1],
					info_g->list_eof[data->v->k], data) == true)
				return (SUCCESS);
			data->v->ii++;
		}
		if (ft_add_text(data, info_g, data->v->k) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	return (SUCCESS);
}

//to make ft_terminal_input fit in 25 lines
int	ft_terminal_input_util(t_data *data, int s_q, int d_q, char *f_line)
{
	if (s_q % 2 == 0 && d_q % 2 == 0)
	{
		if (f_line[data->v->i_ter] == '<' && f_line[data->v->i_ter + 1] == '<')
		{
			if (ft_get_ter_input(data, data->input_info_g,
					data->v->i_ter, f_line) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			data->v->k++;
			data->v->i_ter += 2;
		}
	}
	return (SUCCESS);
}

//to make the terminal input from <<
int	ft_terminal_input(t_data *data, int s_q, int d_q)
{
	char	*f_line;

	f_line = data->input_info_g->first_line_ref;
	if (ft_malloc_eof(data, data->input_info_g, 0) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	while (f_line[data->v->i_ter] != 0)
	{
		if (f_line[data->v->i_ter] == '\"' && s_q % 2 == 0
			&& (data->v->i_ter == 0 || f_line[data->v->i_ter - 1] != '\\'))
			d_q += 1;
		if (f_line[data->v->i_ter] == '\'' && d_q % 2 == 0
			&& (data->v->i_ter == 0 || f_line[data->v->i_ter - 1] != '\\'))
			s_q += 1;
		if (ft_terminal_input_util(data, s_q, d_q, f_line) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		data->v->i_ter++;
	}
	return (SUCCESS);
}
