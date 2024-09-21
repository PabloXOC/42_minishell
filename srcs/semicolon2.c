/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:52:43 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/21 14:55:52 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pos_semicolon(t_data *data, int n_semi, char *str, int j)
{
	int	d_q;
	int	s_q;
	int	count;

	s_q = 0;
	d_q = 0;
	count = 1;
	if (n_semi == 0)
		return (0);
	while (str[j] != 0)
	{
		if (str[j] == '\"' && s_q % 2 == 0 && (j == 0 || str[j - 1] != '\\'))
			d_q++;
		if (str[j] == '\'' && d_q % 2 == 0 && (j == 0 || str[j - 1] != '\\'))
			s_q++;
		if (str[j] == ';' && str[j - 1] != '\\' && s_q % 2 == 0 && d_q % 2 == 0)
		{
			if (count == n_semi)
				return (j + 1);
			count++;
		}
		j++;
	}
	return (j);
}

int	ft_size_semicolon(t_data *data, int pos, char *str)
{
	int	s_q;
	int	d_q;
	int	j;

	s_q = 0;
	d_q = 0;
	j = pos;
	while (str[j] != 0)
	{
		if (str[j] == '\"' && s_q % 2 == 0 && (j == 0 || str[j - 1] != '\\'))
			d_q++;
		if (str[j] == '\'' && d_q % 2 == 0 && (j == 0 || str[j - 1] != '\\'))
			s_q++;
		if (str[j] == ';' && str[j - 1] != '\\' && s_q % 2 == 0 && d_q % 2 == 0)
			return (j - pos);
		j++;
	}
	return (j);
}

int	ft_copy_text(t_data *data, int size, int start, int semi_pos)
{
	int		i;
	int		j;
	char	*str;

	i = start;
	j = 0;
	str = (char *) malloc ((size + 1) * sizeof (char));
	if (str == NULL)
		return (error_i(MALLOC_ERROR, data));
	while (j < size)
		str[j++] = data->input_info_g->first_line_ref[i++];
	str[j] = 0;
	data->spec[semi_pos]->input_info->first_line_ref = str;
	return (SUCCESS);
}

int	ft_split_semicolon(t_data *data, int i)
{
	int	pos;
	int	size;

	pos = ft_pos_semicolon(data, i, data->input_info_g->first_line_ref, 0);
	size = ft_size_semicolon(data, pos, data->input_info_g->first_line_ref);
	if (ft_copy_text(data, size, pos, i) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (SUCCESS);
}
