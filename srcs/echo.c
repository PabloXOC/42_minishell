/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/07/02 17:40:36 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	len_old_var(char *str, int i)
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

void	len_new_var(t_data *data, char *str, int i)
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
			data->iii += len_old;
			data->size_var += ft_strlen(var->content);
			return ;
		}
		var = var->next;
	}
	data->iii += len_old;
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
			d->iii += len_old;
			d->jjj += ft_strlen(var->content);
			ft_memcpy(dst, var->content, ft_strlen(var->content));
			return ;
		}
		var = var->next;
	}
	d->iii += len_old;
}

int	tot_size(t_data *d, char *str, int single_q)
{
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
				len_new_var(d, str, d->iii + 1);
		}
		else
			d->size_var++;
		d->iii++;
	}
	return (d->size_var);
}

char	*ft_fillout_var(t_data *d, int size, char *str, int single_q)
{
	char	*output;

	output = (char *) malloc ((size + 1) * sizeof(char));
	if (!output)
		return (ft_write_error_c(MALLOC_ERROR, d));
	single_q = 0;
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
