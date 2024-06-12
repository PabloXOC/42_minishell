/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell_split.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/01 17:16:55 by ffauth-p          #+#    #+#             */
/*   Updated: 2024/06/10 14:21:32 by paxoc01          ###   ########.fr       */
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

static int	count_words(char const *s, char c)
{
	int		count;
	int		i;
	char	quote;

	count = 0;
	i = 0;
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
	int	len_word;
	char	quote;

	len_word = 0;
	if (s[i] == '"' || s[i] == '\'')
	{
		quote = s[i++];
		while (s[i] != quote && s[i] != '\0')
		{
			len_word++;
			i++;
		}
		return (len_word);
	}
	while (s[i] != c && s[i] != '\0')
	{
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
	while ((s[i] == c || s[i] == '"' || s[i] == '\'') && s[i] != '\0')
		i++;
	while (s[i] != '\0')
	{
		len_word = ft_len_words(i, s, c);
		if (s[i] == '"' || s[i] == '\'')
			i++;
		array[row] = ft_substr(s, i, len_word);
		if (array[row] == NULL)
		{
			ft_free_malloc(array, row);
			return (NULL);
		}
		i = len_word + i;
		if (s[i] == '"' || s[i] == '\'')
			i++;
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

	nwords = count_words(s, c);
	printf("nwords: %i\n", nwords);
	array = (char **)malloc((nwords + 1) * sizeof(char *));
	if (!(array))
		return (NULL);
	array[nwords] = 0;
	array = ft_fill_array(s, c, array);
	return (array);
}

/* int	main(int argc, char **argv)
{
	int	i;

	char c = 32;
	char	**result;
	char	str[] = "hola como \"como estas\" yo bien";
	printf("str: %s\n", str);
	result = ft_minishell_split(str, c);
	i = 0;
	while (i < ft_count_words(str, c))
	{
		printf("%s, %d\n", result[i], i);
		i++;
	}
	//printf("%s\n", result);
	//while (42);
} */
