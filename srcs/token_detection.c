/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_detection.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:44:49 by paxoc01           #+#    #+#             */
/*   Updated: 2024/06/12 14:45:56 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//boolan, returns true if it finds a < > << >>
static bool ft_found_io(char *str, int i, t_data *data)
{
	if (str[i] == '<' && str[i + 1] == '<')
	{
		data->input_info->n_eof++;
		return (true);
	}
	if (str[i] == '<' && str[i + 1] == ' ')
		return (true);
	if (str[i] == '>' && str[i + 1] == '>')
		return (true);
	if (str[i] == '>' && str[i + 1] == ' ')
		return (true);
	return (false);
}

//boolean returns true if it finds an invalid token
static bool ft_invalid_token(char *str, int i)
{
	while (str[i] == ' ')
		i++;
	if (str[i] == '\n')
		return (true);
	if (str[i] == '\0')
		return (true);
	if (str[i] == '|')
		return (true);
	if (str[i] == '<' && str[i + 1] == '<')
		return (true);
	if (str[i] == '<' && str[i + 1] == ' ')
		return (true);
	if (str[i] == '>' && str[i + 1] == '>')
		return (true);
	if (str[i] == '>' && str[i + 1] == ' ')
		return (true);
	return (false);
}


//if we find quotations we skip until we are outside
static int	ft_skip_quote(char *str, int i, char c)
{
	i++;
	while (str[i] != c)
	{
		if (str[i] == '\0')
			return (i);
		i++;
	}
	i++;
	return (i);
}

//find if after a < > << >> we have a valid token
int	ft_check_token(t_data *data)
{
	int	i;

	i = 0;
	while (data->input_info->first_line_ref[i] != '\0')
	{
		if (data->input_info->first_line_ref[i] == '\'' || data->input_info->first_line_ref[i] == '\"')
			i = ft_skip_quote(data->input_info->first_line_ref, i, data->input_info->first_line_ref[i]);
		if (data->input_info->first_line_ref[i] == '\0')
			break ;
		if (ft_found_io(data->input_info->first_line_ref, i, data) == true)
		{
			i +=2;
			if (ft_invalid_token(data->input_info->first_line_ref, i) == true)
				return (INVALID_TOKEN);
		}
		i++;
	}
	return (SUCCESS);
}