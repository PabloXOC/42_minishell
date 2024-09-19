/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_reformats.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/18 11:44:10 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/19 11:39:42 by paxoc01          ###   ########.fr       */
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

int	ft_count_size_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != 0)
		i++;
	return (i);
}


char	**ft_new_array(t_data *d, char **old_array, char **temp_array, int w_count)
{
	int		i;
	int		size;
	char	**new_array;

	size = ft_count_size_array(old_array) - 1;
	new_array = (char **) malloc ((w_count + size) * sizeof (char));
	if (new_array == NULL)
		return (ft_write_error_a(MALLOC_ERROR, d, d->specific[d->sc_pos]));
	new_array[w_count + size - 1] = 0;
	i = -1;
	while (++i < w_count)
	{
		new_array[i] = ft_strdup(temp_array[i]);
		if (new_array[i] == NULL)
			return (ft_write_error_a(MALLOC_ERROR, d, d->specific[d->sc_pos]));
	}
	i = -1;
	while (++i < size)
	{
		new_array[i + w_count] = ft_strdup(old_array[i + 1]);
		if (new_array[i] == NULL)
			return (ft_write_error_a(MALLOC_ERROR, d, d->specific[d->sc_pos]));
	}
	return (new_array);
}

int	ft_expand_first_word(t_data *data, t_command *com)
{
	int		count;
	char	**new_array;
	char	**temp_array;

	temp_array = ft_split(com->content[0], ' ');
	if (temp_array == NULL)
		return (ft_write_error_i(MALLOC_ERROR, data));
	count = ft_count_size_array(temp_array);
	if (count > 1)
	{
		new_array = ft_new_array(data, com->content, temp_array, count);
		if (new_array == NULL)
		{
			ft_free_char_pp(temp_array);
			return (ft_write_error_i(MALLOC_ERROR, data));
		}
		ft_free_char_pp(com->content);
		com->content = new_array;
	}
	ft_free_char_pp(temp_array);
	return (SUCCESS);
}

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
		if (ft_expand_first_word(data, com) == MALLOC_ERROR)
			return (MALLOC_ERROR);
		com->full_path = find_command_path(data->env, com->content[0], 0, data);
		if (com->full_path == NULL)
			return (ft_write_error_i(MALLOC_ERROR, data));
		com = com->next;
	}
}
