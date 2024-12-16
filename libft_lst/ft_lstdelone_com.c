/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone_com.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 12:25:20 by pximenez          #+#    #+#             */
/*   Updated: 2024/09/19 15:27:33 by paxoc01          ###   ########.fr       */
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
		if (lst->text_input != NULL)
			free(lst->text_input);
		if (lst->redirect_input != NULL)
			free(lst->redirect_input);
		if (lst->redirect_output != NULL)
			free(lst->redirect_output);
	}
	free(lst);
}
