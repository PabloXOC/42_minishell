/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/06/26 18:06:08 by paxoc01          ###   ########.fr       */
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

//when we find a complete "first line", we save it to first_line variable and copy the contents
int	found_end_first_line(t_data *data, int i, char *input)
{
	data->input_info->first_line = (char *) malloc ((i + 1) * sizeof(char));
	if (data->input_info->first_line == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	ft_memcpy(data->input_info->first_line, input, i);
	data->input_info->first_line[i] = 0;
	data->input_info->terminal_input = init_terminal_input(data, input, i);
	if (data->input_info->terminal_input == NULL)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

//we determine if the "first line" is complete or we need more input from the user
int	first_line_complete(char *input, t_data *data, int n_double_q, int n_single_q)
{
	int	i;

	i = 0;
	while (input[i] != 0)
	{
		while (input[i] != '\n' || input[i] != '\0')
		{
			if (input[i] == '\\' && (input[i + 1] == '\'' || input[i + 1] == '\"'))
				i += 2;
			else if (input[i] == '\'' && n_double_q % 2 == 0)
				n_single_q++;
			else if (input[i] == '\"' && n_single_q % 2 == 0)
				n_double_q++;
			if (n_double_q % 2 == 0 && n_single_q % 2 == 0 //&& input[i] != '\\'
				&& (input[i] == '\n' || input[i] == '\0'))
			{
				if (found_end_first_line(data, i, input) == MALLOC_ERROR)
					return (MALLOC_ERROR);
				return (SUCCESS);
			}
			i++;
		}
		if (input[i] == '\n')
			i++;
	}
	return (FAILURE);
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
			if (ft_compare_eof(&data->input_info->terminal_input[i], data->input_info->list_eof[j], data))
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

int	ft_save_until_eof(t_data *data)
{
	int	len;
	int	i;
	int	j;
	int	k;

	len = ft_eofsize_total(data, 0, 0);
	j = 0;
	while ((data->input_info->list_eof[j]) != 0)
	{
		len -= (ft_strlen(data->input_info->list_eof[j]) + 1);
		j++;
	}
	data->input_info->final_text = (char *) malloc ((len) * sizeof (char));
	if (data->input_info->final_text == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	i = 1;
	j = 0;
	k = 0;
	while (k < len - 1)
	{
		if ((i == 1 || data->input_info->terminal_input[i - 1] == '\n')
			&& ft_compare_eof(&data->input_info->terminal_input[i], data->input_info->list_eof[j], data) == true)
		{
			i += ft_strlen(data->input_info->list_eof[j]) + 1;
			j++;
		}
		else
		{
			data->input_info->final_text[k] = data->input_info->terminal_input[i];
			i++;
			k++;
		}
	}
	data->input_info->final_text[k] = 0;
	return (SUCCESS);
}

int	ft_len_to_eof(t_data *data, t_input_var *input_info, int i, int k)
{
	int	len;

	len = 0;
	while (input_info->terminal_input[i] != 0)
	{
		if ((input_info->terminal_input[i - 1] == '\n' || len == 0) && ft_compare_eof_ind(&input_info->terminal_input[i],
			input_info->list_eof[k], data) == true)
			return (len);
		i++;
		len++;
	}
	return (len);
}

int	ft_save_last_eof(t_data *data, t_input_var *input_info, int i, int j)
{
	int	k;
	int	len;

	k = 0;
	if (input_info->n_eof == 0)
		return (SUCCESS);
	while (k + 1 < input_info->n_eof)
	{
		if ((input_info->terminal_input[i - 1] == '\n' || i == 0)
			&& ft_compare_eof(&input_info->terminal_input[i],
			input_info->list_eof[k], data) == true)
			k++;
		i++;
	}
	while (input_info->terminal_input[i - 1] != '\n')
		i++;
	len = ft_len_to_eof(data, input_info, i, k);
	input_info->final_text_last = (char *) malloc ((len + 1) * sizeof(char));
	if (input_info->final_text_last == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	while (j < len)
		input_info->final_text_last[j++] = input_info->terminal_input[i++];
	input_info->final_text_last[j] = 0;
	return (SUCCESS);
}

//if the input is not complete we ask the user for more input and join it to the initial input
int	ft_ask_user_for_more_input(t_data *data)
{
	char	*more_input;

	data->input_info->init_input = ft_join_input(data->input_info->init_input, "\n");
	if (data->input_info->init_input == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	more_input = readline("> ");
	if (more_input == NULL)
		return (ft_control_d());
	data->input_info->init_input = ft_strjoin(data->input_info->init_input, more_input);
	free(more_input);
	return (SUCCESS);
}

int	ft_combine_fl_ft(t_data *data)
{
	char	*str;
	char	*str_temp;

	str_temp = ft_strdup(data->input_info->first_line);
	str_temp = ft_join_input(str_temp, "\n");
	if (str_temp == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	str = ft_strjoin(str_temp, data->input_info->final_text);
	if (str == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	data->input_info->first_line_and_final_text = str;
	free(str_temp);
	return (SUCCESS);
}

int	ft_copy_until_eof(t_data *data, int i, int j)
{
	int		len;
	char	*str;

	len = ft_len_to_eof(data, data->input_info, data->kk, i);
	str = (char *) malloc ((len + 1) * sizeof (char));
	if (str == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	while (j < len)
	{
		str[j] = data->input_info->terminal_input[data->kk];
		j++;
		data->kk++;
	}
	str[len] = 0;
	data->input_info->text_input[i] = str;
	data->kk += ft_strlen(data->input_info->list_eof[i]) + 1;
	return (SUCCESS);
}
int	ft_individual_eof(t_data *data, int i)
{
	while (i < data->input_info->n_eof)
	{
		if (ft_copy_until_eof(data, i, 0) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		i++;
	}
	return (SUCCESS);
}

int	recieve_complete_input(t_data *data)
{
	if (init_input_struct(data) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (refresh_terminal_entry(data) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	data->input_info->init_input = readline(data->entry);
	if (data->input_info->init_input == NULL)
		return (ft_control_d());
	if (ft_empty(data->input_info->init_input) == true)//could be more precise (TO DO)
		return (EMPTY);
	while (first_line_complete(data->input_info->init_input, data, 0, 0) == FAILURE)
	{
		if (ft_ask_user_for_more_input(data) == MALLOC_ERROR)
			return (MALLOC_ERROR);
	}
	if (data->input_info->first_line == NULL)
		return (MALLOC_ERROR);
	data->input_info->first_line_ref = ft_reformat_input(data->input_info->first_line, data);
	if (data->input_info->first_line_ref == NULL)
		return (MALLOC_ERROR);
	if (ft_check_token(data) == INVALID_TOKEN)
		return (INVALID_TOKEN);
	if (ft_terminal_input(data, 0, 0) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (ft_save_until_eof(data) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (ft_individual_eof(data, 0) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (ft_save_last_eof(data, data->input_info, 0, 0) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	if (ft_combine_fl_ft(data) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (SUCCESS);
}
