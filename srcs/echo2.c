/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/03 12:56:18 by ffauth-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_fillout_var(t_data *d, int size, char *str, int single_q)
{
	char	*output;

	output = (char *) malloc ((size + 1) * sizeof(char));
	if (!output)
		return (ft_write_error_c(MALLOC_ERROR, d));
	while (str[d->iii] != 0)
	{
		if (str[d->iii] == '\'')
			single_q++;
		else if (str[d->iii] == '\"' && single_q % 2 == 0)
			;
		else if (str[d->iii] == '$' && single_q % 2 == 0
			&& str[d->iii + 1] != ' ' && str[d->iii + 1] != 0)
		{
			if (str[d->iii + 1] >= '0' && str[d->iii + 1] <= '9')
				d->iii++;
			else
				fill_new_var(d, str, d->iii + 1, &output[d->jjj]);
		}
		else
			output[d->jjj++] = str[d->iii];
		d->iii++;
	}
	output[d->jjj] = 0;
	return (output);
}

char	*expand_var(t_data *data, char *text)
{
	int		size;
	char	*str;

	if (text == NULL)
		return (ft_strdup(""));
	data->iii = 0;
	data->size = 0;
	size = tot_size(data, text, 0);
	data->iii = 0;
	data->jjj = 0;
	str = ft_fillout_var(data, size, text, 0);
	free(text);
	return (str);
}
