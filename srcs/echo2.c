/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:45:15 by pximenez          #+#    #+#             */
/*   Updated: 2024/11/11 13:23:36 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_fillout_var(t_data *d, char *str, int s_q, int d_q)
{
	char	*output;

	output = (char *) malloc ((d->v->size_tot + 1) * sizeof(char));
	if (!output)
		return (error_c(MALLOC_ERROR, d, d->spec[d->sc_n]));
	while (str[d->v->iii] != 0)
	{
		if (str[d->v->iii] == '\'' && d_q % 2 == 0
			&& (d->v->iii == 0 || str[d->v->iii - 1] != '\\'))
			s_q++;
		if (str[d->v->iii] == '\"' && s_q % 2 == 0
			&& (d->v->iii == 0 || str[d->v->iii - 1] != '\\'))
			d_q++;
		if (str[d->v->iii] == '$' && s_q % 2 == 0
			&& str[d->v->iii + 1] != ' ' && str[d->v->iii + 1] != 0)
			fill_new_var(d, str, d->v->iii + 1, &output[d->v->jjj]);
		else
			output[d->v->jjj++] = str[d->v->iii];
		d->v->iii++;
	}
	output[d->v->jjj] = 0;
	return (output);
}

char	*expand_var(t_data *data, char *text)
{
	char	*str;

	if (text == NULL)
		return (ft_strdup(""));
	if (ft_strncmp(text, "~", 2) == 0)
	{
		if (return_content_var(data->env_lst, "HOME") == NULL)
			return (NULL);
		str = ft_strdup(return_content_var(data->env_lst, "HOME"));
		if (str == NULL)
			return (error_c(MALLOC_ERROR,
					data, data->spec[data->sc_n]));
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

int	exec_echo_search(t_command *full_com, int i, int j, bool *n)
{
	while (full_com->content[i] != 0)
	{
		if (full_com->content[i][0] != '-')
			return (i);
		j = 1;
		while (full_com->content[i][j] != 0)
		{
			if (full_com->content[i][j] != 'n')
				return (i);
			j++;
		}
		(*n) = true;
		i++;
	}
	return (i);
}

int	exec_echo(t_command *full_com, int i, bool n)
{
	i = exec_echo_search(full_com, 1, 0, &n);
	while (full_com->content[i] != 0)
	{
		write(full_com->fd_out, full_com->content[i], ft_strlen(full_com->content[i]));
		if (full_com->content[i + 1] != 0)
			write(full_com->fd_out, " ", 1);
		i++;
	}
	if (n == false)
		write(full_com->fd_out, "\n", 1);
	return (exit_codes(EXIT_0, NULL));
}
