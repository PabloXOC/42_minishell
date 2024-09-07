/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   semicolon2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 12:52:43 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/07 14:48:53 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size_next_semicolon(t_data *data, int n_semi, char *str, int start)
{
	int	s_q;
	int	d_q;
	int	j;
	int	count;

	s_q = 0;
	d_q = 0;
	j = 0;
	count = 0;
	while (str[j] != 0)
	{
		if (str[j] == '\"' && s_q % 2 == 0 && (j == 0 || str[j - 1] != '\\'))
			d_q == 0;
		if (str[j] == '\'' && d_q % 2 == 0 && (j == 0 || str[j - 1] != '\\'))
			s_q == 0;
		if (str[j] == ';' && s_q % 2 == 0 && d_q % 2 == 0)
		{
			if (count == n_semi)
				return (j - start);
			count++;
		}
		j++;
	}
	return (j - start);
}

int	ft_copy_text(t_data *data, int size, int start, int semi_pos)
{
	int	i;
	int	j;
	char *str;
	
	i = start;
	j = 0;
	str = (char *) malloc ((size + 1) * sizeof (char));
	if (str == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	while (j < size)
		str[j++] = data->input_info_g->first_line_ref[i++];
	str[j] = 0;
	data->specific[semi_pos]->input_info->first_line_ref = str;
	return (SUCCESS);
}

int ft_split_semicolon(t_data *data)
{
	int	size;
	int tot_size;
	int	i;

	size = 0;
	i = 0;
	while (i <= data->n_semicolons)
	{
		size = ft_size_next_semicolon(data, i, data->input_info_g->first_line_ref, tot_size);
		if (ft_copy_text(data, size, tot_size, i) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		tot_size += size;
		i++;
	}
	i = 0;
	while (i <= data->n_semicolons)
	{
		ft_printf("AA:%s\n", data->specific[i]->input_info->first_line_ref);
	}
	return (SUCCESS);
}
