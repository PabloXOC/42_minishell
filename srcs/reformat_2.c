/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reformat_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:28:35 by pximenez          #+#    #+#             */
/*   Updated: 2024/07/03 16:29:48 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//to make ft_count_sep_char fit in 25 lines
int	ft_count_sep_char_util(char *input, int i)
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
	return (i);
}

//find how many additional characters we are going to require
int	ft_count_sep_char(char *input)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (input[i] != 0)
	{
		i = ft_count_sep_char_util(input, i);
		if ((input[i] == '<' && input[i + 1] == '<')
			|| (input[i] == '>' && input[i + 1] == '>'))
		{
			count += 2;
			i += 2;
		}
		else if (input[i] == '<' || input[i] == '>' || input[i] == '|')
		{
			count += 2;
			i++;
		}
		else
			i++;
	}
	return (count);
}

//used to substitute "str" with " str "
char	*ft_paste_char(char *output, char *added, int pos, int size)
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