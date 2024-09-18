/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_reformats.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:44:10 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/18 20:34:18 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	expand_squiggle(t_data *data, char ***array, int i)
{
    while ((*array)[i] != 0)
    {
		if (ft_strncmp((*array)[i], "~", 2) == 0)
		{
			if (return_content_var(data->env_lst, "HOME") == NULL)
			{
				free((*array)[i]);
				(*array)[i] = ft_strdup("");
				if ((*array)[i] == NULL)
					return (ft_write_error_i(MALLOC_ERROR, data));
			}
			else
			{
				free((*array)[i]);
				(*array)[i] = ft_strdup(return_content_var(data->env_lst, "HOME"));
				if ((*array)[i] == NULL)
					return (ft_write_error_i(MALLOC_ERROR, data));
			}
		}
		i++;
    }
	return (SUCCESS);
}

/* int	ft_expand_first_word(t_data *data, char **array, int i)
{
	
} */

int	reformat_final(t_data *data,t_specific *spec)
{
	t_command *com;

	com = spec->command_list;
	while (com != NULL)
	{
		if (expand_squiggle(data, &com->content, 0) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		if (ft_remove_quotes_bar(&com->content, data) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		/* if (ft_expand_first_word(info->first_line_split, data) == MALLOC_ERROR)
			return (MALLOC_ERROR); */
		com->full_path = find_command_path(data->env, com->content[0], 0, data);
		if (com->full_path == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
		com = com->next;
	}
}