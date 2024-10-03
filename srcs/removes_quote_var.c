/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removes_quote_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:52:30 by paxoc01           #+#    #+#             */
/*   Updated: 2024/10/03 10:59:28 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_calc_size(t_data *d, char *old_str, int len)
{
	d->v->jj = 0;
	while (old_str[d->v->jj] != 0)
	{
		if (old_str[d->v->jj] == '\'' && (d->v->jj == 0
				|| old_str[d->v->jj - 1] != '\\'))
			len = ft_handle_s_quote(d, old_str, len);
		else if (old_str[d->v->jj] == '\"' && (d->v->jj == 0
				|| old_str[d->v->jj - 1] != '\\'))
			len = ft_handle_d_quote(d, old_str, len);
		else if (old_str[d->v->jj] == '\\')
		{
			if (old_str[d->v->jj + 1] == 0)
				return (len);
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

static void	ft_new_string(t_data *d, char *old_str, char **new_str, int i)
{
	d->v->jj = 0;
	while (old_str[i] != 0)
	{
		if (old_str[i] == '\'' && (i == 0 || old_str[i - 1] != '\\'))
			i = ft_paste_s_quote(d, old_str, new_str, i);
		else if (old_str[i] == '\"' && (i == 0 || old_str[i - 1] != '\\'))
			i = ft_paste_d_quote(d, old_str, new_str, i);
		else if (old_str[i] == '\\')
		{
			if (old_str[i + 1] == 0)
			{
				(*new_str)[d->v->jj++] = 0;
				return ;
			}
			i++;
			(*new_str)[d->v->jj++] = old_str[i++];
		}
		else
			(*new_str)[d->v->jj++] = old_str[i++];
	}
	(*new_str)[d->v->jj++] = 0;
}

int	ft_assemble(char **list, t_data *data, char ***new_list, int i)
{
	int		new_size;
	char	*new_str;
	int		j;

	j = 0;
	while (list[j] != 0)
	{
		new_size = ft_calc_size(data, list[j], 0);
		if (new_size != 0)
		{
			new_str = (char *) malloc ((new_size + 1) * sizeof (char));
			if (new_str == NULL)
				return (error_i(MALLOC_ERROR, data));
			new_str[new_size] = 0;
			ft_new_string(data, list[j], &new_str, 0);
			(*new_list)[i] = new_str;
			i++;
		}
		j++;
	}
	return (SUCCESS);
}

int	ft_size_array(char **list, t_data *data)
{
	int		j;
	int		new_size;
	int		counter;

	j = 0;
	counter = 0;
	while (list[j] != 0)
	{
		new_size = ft_calc_size(data, list[j], 0);
		if (new_size != 0)
			counter++;
		j++;
	}
	return (counter);
}

int	ft_remove_quotes_bar(char ***list, t_data *data)
{
	int		new_size;
	char	**new_list;

	new_size = ft_size_array((*list), data);
	if (new_size == 0)
	{
		ft_free_char_pp(*list);
		new_list = (char **) malloc ((1 + 1) * sizeof (char *));
		new_list[1] = 0;
		new_list[0] = ft_strdup("");
		(*list) = new_list;
		return (SUCCESS);
	}
	new_list = (char **) malloc ((new_size + 1) * sizeof (char *));
	if (new_list == NULL)
		return (error_i(MALLOC_ERROR, data));
	new_list[new_size] = 0;
	if (ft_assemble(*list, data, &new_list, 0) != SUCCESS)
	{
		ft_free_char_pp(new_list);
		return (MALLOC_ERROR);
	}
	ft_free_char_pp(*list);
	(*list) = new_list;
	return (SUCCESS);
}
