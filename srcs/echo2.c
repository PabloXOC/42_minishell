/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:45:15 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/14 19:07:42 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_fillout_var(t_data *d, char *str, int s_q, int d_q)
{
	char	*output;

	output = (char *) malloc ((d->v->size_tot + 1) * sizeof(char));
	if (!output)
		return (ft_write_error_c(MALLOC_ERROR, d, d->specific[d->sc_pos]));
	while (str[d->v->iii] != 0)
	{
		if (str[d->v->iii] == '\'' && d_q % 2 == 0 && (d->v->iii == 0 || str[d->v->iii - 1] != '\\'))
			s_q++;
		if (str[d->v->iii] == '\"' && s_q % 2 == 0 && (d->v->iii == 0 || str[d->v->iii - 1] != '\\'))
			d_q++;
		if (str[d->v->iii] == '$' && s_q % 2 == 0
			&& str[d->v->iii + 1] != ' ' && str[d->v->iii + 1] != 0)
		{
			if (str[d->v->iii + 1] >= '0' && str[d->v->iii + 1] <= '9')
				d->v->iii++;
			else
				fill_new_var(d, str, d->v->iii + 1, &output[d->v->jjj]);
		}
		else
			output[d->v->jjj++] = str[d->v->iii];
		d->v->iii++;
	}
	output[d->v->jjj] = 0;
	return (output);
}

char	*expand_var(t_data *data, char *text)
{
	int		size;
	char	*str;

	if (text == NULL)
		return (ft_strdup(""));
	if (ft_strncmp(text, "~", 2) == 0)
	{
		if (return_content_var(data->env_lst, "HOME") == NULL)
			return (NULL);
		str = ft_strdup(return_content_var(data->env_lst, "HOME"));
		if (str == NULL)
			return (ft_write_error_c(MALLOC_ERROR, data, data->specific[data->sc_pos]));
		return (str);
	}
	data->v->iii = 0;
	data->v->size_var = 0;
	data->v->size_tot = tot_size(data, text, 0, 0);
	data->v->iii = 0;
	data->v->jjj = 0;
	str = ft_fillout_var(data, text, 0, 0);
	free(text);
	return (str);
}
