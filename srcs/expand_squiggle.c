/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_squiggle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 16:42:48 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/22 17:43:58 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_strncmp2(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (s1[i] && s2[i] && i < n)
	{
		if (s1[i] - s2[i] != 0)
			return ((unsigned char) s1[i] - (unsigned char) s2[i]);
		i++;
	}
	return (0);
}

int	expand_squiggle(t_data *data, char ***array, int i)
{
	while ((*array)[i] != 0)
	{
		if (ft_strncmp((*array)[i], "~", 2) == 0)
		{
			if (return_content_var(data->env_lst, "HOME") == NULL)
				return (SUCCESS);
			else
			{
				free((*array)[i]);
				(*array)[i] = ft_strdup(return_content_var(data->env_lst,
							"HOME"));
				if ((*array)[i] == NULL)
					return (error_i(MALLOC_ERROR, data));
			}
		}
		i++;
	}
	return (SUCCESS);
}

static char	*copy_rest(t_data *d, char *str, int len)
{
	int		i;
	int		j;
	char	*out;

	i = 1;
	out = (char *) malloc ((len) * sizeof (char));
	if (out == NULL)
		return ((char *)error_c(MALLOC_ERROR, d, d->spec[d->sc_n]));
	out[len - 1] = 0;
	j = 0;
	while (i < len)
		out[j++] = str[i++];
	return (out);
}

static int	expand_squiggle2_ext(t_data *data, char ***array, int i)
{
	char	*str1;
	char	*str2;

	str2 = copy_rest(data, (*array)[i], ft_strlen((*array)[i]));
	if (str2 == NULL)
		return (MALLOC_ERROR);
	free((*array)[i]);
	str1 = ft_strdup(return_content_var(data->env_lst,
				"HOME"));
	if (str1 == NULL)
		return (error_i(MALLOC_ERROR, data));
	(*array)[i] = ft_strjoin(str1, str2);
	if ((*array)[i] == NULL)
		return (error_i(MALLOC_ERROR, data));
}

int	expand_squiggle2(t_data *data, char ***array, int i)
{
	while ((*array)[i] != 0)
	{
		if (ft_strncmp2((*array)[i], "~/", 2) == 0)
		{
			if (return_content_var(data->env_lst, "HOME") == NULL)
				return (SUCCESS);
			else if (expand_squiggle2_ext(data, array, i) == MALLOC_ERROR)
				return (MALLOC_ERROR);
		}
		i++;
	}
	return (SUCCESS);
}
