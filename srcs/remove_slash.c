/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_slash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:51:29 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/07 15:05:55 by paxoc01          ###   ########.fr       */
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
	return (len);
}

int	ft_handle_d_quote(t_data *data, char *old_str)
{
	int	len;

	data->v->jj++;
	len = 0;
	while (old_str[data->v->jj] != '\"' && old_str[data->v->jj != 0])
	{
		if (old_str[data->v->jj] == '\\' && (old_str[data->v->jj + 1] == '\\'
				|| old_str[data->v->jj + 1] == '\"'))
			data->v->jj += 2;
		else
			data->v->jj++;
		len++;
	}
	if (old_str[data->v->jj] == '\"')
		data->v->jj++;
	return (len);
}

int	ft_paste_s_quote(t_data *d, char *old_str, char **str, int i)
{
	d->v->jj++;
	while (old_str[d->v->jj] != '\'' && old_str[d->v->jj != 0])
		(*str)[i++] = old_str[d->v->jj++];
	if (old_str[d->v->jj] == '\'')
		d->v->jj++;
	return (i);
}

int	ft_paste_d_quote(t_data *d, char *old_str, char **str, int i)
{
	d->v->jj++;
	while (old_str[d->v->jj] != '\"' && old_str[d->v->jj != 0])
	{
		if (old_str[d->v->jj] == '\\' && (old_str[d->v->jj + 1] == '\\'
				|| old_str[d->v->jj + 1] == '\"'))
		{
			(*str)[i++] = old_str[d->v->jj];
			d->v->jj += 2;
		}
		else
			(*str)[i++] = old_str[d->v->jj++];
	}
	if (old_str[d->v->jj] == '\"')
		d->v->jj++;
	return (i);
}

int	size_removing_slash(t_data *d, char *old_str)
{
	int	len;

	d->v->jj = 0;
	len = 0;
	while (old_str[d->v->jj] != 0)
	{
		if (old_str[d->v->jj] == '\'')
			len += ft_handle_s_quote(d, old_str);
		else if (old_str[d->v->jj] == '\"')
			len += ft_handle_d_quote(d, old_str);
		else if (old_str[d->v->jj] == '\\')
		{
			len++;
			d->v->jj += 2;
		}
		else
		{
			d->v->jj++;
			len++;
		}
	}
	return (len);
}

char	*ft_new_string(t_data *data, int len, char *old_str, int i)
{
	char	*str;

	str = (char *) malloc ((len + 1) * sizeof(char));
	if (str == NULL)
		return (ft_write_error_c(MALLOC_ERROR, data->v->data, data->specific[data->n_semicolons]));
	data->v->jj = 0;
	while (data->v->jj < len)
	{
		if (old_str[data->v->jj] == '\'')
			i = ft_paste_s_quote(data, old_str, &str, i);
		else if (old_str[data->v->jj] == '\"')
			i = ft_paste_d_quote(data, old_str, &str, i);
		else if (old_str[data->v->jj] == '\\')
		{
			str[i++] = old_str[data->v->jj + 1];
			data->v->jj += 2;
		}
		else
			str[i++] = old_str[data->v->jj++];
	}
	str[len] = 0;
	return (str);
}

int	ft_reformat_slash(t_data *data, t_input_var *info)
{
	int		i;
	int		len;
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
		len = size_removing_slash(data, info->first_line_split[i]);
		new_split[i] = ft_new_string(data, len, info->first_line_split[i], 0);
		if (new_split[i] == NULL)
			return (MALLOC_ERROR);
		i++;
	}
	new_split[i] = 0;
	info->first_line_split = new_split;
	return (SUCCESS);
}
