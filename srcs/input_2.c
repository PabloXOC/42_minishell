/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 11:45:40 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/01 15:31:08 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*init_terminal_input(t_data *data, char *input, int i)
{
	char	*terminal_input;
	int		size;
	int		j;

	size = ft_strlen(&input[i]);
	terminal_input = (char *) malloc ((size + 1) * sizeof(char));
	if (terminal_input == NULL)
		return (ft_write_error_c(MALLOC_ERROR, data));
	j = 0;
	while (input[i] != 0)
	{
		terminal_input[j] = input[i];
		i++;
		j++;
	}
	terminal_input[j] = 0;
	return (terminal_input);
}

int	first_line_complete_2(t_data *data, int i, int d_q, int s_q)
{
	char	*input;

	input = data->input_info->init_input;
	if (d_q % 2 == 0 && s_q % 2 == 0)
	{
		if (found_end_first_line(data, i, input) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		return (SUCCESS);
	}
	else if (d_q % 2 == 0)
		data->quote = '\'';
	else
		data->quote = '\"';
	return (FAILURE);
}

int	first_line_complete(char *input, t_data *data, int d_q, int s_q)
{
	int	i;

	i = -1;
	while (input[++i] != 0)
	{
		if (input[i] == '\\' && (input[i + 1] == '\'' || input[i + 1] == '\"'))
			i++;
		else if (input[i] == '\'' && d_q % 2 == 0)
			s_q++;
		else if (input[i] == '\"' && s_q % 2 == 0)
			d_q++;
		if (d_q % 2 == 0 && s_q % 2 == 0 && input[i] == '\n')
		{
			if (found_end_first_line(data, i, input) == MALLOC_ERROR)
				return (MALLOC_ERROR);
			return (SUCCESS);
		}
	}
	return (first_line_complete_2(data, i, d_q, s_q));
}

//ft_strjoin with a free for s1
char	*ft_join_input(char *s1, char *s2)
{
	char	*str;
	int		len_1;
	int		len_2;

	if (s1 != NULL)
		len_1 = ft_strlen(s1);
	else
		len_1 = 0;
	if (s2 != NULL)
		len_2 = ft_strlen(s2);
	else
		len_2 = 0;
	str = ft_calloc(len_1 + len_2 + 1, 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1, len_1);
	ft_memcpy(&str[len_1], s2, len_2);
	str[len_1 + len_2] = 0;
	if (s1 != NULL)
		free(s1);
	return (str);
}

int	ft_eofsize_total(t_data *data, int i, int j)
{
	bool	found;

	while (data->input_info->list_eof[j] != 0)
	{
		found = false;
		while (found == false)
		{
			if (data->input_info->terminal_input[i] == '\n')
				i++;
			if (ft_compare_eof(&data->input_info->terminal_input[i],
					data->input_info->list_eof[j], data))
			{
				found = true;
				i += ft_strlen(data->input_info->list_eof[j]);
			}
			else if (data->input_info->terminal_input[i] != '\n')
			{
				i++;
				while (data->input_info->terminal_input[i] != '\n')
					i++;
			}
		}
		j++;
	}
	return (i);
}
