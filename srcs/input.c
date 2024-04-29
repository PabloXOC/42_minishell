/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 11:30:25 by pximenez          #+#    #+#             */
/*   Updated: 2024/04/29 15:54:08 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*command_init(void)
{
	t_command	*command;

	command = (t_command *) malloc (sizeof (t_command));
	if (command == NULL)
		return (ft_write_error_c(MALLOC_ERROR, command));
	command->command_parsed = NULL;
	command->full_address = NULL;
	command->input = NULL;
	command->n_words = 0;
	command->paired = 0;
	command->exit = 0;
	command->user = NULL;
	command->hostname = NULL;
	command->dir = NULL;
	command->entry = NULL;
	command->command_list = NULL;
	command->create_var = NULL;
	command->redirect_input = NULL;
	command->redirect_output = NULL;
	command->limiter = NULL;
	command->append_output = NULL;
	return (command);
}

int	ft_pair(char *input, char c, int i, t_command *command)
{
	while (input[i] != 0)
	{
		if (input[i] == c)
		{
			command->paired = 2;
			i++;
			break ;
		}
		i++;
	}
	return (i);
}

bool	ft_not_complete(char *input, t_command *command)
{
	int	i;

	i = 0;
	while (input[i] != 0)
	{
		if (input[i] == '"' || input[i] == '\'')
		{
			command->paired = 1;
			i = ft_pair(input, input[i], i + 1, command);
			if (command->paired == 1)
			{
				command->paired = 0;
				return (true);
			}
		}
		if (input[i] == '\\' && input[i + 1] == 0)
			return (true);
		if (input[i] == '\\' && input[i + 1] == '\\')
			return (false);
		if (input[i] != 0)
			i++;
	}
	return (false);
}

char	*ft_join_input(char *s1, char *s2)
{
	char	*str;
	int		len_1;
	int		len_2;

	len_1 = ft_strlen(s1);
	len_2 = ft_strlen(s2);
	str = ft_calloc(len_1 + len_2 + 1, 1);
	if (str == NULL)
		return (NULL);
	ft_memcpy(str, s1, len_1);
	ft_memcpy(&str[len_1], s2, len_2);
	str[len_1 + len_2] = 0;
	free(s1);
	return (str);
}
