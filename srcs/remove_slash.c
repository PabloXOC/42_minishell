/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_slash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:51:29 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/18 12:21:03 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



static int	len_old_var(char *str, int i)
{
	int	size;

	size = 0;
	if (str[i] == '?')
		return (1);
	while (str[i] != 0)
	{
		if (str[i] == ' ' && str[i] == '\'' && str[i] == '\"')
			return (size);
		else if (ft_isalpha(str[i]) == 0)
			return (size);
		i++;
		size++;
	}
	return (size);
}

void	ft_count_vars(t_data *d, char *str, int i)
{
	int		len_old;

	d->v->jj++;
	len_old = len_old_var(str, i);
	d->v->jj += len_old;
	if (len_old == 0)
		return ;
	while (d->var != NULL)
	{
		if (ft_strncmp(&str[i], d->var->var, len_old) == 0)
		{
			d->v->len += ft_strlen(d->var->content);
			return ;
		}
		d->var = d->var->next;
	}
}

int	ft_size_new(t_data *d, char *old_str, int s_q, int d_q)
{
	int	var_counter;

	var_counter = 0;
	while (old_str[d->v->jj] != 0)
	{
		if ((old_str[d->v->jj] == '\'') && d_q % 2 == 0
			&& (d->v->jj == 0 || old_str[d->v->jj - 1] != '\\'))
			s_q++;
		if (old_str[d->v->jj] == '\"' && s_q % 2 == 0
			&& (d->v->jj == 0 || old_str[d->v->jj - 1] != '\\'))
			d_q++;
		if (old_str[d->v->jj] == '$' && s_q % 2 == 0
			&& (d->v->jj == 0 || old_str[d->v->jj - 1] != '\\'))
		{
			ft_count_vars(d, old_str, d->v->jj + 1);
			var_counter++;
		}
		else
		{
			d->v->jj++;
			d->v->len++;
		}
	}
	return (var_counter);
}

int	ft_paste_new_var(t_data *d, char **new_str, char *old_str, int i)
{
	int		len_old;
	int		len_new;
	int		k;

	k = 0;
	d->v->jj++;
	len_old = len_old_var(old_str, d->v->jj);
	if (len_old == 0)
		return (i);
	while (d->var != NULL)
	{
		if (ft_strncmp(&old_str[d->v->jj], d->var->var, len_old) == 0)
		{
			len_new += ft_strlen(d->var->content);
			while (k < len_new)
				(*new_str)[i++] = d->var->content[k++];
			d->v->jj += len_old;
			return (i);
		}
		d->var = d->var->next;
	}
	return (i);
}

void	ft_make_new_string(t_data *d, char *old_str, char **new_str)
{
	int	s_q;
	int	d_q;
	int	i;

	d->v->jj = 0;
	i = 0;
	s_q = 0;
	d_q = 0;
	while (old_str[d->v->jj] != 0)
	{
		if (old_str[d->v->jj] == '\'' && d_q % 2 == 0
			&& (d->v->jj == 0 || old_str[d->v->jj - 1] != '\\'))
			s_q++;
		if (old_str[d->v->jj] == '\"' && s_q % 2 == 0
			&& (d->v->jj == 0 || old_str[d->v->jj - 1] != '\\'))
			d_q++;
		if (old_str[d->v->jj] == '$' && s_q % 2 == 0
			&& (d->v->jj == 0 || old_str[d->v->jj - 1] != '\\'))
			i = ft_paste_new_var(d, new_str, old_str, i);
		else
			(*new_str)[i++] = old_str[d->v->jj++];
	}
}

int	ft_reformat_vars(t_data *data, t_input_var *info)
{
	char	*new_str;
	char	*old_str;
	int		var_counter;

	new_str = NULL;
	var_counter = 1;
	old_str = ft_strdup(info->first_line_ref);
	while (var_counter > 0)
	{
		if (new_str != NULL)
		{
			free(old_str);
			old_str = new_str;
		}
		data->v->jj = 0;
		data->v->len = 0;
		var_counter = ft_size_new(data, old_str, 0, 0);
		new_str = (char *) malloc ((data->v->len + 1) * sizeof (char));
		if (new_str == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
		new_str[data->v->len] = 0;
		ft_make_new_string(data, old_str, &new_str);
	}
	info->first_line_vars = new_str;
	return (SUCCESS);
}
