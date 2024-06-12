/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_com.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:51:57 by farah             #+#    #+#             */
/*   Updated: 2024/06/07 13:50:04 by paxoc01          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LST_COM_H
# define LST_COM_H

# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define OK 0
# define ERROR 1
# define NO_INFILE 2
# define NO_PERMISSIONS 3

typedef struct s_command	t_command;

typedef struct s_command
{
	char			**content;
	char			*full_path;
	t_command		*next;
}					t_command;

int	ft_lstsize_com(t_command *lst);
t_command	*ft_lstnew_com(char **content);
t_command	*ft_lstmap_com(t_command *lst, void *(*f)(void *), void (*del)(char **));
t_command	*ft_lstlast_com(t_command *lst);
void	ft_lstiter_com(t_command *lst, void (*f)(void *));
void	ft_lstdelone_com(t_command *lst, void (*del)(char **));
void	ft_lstclear_com(t_command **lst, void (*del)(char **));
void	ft_lstadd_front_com(t_command **lst, t_command *new);
void	ft_lstadd_back_com(t_command **lst, t_command *new);



#endif