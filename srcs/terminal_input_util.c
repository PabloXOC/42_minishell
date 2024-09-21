/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   terminal_input_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 15:21:58 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/21 14:31:45 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//determine the size of eof
int	ft_eofsize(char *str, int i, bool single_q, bool double_q)
{
	int		size;

	size = 0;
	while ((((single_q == true || double_q == true) || (single_q == false
					&& double_q == false && str[i] != ' '))) && str[i] != 0)
	{
		if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
		{
			i++;
			size++;
		}
		else if (str[i] == '\'' && double_q == false)
			single_q = ft_quote_switch(str, i, single_q, double_q);
		else if (str[i] == '\"' && single_q == false)
			double_q = ft_quote_switch(str, i, single_q, double_q);
		else
		{
			size++;
		}
		i++;
	}
	return (size);
}

//save the eof to the variable
char	*ft_write_eof(char *str, char *eof, int size, int i)
{
	int		j;
	bool	single_q;
	bool	double_q;

	single_q = false;
	double_q = false;
	j = 0;
	while (j < size && str[i] != '\0')
	{
		if (str[i] == '\\' && (str[i + 1] == '\'' || str[i + 1] == '\"'))
		{
			eof[j++] = str[i + 1];
			i += 2;
		}
		else if (str[i] == '\'' && double_q == false)
			single_q = ft_quote_switch(str, i, single_q, double_q);
		else if (str[i] == '\"' && single_q == false)
			double_q = ft_quote_switch(str, i, single_q, double_q);
		else
			eof[j++] = str[i];
		i++;
	}
	eof[j] = 0;
	return (eof);
}

//given the position in the str, we determine what the eof will be
char	*ft_find_eof(char *str, int i, t_data *data)
{
	int		j;
	int		size;
	char	*eof;

	while (str[i] == ' ')
		i++;
	size = ft_eofsize(str, i, false, false);
	eof = (char *) malloc ((size + 1) * sizeof(char));
	if (eof == NULL)
		return (error_c(MALLOC_ERROR, data, NULL));
	ft_write_eof(str, eof, size, i);
	return (eof);
}

bool	ft_compare_eof(char *str, char *eof, t_data *data)
{
	int	size;
	int	i;

	i = 0;
	size = ft_strlen(eof);
	while (i < size && str[i] != 0 && str[i] != '\n')
	{
		if (str[i] != eof[i])
			return (false);
		i++;
	}
	if (i != size)
		return (false);
	if (str[i] == '\n' || str[i] == '\0')
	{
		data->input_info_g->search_eof = &str[i + 1];
		return (true);
	}
	else
		return (false);
}

bool	ft_compare_eof_ind(char *str, char *eof, t_data *data)
{
	int	size;
	int	i;

	i = 0;
	size = ft_strlen(eof);
	while (i < size && str[i] != 0 && str[i] != '\n')
	{
		if (str[i] != eof[i])
			return (false);
		i++;
	}
	if (i != size)
		return (false);
	if (str[i] == '\n' || str[i] == '\0')
	{
		return (true);
	}
	else
		return (false);
}
