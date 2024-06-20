/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: farah <farah@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 19:51:57 by farah             #+#    #+#             */
/*   Updated: 2024/06/18 21:38:46 by farah            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <ctype.h>
# include <errno.h>
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>
# include "srcs/minishell.h"

# define OK 0
# define ERROR 1
# define NO_INFILE 2
# define NO_PERMISSIONS 3

typedef struct s_clist
{
	char			**command;
	char			*path;
	struct s_clist	*next;
}			t_clist;

typedef struct s_info
{
	t_clist	*commands;
	char	**env;
	int		num_commands;
	int		fd_in;
	int		fd_out;
	int		no_infile;
	int		no_permissions;
	char	*temp_file;
}			t_info;

/* Access */
int		ft_file_exists(char *file);
int		ft_read_permission(char *file);
int		ft_write_permission(char *file);
int		ft_infile_permissions(char *file, t_info *commands);
int		ft_outfile_permissions(char *file, t_info *commands);

/* Command path */
char	*ft_find_command_path(char **envp, char *command, int i);
char	*ft_return_accessible_path(char **available_paths, char *command);
void	ft_free_commands(t_info *commands);
t_clist	*ft_fill_middle_commands(char **argv, char **envp, int argc);
t_info	*ft_commands(char **argv, char **envp, int argc);

/* Lists */
t_clist	*ft_new_t_clist(char **command, char *path);
void	ft_t_clist_add_back(t_clist **lst, t_clist *lst_new);
t_clist	*ft_t_clist_last(t_clist *lst);
void	ft_t_clist_delone(t_clist *lst);
void	ft_t_clist_clear(t_clist **lst);
int		ft_t_clist_size(t_clist *lst);

/* Aid */
void	ft_free_char_pp(char **stack);
int		ft_char_pp_len(char **stack);
void	print_char_pp(char **stack);
int		ft_open_infile(char *file, t_info *commands);
int		ft_open_outfile(char *file, t_info *commands);
int		ft_file_permissions(char *file1, char *file2, t_info *commands);
char	*ft_create_file_name(void);
int		**open_pipes(t_data *data);
void	close_pipes(int	**pipe_fd, t_info *commands);

/* Clean up */
void	ft_cleanup(char *in_file, t_info *commands);

/* Bonus */
int		father_son_bonus(t_info *commands);

#endif
