/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reformat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 15:39:06 by paxoc01           #+#    #+#             */
/*   Updated: 2024/05/04 14:14:22 by paxoc01          ###   ########.fr       */
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

static char	*ft_make_new_string(char *input,char *output, int i, int j)
{
	while (input[++j] != 0)
	{
/* 		if (input[j] == '\\' && input[j + 1] == '\\')
		{
			j++;
			ft_paste_char(output, "\\", i, 1);
		}
		else if (input[j] == '\\')
			i--;  */
		if ((input[j] == '<' && input[j + 1] == '<') || (input[j] == '>' && input[j + 1] == '>'))
		{
			if (input[j] == '<')
				ft_paste_char(output, " << ", i, 4);
			else
				ft_paste_char(output, " >> ", i, 4);
			i += 3;
			j += 1;
		}
		else if (input[j] == '<' || input[j] == '>' || input[j] == '|')
		{
			ft_ifs(input, output, i, j);
			i += 2;
		}
		else
			output[i] = input[j];
		i++;
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
	output = ft_make_new_string(input, output, 0, -1);
	free(input);
	return (output);
}
