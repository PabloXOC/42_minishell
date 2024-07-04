/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffauth-p <ffauth-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 16:44:39 by pximenez          #+#    #+#             */
/*   Updated: 2024/07/04 21:03:33 by ffauth-p         ###   ########.fr       */
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

static int	count_words(char const *s, char c, int count, int i)
{
	char	quote;

	if (s[0] != c && s[0] != '\0')
		count = 1;
	while (s[i] != '\0')
	{
		if (s[i] == '"' || s[i] == '\'')
		{
			quote = s[i++];
			while (s[i] != quote && s[i] != '\0')
				i++;
			i++;
		}
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i] != '\0')
				count++;
		}
		if ((s[i] != '"' && s[i] != '\''))
			i++;
	}
	return (count);
}

static int	ft_len_words(int i, char const *s, char c)
{
	int		len_word;
	char	quote;

	len_word = 0;
	while (s[i] != c && s[i] != '\0')
	{
		if ((i == 0 || s[i - 1] != '\\') && (s[i] == '"' || s[i] == '\''))
		{
			quote = s[i++];
			len_word++;
			while (s[i] != quote && s[i] != '\0' && s[i - 1] != '\\')
			{
				len_word++;
				i++;
			}
		}
		len_word++;
		i++;
	}
	return (len_word);
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
		len_word = ft_len_words(i, s, c);
		//printf("len word: %i\n", len_word);
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

	nwords = count_words(s, c, 0, 0);
	array = (char **)malloc((nwords + 1) * sizeof(char *));
	if (!(array))
		return (NULL);
	array[nwords] = 0;
	array = ft_fill_array(s, c, array);
	return (array);
}
