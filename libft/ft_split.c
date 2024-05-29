/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/03 14:46:58 by pximenez          #+#    #+#             */
/*   Updated: 2023/12/07 15:37:23 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nwords(char const *s, char c)
{
	int	counter;
	int	i;

	i = 0;
	counter = 0;
	if (s[0] != c && s[0] != 0)
		counter++;
	while (s[i])
	{
		if (s[i] == c)
		{
			while (s[i] == c)
				i++;
			if (s[i] != 0)
				counter++;
		}
		if (s[i] == 0)
			return (counter);
		i++;
	}
	return (counter);
}

static void	ft_free(char **str_ptr, int number)
{
	int	i;

	i = 0;
	while (i < number)
	{
		free(str_ptr[i]);
		i++;
	}
	free(str_ptr);
}

static	char	**ft_middle(char const *s, char c, char **str_ptr, int n_words)
{
	int	i;
	int	len_word;

	i = 0;
	while (*s == c && *s != 0)
		s++;
	while (i < n_words)
	{
		len_word = 0;
		while (s[len_word] != c && s[len_word] != 0)
			len_word++;
		str_ptr[i] = ft_substr(s, 0, len_word);
		if (str_ptr[i] == NULL)
		{
			ft_free(str_ptr, i);
			return (NULL);
		}
		s = &s[len_word];
		if (*s == 0)
			break ;
		while (*s == c)
			s++;
		i++;
	}
	return (str_ptr);
}

char	**ft_split(char const *s, char c)
{
	int		n_words;
	char	**str_ptr;

	n_words = ft_nwords(s, c);
	str_ptr = (char **)malloc((n_words + 1) * sizeof(char *));
	if (!(str_ptr))
		return (NULL);
	str_ptr[n_words] = 0;
	str_ptr = ft_middle(s, c, str_ptr, n_words);
	return (str_ptr);
}

/* int	main(void)
{
	char	**ptr;

	char str[25] = "hello!l";
	ptr = ft_split("hola", 0);
	printf("%s\n", ptr[0]);
	printf("%s\n", ptr[1]);
	//printf("%s\n", ptr);
} */
