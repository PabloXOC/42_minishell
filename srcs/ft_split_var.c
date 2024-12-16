/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_var.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/16 11:07:53 by paxoc01           #+#    #+#             */
/*   Updated: 2024/10/03 11:57:42 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_free(char **str_ptr, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		if (str_ptr[i] != NULL)
			free(str_ptr[i]);
		i++;
	}
	free(str_ptr);
	return (NULL);
}

static char	*ft_second_word(char const *s, int pos)
{
	char	*output;
	int		len_word;
	int		i;
	int		j;

	i = pos;
	j = 0;
	len_word = 0;
	while (s[i] != '\0')
	{
		len_word++;
		i++;
	}
	output = (char *) malloc((len_word + 1) * sizeof(char));
	if (output == NULL)
		return (NULL);
	i = pos;
	while (j < len_word)
		output[j++] = s[i++];
	output[j] = '\0';
	return (output);
}

static int	ft_middle(char const *s, char c, char ***str_ptr)
{
	int	i;
	int	len_word;

	i = 0;
	len_word = 0;
	while (s[i] != c && s[i] != '\0')
	{
		len_word++;
		i++;
	}
	(*str_ptr)[0] = (char *) malloc((len_word + 1) * sizeof(char));
	if ((*str_ptr)[0] == NULL)
		return (MALLOC_ERROR);
	i = 0;
	while (i < len_word)
	{
		(*str_ptr)[0][i] = s[i];
		i++;
	}
	(*str_ptr)[0][len_word] = '\0';
	(*str_ptr)[1] = ft_second_word(s, len_word + 1);
	if ((*str_ptr)[1] == NULL)
		return (MALLOC_ERROR);
	return (SUCCESS);
}

char	**ft_split_var(char const *s, char c)
{
	int		n_words;
	char	**str_ptr;

	n_words = 2;
	str_ptr = (char **)malloc((n_words + 1) * sizeof(char *));
	if (str_ptr == NULL)
		return (NULL);
	str_ptr[n_words] = NULL;
	if (ft_middle(s, c, &str_ptr) != SUCCESS)
		return (NULL);
	if (str_ptr == NULL)
		return (ft_free(str_ptr, n_words));
	return (str_ptr);
}
