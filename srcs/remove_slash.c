/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_slash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:51:29 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/16 16:00:04 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_s_quote(t_data *data, char *old_str)
{
	int	len;

	data->v->jj++;
	len = 0;
	while (old_str[data->v->jj] != '\'' && old_str[data->v->jj != 0])
	{
		data->v->jj++;
		len++;
	}
	if (old_str[data->v->jj] == '\'')
		data->v->jj++;
	return (len + 2);
}

int	ft_handle_d_quote(t_data *data, char *old_str)
{
	int	len;

	data->v->jj++;
	len = 0;
	while (old_str[data->v->jj] != '\"' && old_str[data->v->jj != 0]
		&& (data->v->jj == 0 || old_str[data->v->jj - 1] == '\\'))
	{
		if (old_str[data->v->jj] == '\\' && (ft_isalnum(old_str[data->v->jj + 1]) == 0))
			data->v->jj += 2;
		else
			data->v->jj++;
		len++;
	}
	if (old_str[data->v->jj] == '\"')
		data->v->jj++;
	return (len + 2);
}

int	ft_paste_s_quote(t_data *d, char *old_str, char **str, int i)
{
	(*str)[i++] = old_str[d->v->jj++];
	while (old_str[d->v->jj] != '\'' && old_str[d->v->jj != 0]
		&& (d->v->jj == 0 || old_str[d->v->jj - 1] == '\\'))
		(*str)[i++] = old_str[d->v->jj++];
	if (old_str[d->v->jj] == '\'')
		(*str)[i++] = old_str[d->v->jj++];
	return (i);
}

int	ft_paste_d_quote(t_data *d, char *old_str, char **str, int i)
{
	(*str)[i++] = old_str[d->v->jj++];
	while (old_str[d->v->jj] != '\"' && old_str[d->v->jj] != 0)
	{
		if (old_str[d->v->jj] == '\\' && (ft_isalnum(old_str[d->v->jj + 1]) == 0))
		{
			(*str)[i++] = old_str[d->v->jj + 1];
			d->v->jj += 2;
		}
		else
			(*str)[i++] = old_str[d->v->jj++];
	}
	if (old_str[d->v->jj] == '\"')
		(*str)[i++] = old_str[d->v->jj++];
	return (i);
}

int	size_removing_slash(t_data *d, char *old_str, int s_q, int d_q)
{
	int	len;

	d->v->jj = 0;
	len = 0;
	while (old_str[d->v->jj] != 0)
	{
		if (old_str[d->v->jj] == '\'' && d_q % 2 == 0 && (d->v->jj == 0 || old_str[d->v->jj - 1] != '\\'))
			len += ft_handle_s_quote(d, old_str);
		else if (old_str[d->v->jj] == '\"' && s_q % 2 == 0 && (d->v->jj == 0 || old_str[d->v->jj - 1] != '\\'))
			len += ft_handle_d_quote(d, old_str);
		else if (old_str[d->v->jj] == '\\' && s_q % 2 == 0 && d_q % 2 == 0)
		{
			d->v->jj += 2;
			len++;
		}
		else
		{
			d->v->jj++;
			len++;
		}
	}
	return (len);
}
static char	*ft_new_string(t_data *d, char *old_str, int s_q, int d_q)
{
	char	*str;
	int		len;
	int		pos;

	len = size_removing_slash(d, old_str, 0, 0);
	str = (char *) malloc ((len + 1) * sizeof(char));
	if (str == NULL)
		return (ft_write_error_c(MALLOC_ERROR, d, d->specific[d->sc_pos]));
	d->v->jj = 0;
	pos = 0;
	while (old_str[d->v->jj] != 0)
	{
		if (old_str[d->v->jj] == '\'' && d_q % 2 == 0 && (d->v->jj == 0 || old_str[d->v->jj - 1] != '\\'))
			pos = ft_paste_s_quote(d, old_str, &str, pos);
		else if (old_str[d->v->jj] == '\"' && s_q % 2 == 0 && (d->v->jj == 0 || old_str[d->v->jj - 1] != '\\'))
			pos = ft_paste_d_quote(d, old_str, &str, pos);
		else if (old_str[d->v->jj] == '\\' && s_q % 2 == 0 && d_q % 2 == 0)
			d->v->jj++;
		str[pos] = old_str[d->v->jj];
		d->v->jj++;
		pos++;
	}
	str[len] = 0;
	return (str);
}

int	ft_reformat_slash(t_data *data, t_input_var *info)
{
	int		i;
	char	**new_split;

	i = 0;
	while (info->first_line_split[i] != 0)
		i++;
	new_split = (char **) malloc ((i + 1) * sizeof(char *));
	if (new_split == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	i = 0;
	while (info->first_line_split[i] != 0)
	{
		new_split[i] = ft_new_string(data, info->first_line_split[i], 0, 0);
		if (new_split[i] == NULL)
			return (MALLOC_ERROR);
		//free(info->first_line_split[i]);
		i++;
	}
	new_split[i] = 0;
	//free(info->first_line_split);
	info->first_line_split_ref = new_split;
	return (SUCCESS);
}
