/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:39 by pximenez          #+#    #+#             */
/*   Updated: 2024/10/09 01:34:35 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_free_malloc(char **array, int row)
{
	int	i;

	i = 0;
	while (i < row)
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int	count_words(char const *str, char c, int count, int i)
{
	int	s_q;
	int	d_q;

	s_q = 0;
	d_q = 0;
	while (str[i] != '\0')
	{
		if (s_q % 2 == 0 && str[i] == '\\'
			&& (str[i + 1] == '\'' || str[i + 1] == '\"'))
			i++;
		else if (str[i] == '\'' && d_q % 2 == 0)
			s_q++;
		else if (str[i] == '\"' && s_q % 2 == 0)
			d_q++;
		if (str[i] == c && s_q % 2 == 0 && d_q % 2 == 0)
		{
			while (str[i] == c)
				i++;
			if (str[i] != '\0')
				count++;
		}
		else
			i++;
	}
	return (count);
}

static int	ft_len_words(char const *str, char c, int s_q, int d_q)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (s_q % 2 == 0 && str[i] == '\\'
			&& (str[i + 1] == '\'' || str[i + 1] == '\"'))
			i++;
		else if (str[i] == '\'' && d_q % 2 == 0)
			s_q++;
		else if (str[i] == '\"' && s_q % 2 == 0)
			d_q++;
		i++;
		if (str[i] == c && s_q % 2 == 0 && d_q % 2 == 0)
			return (i);
	}
	return (i);
}

static char	**ft_fill_array(char const *s, char c, char **array)
{
	int	row;
	int	i;
	int	len_word;

	i = 0;
	row = 0;
	while ((s[i] == c) && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		len_word = ft_len_words(&s[i], c, 0, 0);
		array[row] = ft_substr(s, i, len_word);
		if (array[row] == NULL)
		{
			ft_free_malloc(array, row);
			return (NULL);
		}
		i = len_word + i;
		while (s[i] == c && s[i] != '\0')
			i++;
		row++;
	}
	return (array);
}

char	**ft_minishell_split(char const *s, char c)
{
	int		nwords;
	char	**array;

	if (s[0] != c && s[0] != '\0')
		nwords = count_words(s, c, 1, 0);
	else
		nwords = count_words(s, c, 0, 0);
	array = (char **)malloc((nwords + 1) * sizeof(char *));
	if (!(array))
		return (NULL);
	array[nwords] = 0;
	array = ft_fill_array(s, c, array);
	return (array);
}
