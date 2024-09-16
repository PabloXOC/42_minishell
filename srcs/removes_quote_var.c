/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removes_quote_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:52:30 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/16 16:30:19 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


int	ft_calc_size(char *old_str, int s_q, int d_q)
{
	int	len;
    int i;

	i = 0;
	len = 0;
	while (old_str[i] != 0)
	{
		if (old_str[i] == '\'' && d_q % 2 == 0 && (i == 0 || old_str[i - 1] != '\\'))
			s_q++;
		else if (old_str[i] == '\"' && s_q % 2 == 0 && (i == 0 || old_str[i - 1] != '\\'))
			d_q++;
		else if (old_str[i] == '\\' && d_q % 2 == 0)
		{
			if (old_str[i + 1] == '\'')
				i++;
			else if (old_str[i + 1] == '\"')
				i++;
		}
		i++;
		len++;
	}
	return (len);
}
static void	ft_new_string(char *old_str, char **new_str, int s_q, int d_q)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (old_str[i] != 0)
	{
		if (old_str[i] == '\'' && d_q % 2 == 0 && (i == 0 || old_str[i - 1] != '\\'))
			s_q++;
		else if (old_str[i] == '\"' && s_q % 2 == 0 && (i == 0 || old_str[i - 1] != '\\'))
			d_q++;
		else if (old_str[i] == '\\' && d_q % 2 == 0)
		{
			if (old_str[i + 1] == '\'')
				i++;
			else if (old_str[i + 1] == '\"')
				i++;
		}
		*(new_str)[j++] = old_str[i++];
	}
}

char *ft_remove_quotes_var(char **list, t_data *data)
{
	int i;
	int new_size;
	char *new_str;

	new_size = ft_calc_size(list[1], 0, 0);
	new_str = (char *) malloc ((new_size + 1) * sizeof (char));
	if (new_str == NULL)
		return (ft_write_error_c(MALLOC_ERROR, data, data->specific[data->sc_pos]));
	new_str[new_size] = 0;
	ft_new_string(list[1], &new_str, 0, 0);
	free(list[1]);
	return (new_str);
}