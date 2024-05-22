/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/05/22 15:08:42 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data_init(void)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof (t_data));
	if (data == NULL)
		return (ft_write_error_c(MALLOC_ERROR, data));
	data->input_split = NULL;
	data->input = NULL;
	data->paired = 0;
	data->exit = false;
	data->user = NULL;
	data->hostname = NULL;
	data->dir = NULL;
	data->entry = NULL;
	data->command_list = NULL;
	data->redirect_input = NULL;
	data->redirect_output = NULL;
	data->limiter = NULL;
	data->append_output = false;
	data->var = NULL;
	data->var_export = NULL;
	data->text_input = NULL;
	data->text_input = NULL;
	data->next_eof = NULL;
	data->malloc_error = false;
	data->input_index = 0;
	data->eof_index = 0;
	return (data);
}

int	ft_pair(char *input, char c, int i, t_data *data)
{
	while (input[i] != 0)
	{
		if (input[i] == c)
		{
			data->paired = 2;
			i++;
			break ;
		}
		i++;
	}
	return (i);
}


//give the string, finds the first word
char	*return_eof(char *input)
{
	size_t	len;
	char	*eof;

	len = 0;
	while (input[len] != 32 && input[len] != 0 && input[len] != '\n' && input[len] != '<' && input[len] != '>' && input[len] != '|')
		len++;
	eof = (char *)malloc((len + 1) * sizeof(char));
	if (eof == NULL)
		return (NULL);
	eof[len] = 0;
	ft_memcpy(eof, input, len);
	return (eof);
}

bool	eof_not_found(int i, t_data *data)
{
	char	*eof;
	char	*input;

	input = data->input;
	while (input[i] == 32 && input[i] != 0)
		i++;
	ft_printf("EOFINPUT:%sAAA\n",&input[i]);
	eof = return_eof(&input[i]);
	if (data->input_index != 0)
		i = data->input_index;
	while (input[i] != 0)
	{
		if (input[i] == '\n')
		{
			i++;
			ft_printf("comp:%sAA\n", &input[i]);
			ft_printf("eof:%sAA\n", eof);
			if (ft_memcmp(eof, &input[i], ft_strlen(eof)) == 0 && ('\0' == input[i + ft_strlen(eof)] || '\n' == input[i + ft_strlen(eof)]))
			{
				data->input_index = i + ft_strlen(eof);
				free(eof);
				return (false);
			}
		}
		i++;
	}
	free(eof);
	return (true);
}

bool ft_quotes_not_paired(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i] != 0)
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			data->paired = 1;
			i = ft_pair(input, input[i], i + 1, data);
			if (data->paired == 1)
			{
				data->paired = 0;
				return (true);
			}
		}
		i++;
	}
	return (false);
}

int	ft_ignore_quotes(char *input, int i, int quote)
{
	while (input[i] != 0 && input[i] != quote)
		i++;
	if (input[i] != 0)
		i++;
	return (i);
}

bool ft_backslash_not_paired(char *input, t_data *data)
{
	int	i;
	int	num_of_bs;

	i = 0;
	num_of_bs = 0;
	while (input[i] != 0)
	{
		if (input[i] == '"' || input[i] == '\'')
			i = ft_ignore_quotes(&input[i], i + 1, input[i]);
		while (input[i] == '\\')
		{
			num_of_bs++;
			i++;
		}
		if (num_of_bs % 2 != 0 && input[i] == 0)
			return (true);
		num_of_bs = 0;
		i++;
	}
	return (false);
}

bool ft_input_required(char *input, t_data *data)
{
	int	i;

	i = data->eof_index;
	while (input[i] != 0)
	{
		if (input[i] == '"' || input[i] == '\'')
			i = ft_ignore_quotes(&input[i], i + 1, input[i]);
		if (input[i] == '<' && input[i + 1] == '<')
		{
			if (eof_not_found(i + 2, data) == true)
			{
				data->eof_index = i + 2;
				return (true);
			}
			i = i + 2;
		}
		i++;
	}
	return (false);
}

bool	ft_not_complete(char *input, t_data *data)
{
	if (ft_quotes_not_paired(input, data) == true) //works
		return (true);
	if (ft_backslash_not_paired(input, data) == true) //works
		return (true);
	while (ft_input_required(input, data) == true)
		return (true);
	data->input_index = 0;
	data->eof_index = 0;

	return (false);
}

char	*ft_join_input(char *s1, char *s2)
{
	char	*str;
	int		len_1;
	int		len_2;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	str = ft_calloc(len_1 + len_2 + 1, 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1, len_1);
	ft_memcpy(&str[len_1], s2, len_2);
	str[len_1 + len_2] = 0;
	free(s1);
	return (str);
}

int	recieve_complete_input(t_data *data)
{
	char	*more_input;
	char	*joined_input;
	char	*temp_input;

	if (ft_empty(data->input) == true)
		return (EMPTY);
	while (ft_not_complete(data->input, data) == true)
	{
		data->input = ft_join_input(data->input, "\n");
		if (data->input == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
		more_input = readline("> ");
		data->input = ft_strjoin(data->input, more_input);
		free(more_input);
	}
	data->input_split = ft_split(data->input, ' ');
	if (data->input_split == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	return (SUCCESS);
}