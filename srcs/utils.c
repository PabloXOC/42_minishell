/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 13:53:03 by paxoc01           #+#    #+#             */
/*   Updated: 2024/04/25 19:17:58 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_empty(char *input)
{
	int	i;

	i = 0;
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
}

int	ft_samestr(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (EXIT_FAILURE);
	while (s1[i])
	{
		if (s1[i] - s2[i] != 0)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
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
