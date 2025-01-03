/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_slash.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:51:29 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/27 14:10:01 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	int		k;
	int		jj;
	t_var	*var;

	k = 0;
	d->v->jj++;
	len_old = len_old_var(old_str, d->v->jj);
	if (len_old == 0)
		return (i);
	jj = d->v->jj;
	d->v->jj += len_old;
	var = d->var;
	while (var != NULL)
	{
		if (ft_strncmp(&old_str[jj], var->var, len_old) == 0)
		{
			while (k < (int) ft_strlen(var->content))
				(*new_str)[i++] = var->content[k++];
			return (i);
		}
		var = var->next;
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

int	ft_reformat_vars(t_data *data, t_info *info, int count, int i)
{
	char	*new_str;
	char	*old_str;

	new_str = NULL;
	old_str = ft_strdup(info->first_line_ref);
	if (old_str == NULL)
		return (error_i(MALLOC_ERROR, data));
	while (count > 0 && i <= 1)
	{
		if (new_str != NULL)
			old_str = new_str;
		data->v->jj = 0;
		data->v->len = 0;
		count = ft_size_new(data, old_str, 0, 0);
		new_str = (char *) malloc ((data->v->len + 1) * sizeof (char));
		if (new_str == NULL)
			return (error_i(MALLOC_ERROR, data));
		new_str[data->v->len] = 0;
		ft_make_new_string(data, old_str, &new_str);
		free(old_str);
		i++;
	}
	info->first_line_vars = new_str;
	return (SUCCESS);
}
