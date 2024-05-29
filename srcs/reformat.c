/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reformat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:39:06 by paxoc01           #+#    #+#             */
/*   Updated: 2024/05/24 11:26:13 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_count_sep_char(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i] != 0)
	{
		if (input[i] == '\'')
		{
			i++;
			while (input[i] != '\'')
				i++;
		}
		if (input[i] == '\"')
		{
			i++;
			while (input[i] != '\"')
				i++;
		}
		if ((input[i] == '<' && input[i + 1] == '<') || (input[i] == '>' && input[i + 1] == '>'))
		{
			count +=2;
			i +=2;
		}
		else if (input[i] == '<' || input[i] == '>' || input[i] == '|')
		{
			count +=2;
			i++;
		}
		else
			i++;
	}
	return (count);
}

static char	*ft_paste_char(char *output, char *added, int pos, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		output[pos + i] = added[i];
		i++;
	}
	return (output);
}

static void	ft_ifs(char *input, char *output, int i, int j)
{
	if (input[j] == '<')
		ft_paste_char(output, " < ", i, 3);
	if (input[j] == '>')
		ft_paste_char(output, " > ", i, 3);
	if (input[j] == '|')
		ft_paste_char(output, " | ", i, 3);
}

static char	*ft_skip_quote(char *input, char *output, t_data *d)
{
	if (input[d->j] == '\'')
	{
		output[d->i] = input[d->j];
		d->i++;
		d->j++;
		while (input[d->j] != '\'')
		{
			output[d->i] = input[d->j];
			d->i++;
			d->j++;
		}
		output[d->i] = input[d->j];
	}
	if (input[d->j] == '\"')
	{
		output[d->i] = input[d->j];
		d->i++;
		d->j++;
		while (input[d->j] != '\"')
		{
			output[d->i] = input[d->j];
			d->i++;
			d->j++;
		}
		output[d->i] = input[d->j];
	}
	return (output);
}
static char	*ft_make_new_string(char *input,char *output, t_data *d)
{
	while (input[++d->j] != 0)
	{
		output = ft_skip_quote(input, output, d);
		if ((input[d->j] == '<' && input[d->j + 1] == '<') || (input[d->j] == '>' && input[d->j + 1] == '>'))
		{
			if (input[d->j] == '<')
				ft_paste_char(output, " << ", d->i, 4);
			else
				ft_paste_char(output, " >> ", d->i, 4);
			d->i += 3;
			d->j += 1;
		}
		else if (input[d->j] == '<' || input[d->j] == '>' || input[d->j] == '|')
		{
			ft_ifs(input, output, d->i, d->j);
			d->i += 2;
		}
		else
			output[d->i] = input[d->j];
		d->i++;
	}
	return (output);
}

int	ft_count_bars(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\\' && str[i + 1] == '\\')
		{
			i += 2;
			count +=2;
		}
		else if (str[i] == '\\')
		{
			i += 1;
			count += 1;
		}
		else
			i++;
	}
	return (count);
}

char	*ft_reformat_input(char *input, t_data *data)
{
	int		n_sep;
	char	*output;
	
	n_sep = ft_count_sep_char(input);
	//n_sep -= ft_count_bars(input);
	output = (char *) malloc ((ft_strlen(input) + n_sep + 1) * sizeof(char));
	if (!output)
		return ((ft_write_error_c(MALLOC_ERROR, data)));
	output = ft_memset(output, 100, ft_strlen(input) + n_sep);
	output = ft_make_new_string(input, output, data);
	//free(input);
	return (output);
}
