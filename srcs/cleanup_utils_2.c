/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup_utils_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 15:40:58 by paxoc01           #+#    #+#             */
/*   Updated: 2024/09/21 13:49:55 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_input_info2(t_info *info)
{
	if (info->terminal_input != NULL)
		free(info->terminal_input);
	if (info->text_input != NULL)
		ft_free_char_pp(info->text_input);
	if (info->search_eof != NULL)
		free(info->search_eof);
	if (info->final_text_last != NULL)
		free(info->final_text_last);
	if (info->first_line_vars != NULL)
		free(info->first_line_vars);
	if (info->real_eof != NULL)
		free(info->real_eof);
}

void	ft_free_input_info(t_info *info)
{
	if (info != NULL)
	{
		if (info->final_text != NULL)
			free(info->final_text);
		if (info->first_line != NULL)
			free(info->first_line);
		if (info->first_line_and_final_text != NULL)
			free(info->first_line_and_final_text);
		if (info->first_line_ref != NULL)
			free(info->first_line_ref);
		if (info->first_line_split != NULL)
			ft_free_char_pp(info->first_line_split);
		if (info->init_input != NULL)
			free(info->init_input);
		if (info->init_input_split != NULL)
			ft_free_char_pp(info->init_input_split);
		if (info->list_eof != NULL)
			ft_free_char_pp(info->list_eof);
		ft_free_input_info2(info);
		free(info);
	}
	info = NULL;
}
