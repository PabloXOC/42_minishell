/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_slash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:51:29 by pximenez          #+#    #+#             */
/*   Updated: 2024/07/03 14:12:12 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	size_removing_slash(char *old_str)
{
	int	len;
	int	i;

	i = 0;
	while (old_str[i] != 0)
	{
		if (old_str[i] == '\\' && old_str[i + 1] == '\\')
		{
			len++;
			i += 2;
		}
		else if (old_str[i] == '\\')
			i++;
		else
		{
			i++;
			len++;
		}
	}
	return (len);
}

char	*ft_new_string(t_data *data, int len, char *old_str, int i)
{
	char	*str;
	int		j;

	str = (char *) malloc ((len + 1) * sizeof(char));
	if (str == NULL)
		return (ft_write_error_c(MALLOC_ERROR, data));
	j = 0;
	while (j < len)
	{
		if (old_str[i] == '\\' && old_str[i + 1] == '\\')
		{
			str[j++] = '\\';
			i += 2;
		}
		else if (old_str[i] == '\\')
			i++;
		else
			str[j++] = old_str[i++];
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
		len = size_removing_slash(data->input_info->first_line_split[i]);
		new_split[i] = ft_new_string(data, len, info->first_line_split[i], 0);
		if (new_split[i] == NULL)
			return (MALLOC_ERROR);
		i++;
	}
	ft_free_char_pp(data->input_info->first_line_split);
	data->input_info->first_line_split = new_split;
	return (SUCCESS);
}
