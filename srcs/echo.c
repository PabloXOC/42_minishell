/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:44:41 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/04 16:24:41 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	len_old_var(char *str, int i)
{
	int	size;

	size = 0;
	while (str[i] != 0)
	{
		if (str[i] == ' ' || str[i] == '\'' || str[i] == '\"')
			return (size);
		else if (str[i] == '?' && size == 0)
			return (1);
		else if (ft_isalnum(str[i]) == 0)
			return (size);
		i++;
		size++;
	}
	return (size);
}

static void	len_new_var(t_data *data, char *str, int i)
{
	int		len_old;
	t_var	*var;

	len_old = len_old_var(str, i);
	if (len_old == 0)
		return ;
	var = data->var;
	while (var != NULL)
	{
		if (ft_strncmp(&str[i], var->var, len_old) == 0)
		{
			data->v->iii += len_old;
			data->v->size_var += ft_strlen(var->content);
			return ;
		}
		var = var->next;
	}
	data->v->iii += len_old;
}

void	fill_new_var(t_data *d, char *str, int i, char *dst)
{
	int		len_old;
	t_var	*var;

	len_old = len_old_var(str, i);
	if (len_old == 0)
		return ;
	var = d->var;
	while (var != NULL)
	{
		if (ft_strncmp(&str[i], var->var, len_old) == 0)
		{
			d->v->iii += len_old;
			d->v->jjj += ft_strlen(var->content);
			ft_memcpy(dst, var->content, ft_strlen(var->content));
			return ;
		}
		var = var->next;
	}
	d->v->iii += len_old;
}

int	tot_size(t_data *d, char *str, int single_q)
{
	while (str[d->v->iii] != 0)
	{
		if (str[d->v->iii] == '\'')
			single_q++;
		else if (str[d->v->iii] == '\"' && single_q % 2 == 0)
			;
		else if (str[d->v->iii] == '$' && single_q % 2 == 0
			&& str[d->v->iii + 1] != ' ' && str[d->v->iii + 1] != 0)
		{
			if (str[d->v->iii + 1] >= '0' && str[d->v->iii + 1] <= '9')
				d->v->iii++;
			else
				len_new_var(d, str, d->v->iii + 1);
		}
		else
			d->v->size_var++;
		d->v->iii++;
	}
	return (d->v->size_var);
}
