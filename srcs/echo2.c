/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 17:45:15 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/27 14:02:16 by paxoc01          ###   ########.fr       */
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

int	print_echo(t_command *full_com)
{
	bool	flag;
	int		i;

	flag = false;
	i = 1;
	if (full_com->content[i] != NULL)
	{
		if (strncmp("-n", full_com->content[i], 3) == 0)
		{
			i++;
			flag = true;
		}
		while (full_com->content[i] != NULL)
		{
			printf("%s", full_com->content[i]);
			if (full_com->content[i + 1] != NULL)
				printf(" ");
			i++;
		}
	}
	if (flag == false)
		printf("\n");
	return (SUCCESS);
}
