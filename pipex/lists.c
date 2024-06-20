/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lists.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/04 12:08:19 by farah             #+#    #+#             */
/*   Updated: 2024/06/18 20:44:30 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "libft/ft_printf.h"
#include "pipex.h"

/* t_clist	*ft_new_t_clist(char **command, char *path)
{
	t_clist	*node;

	node = (t_clist *)malloc(sizeof(t_clist));
	if (!(node))
		return (NULL);
	node->command = command;
	node->path = path;
	node->next = NULL;
	return (node);
}

int	ft_t_clist_size(t_clist *lst)
{
	int	count;

	count = 0;
	while (lst != NULL)
	{
		lst = lst->next;
		count++;
	}
	return (count);
}

void	ft_t_clist_add_back(t_clist **lst, t_clist *lst_new)
{
	t_clist	*last;

	if (lst != NULL && lst_new != NULL)
	{
		last = ft_t_clist_last(*lst);
		if (last == NULL)
			(*lst) = lst_new;
		else
			last->next = lst_new;
	}
}

t_clist	*ft_t_clist_last(t_clist *lst)
{
	int		size;
	int		i;

	size = ft_t_clist_size(lst);
	i = 0;
	while (i < size - 1)
	{
		lst = lst->next;
		i++;
	}
	return (lst);
}

void	ft_t_clist_delone(t_clist *lst)
{
	if (lst != NULL)
	{
		if (lst->command != NULL)
			ft_free_char_pp(lst->command);
		if (lst->path != NULL)
			free(lst->path);
	}
	free (lst);
} */
