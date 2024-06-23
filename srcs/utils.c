/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:53:03 by paxoc01           #+#    #+#             */
/*   Updated: 2024/06/21 09:24:39 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//boolan, if there is no content it returns that the input is empty
//spaces are considered to still be empty
bool	ft_empty(char *input)
{
	int	i;

	i = 0;
	if (input == NULL)
		return (true);
	while (input[i] != 0)
	{
		if (input[i] != 32)
			return (false);
		i++;
	}
	return (true);
}

bool	ft_there_is_equal(char *input)
{
	int	i;

	i = 0;
	while (input[i] != 0 && input[i] != 32)
	{
		if (input[i] == '=')
			return (true);
		i++;
	}
	return (false);
}

bool	ft_samestr(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (false);
	while (s1[i])
	{
		if (s1[i] - s2[i] != 0)
			return (false);
		i++;
	}
	return (true);
}

int	ft_count_words(char **argv)
{
	int	i;

	i = 0;
	while (argv[i] != 0)
		i++;
	return (i);
}

void	print_char_pp(char **stack)
{
	int	i;

	i = 0;
	while (stack[i] != NULL)
	{
		ft_printf("%s\n", stack[i]);
		i++;
	}
}

void	ft_free_char_pp(char **stack)
{
	int	i;

	i = 0;
	while (stack[i] != NULL)
	{
		free(stack[i]);
		i++;
	}
	free (stack);
}

bool	ft_quote_switch(char *str, int i, bool single_q, bool double_q)
{
	if (str[i] == '\'' && single_q == false)
		return (true);
	else if (str[i] == '\'' && single_q == true)
		return (false);
	else if (str[i] == '\"' && double_q == false)
		return (true);
	else if (str[i] == '\"' && double_q == true)
		return (false);
	return (false);
}
