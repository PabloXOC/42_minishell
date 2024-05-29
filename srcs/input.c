/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/05/29 17:11:51 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data_init(void)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof (t_data));
	if (data == NULL)
		return ((t_data *) ft_write_error_c(MALLOC_ERROR, data));
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
	data->first_line = NULL;
	data->first_line_ref = NULL;
	data->i = 0;
	data->j = -1;
	return (data);
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

/* bool ft_quotes_not_paired(char *input, t_data *data)
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
} */

/* bool ft_input_required(char *input, t_data *data)
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
} */

int	first_line_complete(char *input, t_data *data)
{
	int	i;
	int	num_single_quote;
	int	num_double_quote;

	num_single_quote = 0;
	num_double_quote = 0;
	i = 0;
	while (input[i] != 0)
	{
		while (input[i] != '\n' || input[i] != '\0')
		{
			if (input[i] == '\\' && (input[i + 1] == '\'' || input[i + 1] == '\"'))
				i += 2;
			else if (input[i] == '\'' && num_double_quote % 2 == 0)
				num_single_quote++;
			else if (input[i] == '\"' && num_single_quote % 2 == 0)
				num_double_quote++;
			if (num_double_quote % 2 == 0 && num_single_quote % 2 == 0 && input[i] != '\\'
				&& (input[i + 1] == '\n' || input[i + 1] == '\0'))
			{
				data->first_line = (char *) malloc ((i + 2) * sizeof(char));
				if (data->first_line == NULL)
					return (ft_write_error_i(MALLOC_ERROR, data));
				ft_memcpy(data->first_line, input, i + 1);
				data->first_line[i + 2] = 0;
				if (input[i + 1] != '\0')
					data->terminal_input = &input[i + 2];
				else
					data->terminal_input = &input[i + 1];
				return (SUCCESS);
			}
			i++;
		}
		if (input[i] == '\n')
			i++;
	}
	return (FAILURE);
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

static bool ft_found_io(char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '<')
		return (true);
	if (str[i] == '<' && str[i + 1] == ' ')
		return (true);
	if (str[i] == '>' && str[i + 1] == '>')
		return (true);
	if (str[i] == '>' && str[i + 1] == ' ')
		return (true);
	return (false);
}

static bool ft_found_ter_input(char *str, int i)
{
	if (str[i] == '<' && str[i + 1] == '<')
		return (true);
	return (false);
}

static bool ft_bad_token(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	if (str[i] == '\n')
		return (true);
	if (str[i] == '\0')
		return (true);
	if (str[i] == '|')
		return (true);
	if (str[i] == '<' && str[i + 1] == '<')
		return (true);
	if (str[i] == '<' && str[i + 1] == ' ')
		return (true);
	if (str[i] == '>' && str[i + 1] == '>')
		return (true);
	if (str[i] == '>' && str[i + 1] == ' ')
		return (true);
	return (false);
}

int	ft_skip_quote(char *str, int i, char c)
{
	i++;
	while (str[i] != c)
	{
		if (str[i] == '\0')
			return (i);
		i++;
	}
	i++;
	return (i);
}

int	ft_check_token(t_data *data)
{
	int	i;

	i = 0;
	while (data->first_line_ref[i] != '\0')
	{
		if (data->first_line_ref[i] == '\'' || data->first_line_ref[i] == '\"')
			i = ft_skip_quote(data->first_line_ref, i, data->first_line_ref[i]);
		if (data->first_line_ref[i] == '\0')
			break ;
		if (ft_found_io(data->first_line_ref, i) == true)
		{
			i +=2;
			if (ft_bad_token(data->first_line_ref, i) == true)
				return (INVALID_TOKEN);
		}
		i++;
	}
	return (SUCCESS);
}

static bool	ft_quote_switch(char *str, int i, bool single_q, bool double_q)
{
	if (str[i] == '\'' && single_q == false)
		return (true);
	else if (str[i] == '\'' && single_q == true)
		return (false);
	else if (str[i] == '\"' &&double_q == false)
		return (true);
	else if (str[i] == '\"' && double_q == true)
		return (false);
	return (false);
}

