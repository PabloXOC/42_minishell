/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/05/15 16:59:18 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_data	*data_init(void)
{
	t_data	*data;

	data = (t_data *) malloc (sizeof (t_data));
	if (data == NULL)
		return (ft_write_error_c(MALLOC_ERROR, data));
	data->input_split = NULL;
	data->input = NULL;
	data->paired = 0;
	data->exit = false;
	data->user = NULL;
	data->hostname = NULL;
	data->dir = NULL;
	data->entry = NULL;
	data->command_list = NULL;
	data->redirect_input = NULL;
	data->redirect_output = NULL;
	data->limiter = NULL;
	data->append_output = false;
	data->var = NULL;
	data->var_export = NULL;
	data->text_input = NULL;
	data->text_input = NULL;
	data->next_eof = NULL;
	data->malloc_error = false;
	return (data);
}

int	ft_pair(char *input, char c, int i, t_data *data)
{
	while (input[i] != 0)
	{
		if (input[i] == c)
		{
			data->paired = 2;
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

bool	ft_not_complete(char *input, t_data *data)
{
	int	i;

	i = 0;
	while (input[i] != 0)
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			data->paired = 1;
			i = ft_pair(input, input[i], i + 1, data);
			if (data->paired == 1)
			{
				data->paired = 0;
				return (true);
			}
		}
		if (input[i] == '\\' && input[i + 1] == 0)
			return (true);
		if (input[i] == '\\' && input[i + 1] == '\\')
			return (false);
		if (input[i] != 0)
			i++;
	}
	return (false);
}

char	*ft_join_input(char *s1, char *s2)
{
	char	*str;
	int		len_1;
	int		len_2;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	str = ft_calloc(len_1 + len_2 + 1, 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1, len_1);
	ft_memcpy(&str[len_1], s2, len_2);
	str[len_1 + len_2] = 0;
	free(s1);
	return (str);
}
