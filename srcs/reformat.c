/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reformat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:39:06 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/27 14:09:19 by paxoc01          ###   ########.fr       */
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

static char	*ft_skip_quote(char *input, char *output, t_data *d)
{
	if ((d->v->j == 0 || input[d->v->j - 1] != '\\') && input[d->v->j] == '\'')
	{
		output[d->v->i++] = input[d->v->j++];
		while (input[d->v->j] != '\''
			|| (input[d->v->j] == '\'' && input[d->v->j - 1] == '\\'))
			output[d->v->i++] = input[d->v->j++];
		output[d->v->i] = input[d->v->j];
	}
	if ((d->v->j == 0 || input[d->v->j - 1] != '\\') && input[d->v->j] == '\"')
	{
		output[d->v->i++] = input[d->v->j++];
		while (input[d->v->j] != '\"'
			|| (input[d->v->j] == '\"' && input[d->v->j - 1] == '\\'))
			output[d->v->i++] = input[d->v->j++];
		output[d->v->i] = input[d->v->j];
	}
	return (output);
}

static char	*ft_fill_new_string(char *input, char *output, t_data *d)
{
	while (input[++d->v->j] != 0)
	{
		output = ft_skip_quote(input, output, d);
		if ((input[d->v->j] == '<' || input[d->v->j] == '>'
				|| input[d->v->j] == '|') && input[d->v->j - 1] == '\\')
			output[d->v->i] = input[d->v->j];
		else if ((input[d->v->j] == '<' && input[d->v->j + 1] == '<')
			|| (input[d->v->j] == '>' && input[d->v->j + 1] == '>'))
			ft_fill_new_string2(input, output, d);
		else if (input[d->v->j] == '<' || input[d->v->j] == '>'
			|| input[d->v->j] == '|')
		{
			ft_ifs(input, output, d->v->i, d->v->j);
			d->v->i += 2;
		}
		else
			output[d->v->i] = input[d->v->j];
		d->v->i++;
	}
	return (output);
}

//reformat input
char	*ft_reformat_input(char *input, t_data *data)
{
	int		n_sep;
	int		len;
	char	*output;

	n_sep = ft_count_sep_char(input, 0, 0);
	len = ft_strlen(input);
	output = (char *) malloc ((len + n_sep + 1) * sizeof(char));
	if (!output)
		return (error_c(MALLOC_ERROR, data, data->spec[data->sc_n]));
	output = ft_fill_new_string(input, output, data);
	output[len + n_sep] = 0;
	return (output);
}
