/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_detection2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 14:44:49 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/22 15:19:40 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//boolan, returns true if it finds a < > << >>
static bool	ft_find_token(char *str)
{
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
		return (true);
	if (ft_strncmp(str, ";", ft_strlen(str)) == 0)
		return (true);
	return (false);
}

//boolean returns true if it finds an invalid token
static bool	ft_invalid_token(char **array, char *str, int i)
{
	if (i == 0)
		return (ft_check_next(array, str, i));
	else
		return (ft_check_both(array, str, i));
}

//find if after a < > << >> we have a valid token
int	ft_check_token2(t_data *data, t_info *info)
{
	char	**array;
	int		i;

	array = ft_minishell_split(data->input_info_g->first_line_ref, ' ');
	if (array == NULL)
		return (error_i(MALLOC_ERROR, data));
	i = 0;
	print_char_pp(array);
	while (array[i] != 0)
	{
		if (ft_find_token(array[i]) == true)
		{
			if (ft_invalid_token(array, array[i], i) == true)
			{
				info->invalid_token = true;
				ft_putstr_fd("syntax error near unexpected token\n", 2);
				exit_codes(EXIT_2, data);
				ft_free_char_pp(array);
				return (INVALID_TOKEN);
			}
		}
		i++;
	}
	ft_free_char_pp(array);
	return (SUCCESS);
}
