/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_slash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:51:29 by pximenez          #+#    #+#             */
/*   Updated: 2024/07/04 18:28:27 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_s_quote(t_data *d, char *old_str)
{
	int	len;

	d->jj++;
	len = 0;
	while (old_str[d->jj] != '\'' && old_str[d->jj != 0])
	{
		d->jj++;
		len++;
	}
	if (old_str[d->jj] == '\'')
		d->jj++;
	return (len);
}

int	ft_handle_d_quote(t_data *d, char *old_str)
{
	int	len;

	d->jj++;
	len = 0;
	while (old_str[d->jj] != '\"' && old_str[d->jj != 0])
	{
		if (old_str[d->jj] == '\\' && (old_str[d->jj + 1] == '\\'
				|| old_str[d->jj + 1] == '\"'))
			d->jj += 2;
		else
			d->jj++;
		len++;
	}
	if (old_str[d->jj] == '\"')
		d->jj++;
	return (len);
}

int	ft_paste_s_quote(t_data *d, char *old_str, char **str, int i)
{
	d->jj++;
	while (old_str[d->jj] != '\'' && old_str[d->jj != 0])
		(*str)[i++] = old_str[d->jj++];
	if (old_str[d->jj] == '\'')
		d->jj++;
	return (i);
}

int	ft_paste_d_quote(t_data *d, char *old_str, char **str, int i)
{
	d->jj++;
	while (old_str[d->jj] != '\"' && old_str[d->jj != 0])
	{
		if (old_str[d->jj] == '\\' && (old_str[d->jj + 1] == '\\'
				|| old_str[d->jj + 1] == '\"'))
		{
			(*str)[i++] = old_str[d->jj];
			d->jj += 2;
		}
		else
			(*str)[i++] = old_str[d->jj++];
	}
	if (old_str[d->jj] == '\"')
		d->jj++;
	return (i);
}

int	size_removing_slash(t_data *d, char *old_str)
{
	int	len;

	d->jj = 0;
	len = 0;
	while (old_str[d->jj] != 0)
	{
		if (old_str[d->jj] == '\'')
			len += ft_handle_s_quote(d, old_str);
		else if (old_str[d->jj] == '\"')
			len += ft_handle_d_quote(d, old_str);
		else if (old_str[d->jj] == '\\')
		{
			len++;
			d->jj += 2;
		}
		else
		{
			d->jj++;
			len++;
		}
	}
	return (len);
}

char	*ft_new_string(t_data *d, int len, char *old_str, int i)
{
	char	*str;

	str = (char *) malloc ((len + 1) * sizeof(char));
	if (str == NULL)
		return (ft_write_error_c(MALLOC_ERROR, d));
	d->jj = 0;
	while (d->jj < len)
	{
		if (old_str[d->jj] == '\'')
			i = ft_paste_s_quote(d, old_str, &str, i);
		else if (old_str[d->jj] == '\"')
			i = ft_paste_d_quote(d, old_str, &str, i);
		else if (old_str[d->jj] == '\\')
		{
			str[i++] = old_str[d->jj + 1];
			d->jj += 2;
		}
		else
			str[i++] = old_str[d->jj++];
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
	while (data->input_info->first_line_split[i] != 0)
		i++;
	new_split = (char **) malloc ((i + 1) * sizeof(char *));
	if (new_split == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	i = 0;
	while (data->input_info->first_line_split[i] != 0)
	{
		len = size_removing_slash(data, data->input_info->first_line_split[i]);
		new_split[i] = ft_new_string(data, len, info->first_line_split[i], 0);
		if (new_split[i] == NULL)
			return (MALLOC_ERROR);
		i++;
	}
	new_split[i] = 0;
	data->input_info->first_line_split = new_split;
	return (SUCCESS);
}
