/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   files2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/28 16:50:13 by paxoc01           #+#    #+#             */
/*   Updated: 2024/10/08 21:40:35 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_temp_file(t_command *com, t_data *data)
{
	int	fd;

	com->temp_file = ft_create_file_name(data);
	if (com->temp_file == NULL)
		return (MALLOC_ERROR);
	fd = open(com->temp_file, O_RDWR | O_CREAT, 0644);
	if (fd == -1)
		return (error_i(OPEN_ERROR, data));
	write(fd, com->text_input, ft_strlen(com->text_input));
	close(fd);
	return (SUCCESS);
}

/* int	identify_amb2(char *str, int i, int s_q, int d_q)
{
	while (str[i] != 0)
	{
		if (str[i] == '\"' && s_q % 2 == 0 && (i == 0 || str[i - 1] != '\\'))
			d_q++;
		if (str[i] == '\'' && d_q % 2 == 0 && (i == 0 || str[i - 1] != '\\'))
			s_q++;
		if (s_q % 2 == 0 && d_q % 2 == 0 && str[i] == ' ')
			return (AMBIG_REDIRECT);
		i++;
	}
	return (SUCCESS);
} */

int	identify_amb(char *str, t_data *data)
{
	if (str == NULL || str[0] == 0)
	{
		ft_printf("ambiguous redirect\n");
		exit_codes(EXIT_1, data);
		return (AMBIG_REDIRECT);
	}
	return (SUCCESS);
}
