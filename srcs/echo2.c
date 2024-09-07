/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:45:15 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/04 19:36:34 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_fillout_var(t_data *d, int size, char *str, int single_q)
{
	char	*output;

	output = (char *) malloc ((size + 1) * sizeof(char));
	if (!output)
		return (ft_write_error_c(MALLOC_ERROR, d, d->specific[d->sc_pos]));
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
	data->v->size = 0;
	size = tot_size(data, text, 0);
	//printf("size: %i\n", size);
	data->v->iii = 0;
	data->v->jjj = 0;
	str = ft_fillout_var(data, size, text, 0);
	free(text);
	return (str);
}
