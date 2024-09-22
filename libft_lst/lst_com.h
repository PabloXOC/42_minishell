/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_com.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: paxoc01 <paxoc01@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:51:57 by farah             #+#    #+#             */
/*   Updated: 2024/09/21 18:06:20 by paxoc01          ###   ########.fr       */
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
# include <stdbool.h>

typedef struct s_command	t_command;

typedef struct s_command
{
	char		**content;
	char		*full_path;
	char		*text_input; //    text of <<
	char		*redirect_input; // file name if we have a <
	char		*redirect_output; // file name if we have a > or >>
	int			fd_in;
	int			fd_out;
	bool		file_input; // boolean for (true == <)
	bool		append_output; // boolean for (true == >>) & (false == >)
	bool		no_permissions;
	bool		no_infile;
	char		*temp_file;
	bool		previous_error;
	t_command	*next;
}					t_command;

int			ft_lstsize_com(t_command *lst);
t_command	*ft_lstnew_com(char **content);
t_command	*ft_lstlast_com(t_command *lst);
void		ft_lstiter_com(t_command *lst, void (*f)(void *));
void		ft_lstdelone_com(t_command *lst, void (*del)(char **));
void		ft_lstclear_com(t_command **lst, void (*del)(char **));
void		ft_lstadd_front_com(t_command **lst, t_command *new);
void		ft_lstadd_back_com(t_command **lst, t_command *new);

#endif
