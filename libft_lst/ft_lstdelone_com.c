/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_com.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pximenez <pximenez@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:25:20 by pximenez          #+#    #+#             */
/*   Updated: 2024/07/03 17:45:39 by pximenez         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lst_com.h"

/* void	del(void *content)
{
	free(content);
} */

void	ft_lstdelone_com(t_command *lst, void (*del)(char **))
{
	if (lst != NULL)
	{
		if (lst->content != NULL)
			del(lst->content);
		if (lst->full_path != NULL)
			free(lst->full_path);
		if (lst->temp_file != NULL)
			free(lst->temp_file);
	}
	free(lst);
}
