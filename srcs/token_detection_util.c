/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_detection_util.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:11:07 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/23 17:11:07 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ft_check_next(char **array, char *str, int i)
{
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
	{
		if (array[i + 1] == NULL)
			return (true);
		if (ft_strncmp(array[i + 1], "|", ft_strlen(array[i + 1])) == 0)
			return (true);
		if (ft_strncmp(array[i + 1], ";", ft_strlen(array[i + 1])) == 0)
			return (true);
		if (i == 0)
			return (true);
	}
	if (ft_strncmp(str, ";", ft_strlen(str)))
	{
		if (array[i + 1] == NULL)
			return (true);
		if (ft_strncmp(array[i + 1], "|", ft_strlen(array[i + 1])) == 0)
			return (true);
		if (ft_strncmp(array[i + 1], ";", ft_strlen(array[i + 1])) == 0)
			return (true);
		if (i == 0)
			return (true);
	}
	return (false);
}

bool	ft_check_both2(char **array, char *str, int i)
{
	if (ft_strncmp(str, ";", ft_strlen(str)) == 0)
	{
		if (array[i + 1] == NULL)
			return (true);
		if (ft_strncmp(array[i + 1], "|", ft_strlen(array[i + 1])) == 0)
			return (true);
		if (ft_strncmp(array[i + 1], ";", ft_strlen(array[i + 1])) == 0)
			return (true);
		if (ft_strncmp(array[i - 1], "|", ft_strlen(array[i + 1])) == 0)
			return (true);
		if (ft_strncmp(array[i - 1], ";", ft_strlen(array[i + 1])) == 0)
			return (true);
	}
	return (false);
}

bool	ft_check_both(char **array, char *str, int i)
{
	if (ft_strncmp(str, "|", ft_strlen(str)) == 0)
	{
		if (array[i + 1] == NULL)
			return (true);
		if (ft_strncmp(array[i + 1], "|", ft_strlen(array[i + 1])) == 0)
			return (true);
		if (ft_strncmp(array[i + 1], ";", ft_strlen(array[i + 1])) == 0)
			return (true);
		if (ft_strncmp(array[i - 1], "|", ft_strlen(array[i + 1])) == 0)
			return (true);
		if (ft_strncmp(array[i - 1], ";", ft_strlen(array[i + 1])) == 0)
			return (true);
	}
	return (ft_check_both2(array, str, i));
}