int	ft_eofsize(char *str, int i, bool single_q, bool double_q)
{
	int		size;

	size = 0;
	while ((((single_q == true || double_q == true) || (single_q == false
		&& double_q == false && str[i] != ' '))) && str[i] != 0)
	{
		if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
		{
			i++;
			size++;
		}
		else if (str[i] == '\'' && double_q == false)
			single_q = ft_quote_switch(str, i, single_q, double_q);
		else if (str[i] == '\"' && single_q == false)
			double_q = ft_quote_switch(str, i, single_q, double_q);
		else
		{
			size++;
		}
		i++;
	}
	return (size);
}

static char	*ft_write_eof(char *str, char *eof, int size, int i)
{
	int	j;
	bool	single_q;
	bool	double_q;

	single_q = false;
	double_q = false;
	j = 0;
	while (j < size && str[i] != '\0')
	{

		if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
		{
			eof[j++] = str[i + 1];
			i += 2;
		}
		else if (str[i] == '\'' && double_q == false)
			single_q = ft_quote_switch(str, i, single_q, double_q);
		else if (str[i] == '\"' && single_q == false)
			double_q = ft_quote_switch(str, i, single_q, double_q);
		else
			eof[j++] = str[i];
		i++;
	}
	eof[j] = 0;
	return (eof);
}

char	*ft_find_eof(char *str, int i, t_data *data)
{
	int		j;
	int		size;
	char	*eof;

	while (str[i] == ' ')
		i++;
	size = ft_eofsize(str, i, false, false);
	eof = (char *) malloc ((size + 1) * sizeof(char));
	if (eof == NULL)
		return (ft_write_error_c(MALLOC_ERROR, data));
	ft_write_eof(str, eof, size, i);
	return (eof);
}

bool	ft_compare_eof(char *str, char *eof, t_data *data)
{
	int	size;
	int	i;

	i = 0;
	size = ft_strlen(eof);
	while (i < size && str[i] != 0 && str[i] != ' \n')
	{
		if (str[i] != eof[i])
			return (false);
		i++;
	}
	if (i != size)
		return (false);
	if (str[i] == '\n')
	{
		
	}
}

int	ft_get_ter_input(t_data *data, char *eof)
{
	int	i;
	char *str;

	str = data->terminal_input;
	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\n' && str[i] == '\0')
		{
			if (ft_compare_eof(&str[i + 1], eof, data) == true)
			{
				
			}
		}
	}
}

int	ft_ter_input(t_data *data, int num_single_quote, int num_double_quote)
{
	int	i;
	char	*f_line;
	char	*eof;

	f_line = data->first_line_ref;
	i = 0;
	while (f_line[i] != 0)
	{
		if (f_line[i] == '\\' && (f_line[i + 1] == '\'' || f_line[i + 1] == '\"'))
			i += 2;
		else if (f_line[i] == '\'' && num_double_quote % 2 == 0)
			num_single_quote++;
		else if (f_line[i] == '\"' && num_single_quote % 2 == 0)
			num_double_quote++;
		if (num_double_quote % 2 == 0 && num_single_quote % 2 == 0)
		{
			if (f_line[i] == '<' && f_line[i + 1] == '<')
			{
				eof = ft_find_eof(f_line, i + 2, data);
				ft_get_ter_input(data, eof);
				ft_printf("%s\n", eof);
				i += 2;
			}
		}
		i++;
	}
}

int	recieve_complete_input(t_data *data)
{
	char	*more_input;
	char	*joined_input;
	char	*temp_input;

	data->input = readline(data->entry);
	if (ft_empty(data->input) == true)
		return (EMPTY);
	while (first_line_complete(data->input, data) == FAILURE)
	{
		data->input = ft_join_input(data->input, "\n");
		if (data->input == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
		more_input = readline("> ");
		data->input = ft_strjoin(data->input, more_input);
		free(more_input);
	}
	if (data->first_line == NULL)
		return (MALLOC_ERROR);
	data->first_line_ref = ft_reformat_input(data->first_line, data);
	if (data->first_line_ref == NULL)
		return (MALLOC_ERROR);
	if (ft_check_token(data) == INVALID_TOKEN)
		return (INVALID_TOKEN);
	if (ft_ter_input(data, 0, 0) == MALLOC_ERROR)
		return (MALLOC_ERROR);
	return (SUCCESS);
}
