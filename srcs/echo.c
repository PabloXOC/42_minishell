/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 19:10:17 by farah             #+#    #+#             */
/*   Updated: 2024/06/27 20:19:49 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	trim_vars(t_data *data)
{
	
}

char	*return_content_var(t_data *data, char *text, int len_v)
{
	t_var	*node;

	node = data->var;
	while (node != NULL)
	{
		if (ft_strncmp(text, node->var, len_v) == 0)
			return (node->content);
		node = node->next;
	}
	return (NULL);
}

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

int	len_new_var(t_data* data, char *str, int i)
{
	int		len_old;
	t_var	*var;

	len_old = len_old_var(str, i);
	if (len_old == 0)
		return (0);
	var = data->var;
	while (var != NULL)
	{
		if (ft_strncmp(&str[i], var->var, len_old) == 0)
			return (ft_strlen(var->content));
		var = var->next;
	}
	return (0);
}

int	tot_size(t_data* data, char *str, int single_q)
{
	int	i;
	int	size;
	int	ret;

	i = 0;
	size = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\'')
			single_q++;
		else if (str[i] == '\"')
			;
		else if (str[i] == '$' && single_q % 2 == 0 && str[i + 1] != ' '
			&& str[i + 1] != 0)
		{
			if (str[i + 1] >= '0' && str[i + 1] <= '9')
				i++;
			else
			{
				ret = len_new_var(data, str, i + 1);
				size += ret;
				i += ret;
			}
		}
		else
			size++;
		i++;
	}
	return (size);
}

char	*ft_fillout_var(t_data *data, int size, char *str)
{
	char	*output;
	int		i;

	i = 0;
	output = (char *) malloc ((size + 1) * sizeof(char));
	if (!output)
		return (ft_write_error_c(MALLOC_ERROR, data));
	while (str[i] != 0)
	{
		
	}
	
}

char	*expand_var(t_data *data, char *text)
{
	int		size;
	
	size = tot_size(data, text, 0);
	return (ft_fillout_var(data, size, text));
}
