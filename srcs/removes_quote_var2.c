/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   removes_quote_var2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 15:52:30 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/19 16:10:44 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_s_quote(t_data *d, char *old_str, int len)
{
	d->v->jj++;
	while (old_str[d->v->jj] != '\'' && old_str[d->v->jj != 0])
	{
		d->v->jj++;
		len++;
	}
	if (old_str[d->v->jj] == '\'')
		d->v->jj++;
	return (len);
}

int	ft_handle_d_quote(t_data *d, char *old_str, int len)
{
	d->v->jj++;
	while (old_str[d->v->jj] != '\"' && old_str[d->v->jj != 0]
		&& old_str[d->v->jj - 1] == '\\')
	{
		if (old_str[d->v->jj] == '\\' && ft_isalnum(old_str[d->v->jj + 1]) == 0)
			d->v->jj += 2;
		else
			d->v->jj++;
		len++;
	}
	if (old_str[d->v->jj] == '\"')
		d->v->jj++;
	return (len);
}
