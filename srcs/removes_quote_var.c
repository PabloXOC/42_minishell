/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removes_quote_var.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:52:30 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/21 14:54:23 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_paste_s_quote(t_data *d, char *old_str, char **str, int i)
{
	i++;
	while (old_str[i] != '\'' && old_str[i] != 0)
		(*str)[d->v->jj++] = old_str[i++];
	if (old_str[i] == '\'')
		i++;
	return (i);
}

int	ft_paste_d_quote(t_data *d, char *old_str, char **str, int i)
{
	i++;
	while (old_str[i] != '\"' && old_str[i] != 0)
	{
		if (old_str[i] == '\\' && ft_isalnum(old_str[i + 1]) == 0)
		{
			(*str)[d->v->jj++] = old_str[i + 1];
			i += 2;
		}
		else
			(*str)[d->v->jj++] = old_str[i++];
	}
	if (old_str[i] == '\"')
		i++;
	return (i);
}

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

int	ft_remove_quotes_bar(char ***list, t_data *data)
{
	int		i;
	int		new_size;
	char	*new_str;

	i = 0;
	while ((*list)[i] != 0)
	{
		new_size = ft_calc_size(data, (*list)[i], 0);
		new_str = (char *) malloc ((new_size + 1) * sizeof (char));
		if (new_str == NULL)
			return (error_i(MALLOC_ERROR, data));
		new_str[new_size] = 0;
		ft_new_string(data, (*list)[i], &new_str, 0);
		free((*list)[i]);
		(*list)[i] = new_str;
		i++;
	}
	return (SUCCESS);
}
