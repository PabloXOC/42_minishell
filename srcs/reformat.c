/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reformat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:39:06 by paxoc01           #+#    #+#             */
/*   Updated: 2024/07/03 16:34:04 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to make ft_make_new_string fit in 25 lines
static void	ft_ifs(char *input, char *output, int i, int j)
{
	if (input[j] == '<')
		ft_paste_char(output, " < ", i, 3);
	if (input[j] == '>')
		ft_paste_char(output, " > ", i, 3);
	if (input[j] == '|')
		ft_paste_char(output, " | ", i, 3);
}

static char	*ft_skip_quote_2(char *input, char *output, t_data *d)
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
	return (output);
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
	else if (input[d->j] == '\"')
		output = ft_skip_quote_2(input, output, d);
	return (output);
}

static char	*ft_make_new_string(char *input, char *output, t_data *d)
{
	while (input[++d->j] != 0)
	{
		output = ft_skip_quote(input, output, d);
		if ((input[d->j] == '<' && input[d->j + 1] == '<')
			|| (input[d->j] == '>' && input[d->j + 1] == '>'))
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
	output[d->i] = 0;
	return (output);
}

//reformat input
char	*ft_reformat_input(char *input, t_data *data)
{
	int		n_sep;
	char	*output;

	n_sep = ft_count_sep_char(input);
	output = (char *) malloc ((ft_strlen(input) + n_sep + 1) * sizeof(char));
	if (!output)
		return (ft_write_error_c(MALLOC_ERROR, data));
	output = ft_memset(output, 100, ft_strlen(input) + n_sep);
	output = ft_make_new_string(input, output, data);
	output[ft_strlen(input) + n_sep] = 0;
	return (output);
}
