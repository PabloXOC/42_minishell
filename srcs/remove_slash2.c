/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_slash2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 12:51:29 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/19 16:09:15 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_old_var(char *str, int i)
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
